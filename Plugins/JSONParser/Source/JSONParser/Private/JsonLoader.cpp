/*
Copyright 2018-2021 Bright Night Games

author: Santamaria Nicolas
version: 1.0

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "JsonLoader.h"
#include "Async/Async.h"
#include "Misc/FileHelper.h"
#include "Templates/Function.h"
void UJSONAsyncAction_RequestHttpMessage::Activate()
{
	// Create HTTP Request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetURL(URL);

	// Setup Async response
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
	{
		FString ResponseString = "";
		if (bSuccess)
		{
			ResponseString = Response->GetContentAsString();
		}

		this->HandleRequestCompleted(ResponseString, bSuccess);
	});

	// Handle actual request
	HttpRequest->ProcessRequest();
}


void UJSONAsyncAction_RequestHttpMessage::HandleRequestCompleted(FString ResponseString, bool bSuccess)
{
	UJsonFieldData* JsonData = nullptr;
	FString OutString;
	if (bSuccess)
	{
		/* Deserialize object */
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseString);
		FJsonSerializer::Deserialize(JsonReader, JsonObject);

		if (RegisteredWithGameInstance.IsValid()) {
			JsonData = UJsonFieldData::CreateFromJson(RegisteredWithGameInstance.Get(), JsonObject);
		}
	}
	
	Completed.Broadcast(JsonData, bSuccess);
}


UJSONAsyncAction_RequestHttpMessage* UJSONAsyncAction_RequestHttpMessage::AsyncRequestHTTP(UObject* WorldContextObject, FString URL)
{
	// Create Action Instance for Blueprint System
	UJSONAsyncAction_RequestHttpMessage* Action = NewObject<UJSONAsyncAction_RequestHttpMessage>();
	Action->URL = URL;
	Action->RegisterWithGameInstance(WorldContextObject);

	return Action;
}

////////////////////////


void UJSONAsyncAction_RequestFile::Activate()
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
	{
		FString FileData;
		auto Result = FFileHelper::LoadFileToString(FileData, *Filename);
		HandleRequestCompleted(FileData, Result);
	});
}

void UJSONAsyncAction_RequestFile::HandleRequestCompleted(FString ResponseString, bool bSuccess)
{
	// credits : https://www.tomlooman.com/unreal-engine-async-blueprint-http-json/
	
	UJsonFieldData* JsonData = nullptr;
	FString OutString;
	if (bSuccess)
	{
		/* Deserialize object */
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseString);
		FJsonSerializer::Deserialize(JsonReader, JsonObject);

		if (RegisteredWithGameInstance.IsValid()) {
			JsonData = UJsonFieldData::CreateFromJson(RegisteredWithGameInstance.Get(), JsonObject);
		}
	}

	AsyncTask(ENamedThreads::GameThread, [this, JsonData, bSuccess]()
	{
		Completed.Broadcast(JsonData, bSuccess);
		//SetReadyToDestroy();
	});
}


UJSONAsyncAction_RequestFile* UJSONAsyncAction_RequestFile::AsyncRequestFile(UObject* WorldContextObject, FString Filename)
{
	// Create Action Instance for Blueprint System
	UJSONAsyncAction_RequestFile* Action = NewObject<UJSONAsyncAction_RequestFile>();
	Action->Filename = Filename;
	Action->RegisterWithGameInstance(WorldContextObject);

	return Action;
}
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
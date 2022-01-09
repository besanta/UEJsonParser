#include "JsonLoader.h"

void ULZAsyncAction_RequestHttpMessage::Activate()
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


void ULZAsyncAction_RequestHttpMessage::HandleRequestCompleted(FString ResponseString, bool bSuccess)
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
			// JsonData = UJsonFieldData::CreateFromJson(RegisteredWithGameInstance.Get(), JsonObject);
		}
	}
	
	Completed.Broadcast(JsonData, bSuccess);
}


ULZAsyncAction_RequestHttpMessage* ULZAsyncAction_RequestHttpMessage::AsyncRequestHTTP(UObject* WorldContextObject, FString URL)
{
	// Create Action Instance for Blueprint System
	ULZAsyncAction_RequestHttpMessage* Action = NewObject<ULZAsyncAction_RequestHttpMessage>();
	Action->URL = URL;
	Action->RegisterWithGameInstance(WorldContextObject);

	return Action;
}
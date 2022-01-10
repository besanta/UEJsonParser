#pragma once

#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Engine/Engine.h"

#include "JsonFieldData.h"
#include "JsonLoader.generated.h"

// Event that will be the 'Completed' exec wire in the blueprint node along with all parameters as output pins.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHttpRequestCompleted, UJsonFieldData*, Json, bool, bSuccess);

UCLASS() // Change the _API to match your project
class UJSONAsyncAction_RequestHttpMessage : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected:

	void HandleRequestCompleted(FString ResponseString, bool bSuccess);

public:

	/** Execute the actual load */
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create JSON Data from HTTP", BlueprintInternalUseOnly = "true", Category = "JSON", WorldContext = "WorldContextObject"))
		static UJSONAsyncAction_RequestHttpMessage* AsyncRequestHTTP(UObject* WorldContextObject, FString URL);

	UPROPERTY(BlueprintAssignable)
		FOnHttpRequestCompleted Completed;

	/* URL to send GET request to */
	FString URL;
};

UCLASS() // Change the _API to match your project
class UJSONAsyncAction_RequestFile : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected:

	void HandleRequestCompleted(FString ResponseString, bool bSuccess);

public:

	/** Execute the actual load */
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create JSON Data from File", BlueprintInternalUseOnly = "true", Category = "JSON", WorldContext = "WorldContextObject"))
		static UJSONAsyncAction_RequestFile* AsyncRequestFile(UObject* WorldContextObject, FString Filename);

	UPROPERTY(BlueprintAssignable)
		FOnHttpRequestCompleted Completed;

	/* URL to send GET request to */
	FString Filename;
};
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
class ULZAsyncAction_RequestHttpMessage : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected:

	void HandleRequestCompleted(FString ResponseString, bool bSuccess);

public:

	/** Execute the actual load */
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create JSON Data", BlueprintInternalUseOnly = "true", Category = "JSON", WorldContext = "WorldContextObject"))
		static ULZAsyncAction_RequestHttpMessage* AsyncRequestHTTP(UObject* WorldContextObject, FString URL);

	UPROPERTY(BlueprintAssignable)
		FOnHttpRequestCompleted Completed;

	/* URL to send GET request to */
	FString URL;
};


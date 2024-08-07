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

	void HandleRequestCompleted(const FString& ResponseString, bool bSuccess);

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
class UJSONAsyncAction_POSTHttpMessage : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected:

	void HandleRequestCompleted(const FString& ResponseString, bool bSuccess);

public:

	/** Execute the actual load */
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Send JSON data with HTTP", BlueprintInternalUseOnly = "true", Category = "JSON", WorldContext = "WorldContextObject"))
		static UJSONAsyncAction_POSTHttpMessage* AsyncRequestHTTP(UObject* WorldContextObject, FString URL, FString Verb, UJsonFieldData* Json, const TMap<FString, FString>& Header);

	UPROPERTY(BlueprintAssignable)
		FOnHttpRequestCompleted Completed;

	/* URL to send GET request to */
	FString URL;
	FString Verb;
	FString JSONContent;
	TMap<FString, FString> Header;
};

UCLASS() // Change the _API to match your project
class UJSONAsyncAction_RequestFile : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected:

	void HandleRequestCompleted(const FString& ResponseString, bool bSuccess);

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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWriteCompleted, bool, Success);
UCLASS() // Change the _API to match your project
class UJSONAsyncAction_SaveFile : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected:

	void HandleRequestCompleted(bool bSuccess);

public:

	/** Execute the actual load */
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save JSON Data to File", BlueprintInternalUseOnly = "true", Category = "JSON", WorldContext = "WorldContextObject"))
		static UJSONAsyncAction_SaveFile* AsyncRequestFile(UObject* WorldContextObject, UJsonFieldData* Json, FString Filename);

	UPROPERTY(BlueprintAssignable)
		FOnWriteCompleted Completed;

	FString Filename;
	FString JSONContent;

};
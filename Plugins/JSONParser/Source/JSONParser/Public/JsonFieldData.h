/*
Copyright 2018 Bright Night Games

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once

#include "UObject/Interface.h"

#include "Serialization/JsonTypes.h"
//#include "Dom/JsonValue.h"
//#include "Dom/JsonObject.h"

#include "Serialization/JsonSerializer.h"

#include "Engine/World.h"
#include "UObject/UnrealType.h"

#include "JsonFieldData.generated.h"

class FProperty;

UCLASS(BlueprintType, Blueprintable)
class UJsonFieldData : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	/* Resets the current post data */
	void Reset();

	void WriteObject(TSharedRef<TJsonWriter<TCHAR>> writer, FString key, FJsonValue* value);
public:
	UObject* contextObject;

	/* The actual field data */
	TSharedPtr<FJsonObject> Data;

	class UWorld* GetWorld() const override 
	{
		return GEngine->GetWorldFromContextObject(contextObject, EGetWorldErrorMode::LogAndReturnNull);
	}

	/* Get Content of the FieldData as a String */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Content String"), Category = "JSON")
	FString GetContentString();

	/* Get pretty content of the FieldData as a String */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Pretty String"), Category = "JSON")
	FString GetPrettyString();

	/* Get Content of the FieldData as a compressed String */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Archive"), Category = "JSON")
	void GetContentCompressed(TArray<uint8>& Compressed, bool& bIsValid);

	/* Creates a new post data object */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Create JSON Data", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
	static UJsonFieldData* Create(UObject* WorldContextObject);

	/* Creates a new post data object */
	static UJsonFieldData* CreateFromJson(UObject* WorldContextObject, TSharedPtr<FJsonObject> Data);

	/* Creates a new post data object */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Create JSON Data From String", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
	static UJsonFieldData* CreateFromString(UObject* WorldContextObject, const FString& data);

	/* Adds string data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add String Field"), Category = "JSON")
	UJsonFieldData* SetString(const FString& key, const FString& value);

	/* Adds a string array to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add String Array Field"), Category = "JSON")
	UJsonFieldData* SetStringArray(const FString& key, const TArray<FString> arrayData);

	/* Adds Name data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Name Field"), Category = "JSON")
	UJsonFieldData* SetName(const FString& key, const FName& value);

	/* Adds a string array to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Name Array Field"), Category = "JSON")
	UJsonFieldData* SetNameArray(const FString& key, const TArray<FName> arrayData);

	/* Adds Byte data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Byte Field"), Category = "JSON")
	UJsonFieldData* SetByte(const FString& key, uint8 value);

	/* Adds a Byte array to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Byte Array Field"), Category = "JSON")
	UJsonFieldData* SetByteArray(const FString& key, const TArray<uint8> arrayData);

	/* Adds Bool data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Bool Field"), Category = "JSON")
	UJsonFieldData* SetBool(const FString& key, bool value);

	/* Adds a Bool array to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Bool Array Field"), Category = "JSON")
	UJsonFieldData* SetBoolArray(const FString& key, const TArray<bool> arrayData);

	/* Adds Number data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Number Field"), Category = "JSON")
	UJsonFieldData* SetNumber(const FString& key, float value);

	/* Adds Number data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Number Array Field"), Category = "JSON")
	UJsonFieldData* SetNumberArray(const FString& key, const TArray<float> arrayData);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Vector Field"), Category = "JSON")
	UJsonFieldData * SetVector(const FString & key, FVector value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Vector Array Field", DeprecatedFunction, DeprecationMessage = "Use Add Any Field"), Category = "JSON")
	UJsonFieldData * SetVectorArray(const FString & key, const TArray<FVector>& arrayData);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Color Field", DeprecatedFunction, DeprecationMessage = "Use Add Any Field"), Category = "JSON")
	UJsonFieldData * SetColor(const FString & key, const FLinearColor& value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Rotator Field", DeprecatedFunction, DeprecationMessage = "Use Add Any Field"), Category = "JSON")
	UJsonFieldData * SetRotator(const FString & key, FRotator value);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Transform Field", DeprecatedFunction, DeprecationMessage = "Use Add Any Field"), Category = "JSON")
	UJsonFieldData * SetTransform(const FString & key, FTransform value);

	/* Sets nested object data to the post array */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Data Field"), Category = "JSON")
	UJsonFieldData* SetObject(const FString& key, const UJsonFieldData* objectData);

	/* Adds a new post data field to the specified data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Data Array Field"), Category = "JSON")
	UJsonFieldData* SetObjectArray(const FString& key, const TArray<UJsonFieldData*> arrayData);

	/* Adds string data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Class Field"), Category = "JSON")
	UJsonFieldData* SetClass(const FString& key, UClass* value);
	
	/* Adds a Bool array to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Class Array Field"), Category = "JSON")
	UJsonFieldData* SetClassArray(const FString& key, const TArray<UClass*> arrayData);

	/* Gets string data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get String Field"), Category = "JSON")
	FString GetString(const FString& key) const;

	/* Gets a string array with the specified key */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get String Array Field"), Category = "JSON")
	TArray<FString> GetStringArray(const FString& key) const;

	/* Gets Name data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Name Field"), Category = "JSON")
	FName GetName(const FString& key) const;

	/* Gets a Name array with the specified key */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Name Array Field"), Category = "JSON")
	TArray<FName> GetNameArray(const FString& key) const;

	/* Gets Byte data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Byte Field"), Category = "JSON")
	uint8 GetByte(const FString& key) const;

	/* Gets a Byte array with the specified key */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Byte Array Field"), Category = "JSON")
	TArray<uint8> GetByteArray(const FString& key) const;

	/* Gets Bool data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Bool Field"), Category = "JSON")
	bool GetBool(const FString& key) const;

	/* Gets a Bool array with the specified key */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Bool Array Field"), Category = "JSON")
	TArray<bool> GetBoolArray(const FString& key) const;

	/* Gets Number data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Number Field"), Category = "JSON")
	float GetNumber(const FString& key) const;

	/* Gets a Number array with the specified key */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Number Array Field"), Category = "JSON")
	TArray<float> GetNumberArray(const FString& key) const;

	/* Fetches nested post data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Data Field"), Category = "JSON")
	UJsonFieldData* GetObject(const FString& key) const;

	/* Gets an array with post data with the specified key */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Data Array Field"), Category = "JSON")
	TArray<UJsonFieldData*> GetObjectArray(const FString& key) const;

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Transform Field"), Category = "JSON")
	FTransform GetTransform(const FString & key) const;

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Rotator Field"), Category = "JSON")
	FRotator GetRotator(const FString & key) const;
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Color Field"), Category = "JSON")
	FLinearColor GetColor(const FString & key) const;

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Color Array Field"), Category = "JSON")
	TArray<FLinearColor> GetColorArray(const FString & key) const;

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Vector Field"), Category = "JSON")
	FVector GetVector(const FString & key) const;
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Vector Array Field"), Category = "JSON")
	TArray<FVector> GetVectorArray(const FString & key) const;


	/* Fetches nested post data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Class Field"),Category = "JSON")
	UClass* GetClass(const FString& key) const;

	/* Gets an array with post data with the specified key */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Class Array Field"), Category = "JSON")
	TArray<UClass*> GetClassArray(const FString& key) const;

	
	/* Get all keys from the object */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Keys"), Category = "JSON")
	TArray<FString> GetObjectKeys() const;

	/* Check wheter or not the key is in the property list */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Has Key"), Category = "JSON")
	bool HasKey(const FString& key) const;

	/* Check wheter or not the key is in the property list */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Has All Keys"), Category = "JSON")
	bool HasAllKeys(const TArray<FString>& keys) const;

	/* Creates new data from the input string */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From String"), Category = "JSON")
	UJsonFieldData* FromString(const FString& dataString);

	/* Creates new data from the input compressed JSON string */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From Archive"), Category = "JSON")
	UJsonFieldData* FromCompressed(const TArray<uint8>& CompressedData, bool& bIsValid);

	/* Adds UObject data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add UObject Field"), Category = "JSON|Experimental")
	UJsonFieldData* SetUObject(const FString& key, const UObject* value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get UObject Field"), Category = "JSON|Experimental")
	UObject* GetUObjectField(const FString& Key, UObject* Context, bool& Success);
	
	/* Adds Any data to the post data */
	UFUNCTION(BlueprintPure, CustomThunk, meta = (DisplayName = "Add Any Field", CustomStructureParam = "Value"), Category = "JSON|Experimental")
	UJsonFieldData* SetAnyProperty(const FString& Key, UProperty* Value);

	DECLARE_FUNCTION(execSetAnyProperty)
	{
		//https://forums.unrealengine.com/showthread.php?56537-Tutorial-How-to-accept-wildcard-structs-in-your-UFUNCTIONs&p=206131#post206131
		P_GET_PROPERTY(FStrProperty, Key);
		Stack.MostRecentProperty = NULL;
		Stack.MostRecentPropertyAddress = NULL;
		Stack.StepCompiledIn<FProperty>(NULL);
		FProperty* Property = Stack.MostRecentProperty;
		void* DataPtr = Stack.MostRecentPropertyAddress;
		P_FINISH;

		UJsonFieldData* LocalContext = ExactCast<UJsonFieldData>(P_THIS_OBJECT);
		if (LocalContext) {
			WriteProperty(LocalContext->Data, Key, Property, DataPtr);
		}

		*(UJsonFieldData**)RESULT_PARAM = LocalContext;
	}

private:
	static TSharedPtr<FJsonObject> CreateJsonValueFromUObjectProperty(const FObjectProperty * InObjectProperty, const void * InObjectData);

	static TSharedPtr<FJsonObject> CreateJsonValueFromUObject(const UObject* InObject);

	static TSharedPtr<FJsonObject> CreateJsonValueFromStruct(const FStructProperty* StructProperty, const void* StructPtr);

	static TArray<TSharedPtr<FJsonValue>> CreateJsonValueArray(const FArrayProperty* ArrayProperty, const void * InPropertyData);

	static TSharedPtr<FJsonValue> GetJsonValue(const FProperty * InProperty, const void * InPropertyData);
	static bool SetJsonValue(TSharedPtr<FJsonValue> Value, const FProperty* Property, void* PropertyData);

	static bool WriteProperty(TSharedPtr<FJsonObject> JsonWriter, const FString& Identifier, const FProperty* InProperty, const void* InPropertyData);


	FORCEINLINE static TSharedPtr<FJsonObject> CreateJSONVector(const FVector& value)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		JsonObject->SetNumberField("X", value.X);
		JsonObject->SetNumberField("Y", value.Y);
		JsonObject->SetNumberField("Z", value.Z);
		return JsonObject;
	}

	FORCEINLINE static FVector CreateVector(const TSharedPtr<FJsonObject> JsonObject)
	{
		if (JsonObject->HasTypedField<EJson::Number>("X")
			&& JsonObject->HasTypedField<EJson::Number>("Y")
			&& JsonObject->HasTypedField<EJson::Number>("Z")
			)
		{
			return FVector(
				JsonObject->GetNumberField("X"),
				JsonObject->GetNumberField("Y"),
				JsonObject->GetNumberField("Z")
			);
		}

		return FVector();
	}

	FORCEINLINE static TSharedPtr<FJsonObject> CreateJSONColor(const FLinearColor& value)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		JsonObject->SetNumberField("R", value.R);
		JsonObject->SetNumberField("G", value.G);
		JsonObject->SetNumberField("B", value.B);
		JsonObject->SetNumberField("A", value.A);

		return JsonObject;
	}

	FORCEINLINE static FLinearColor CreateColor(const TSharedPtr<FJsonObject> JsonObject)
	{
		if (JsonObject->HasTypedField<EJson::Number>("R")
			&& JsonObject->HasTypedField<EJson::Number>("G")
			&& JsonObject->HasTypedField<EJson::Number>("B")
			&& JsonObject->HasTypedField<EJson::Number>("A")
			)
		{
			return FLinearColor(
				JsonObject->GetNumberField("R"),
				JsonObject->GetNumberField("G"),
				JsonObject->GetNumberField("B"),
				JsonObject->GetNumberField("A")
			);
		}

		return FLinearColor();
	}

	FORCEINLINE static TSharedPtr<FJsonObject> CreateJSONRotator(const FRotator& value)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		JsonObject->SetNumberField("Pitch", value.Pitch);
		JsonObject->SetNumberField("Yaw", value.Yaw);
		JsonObject->SetNumberField("Roll", value.Roll);

		return JsonObject;
	}

	FORCEINLINE static FRotator CreateRotator(const TSharedPtr<FJsonObject> JsonObject)
	{
		if (JsonObject->HasTypedField<EJson::Number>("Yaw")
			&& JsonObject->HasTypedField<EJson::Number>("Pitch")
			&& JsonObject->HasTypedField<EJson::Number>("Roll")
			)
		{
			return FRotator(
				JsonObject->GetNumberField("Yaw"),
				JsonObject->GetNumberField("Pitch"),
				JsonObject->GetNumberField("Roll")
			);
		}

		return FRotator();
	}
};

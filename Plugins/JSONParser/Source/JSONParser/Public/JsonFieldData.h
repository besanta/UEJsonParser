// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
// Copyright 1998-2016 Bright Night Games, Inc. All Rights Reserved.
#pragma once
//#include "Json.h"

#include "UObject/Interface.h"

#include "Serialization/JsonTypes.h"
#include "Dom/JsonValue.h"
#include "Dom/JsonObject.h"

#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

#include "Engine/World.h"
#include "Engine/Engine.h"

#include "JsonFieldData.generated.h"

UINTERFACE(Blueprintable)
class USerializableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ISerializableInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "JSON")
	UJsonFieldData* Serialize(UJsonFieldData* data);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "JSON")
	bool Unserialize(UJsonFieldData* data);
};

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

	/* Contains the actual page content, as a string */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JSON")
	//FString Content;

	/* Get Content of the FieldData as a String */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Content String"), Category = "JSON")
	FString GetContentString();

	/* Get Content of the FieldData as a compressed String */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Archive"), Category = "JSON")
	void GetContentCompressed(TArray<uint8>& Compressed, bool& bIsValid);

	/* Creates a new post data object */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Create JSON Data", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
	static UJsonFieldData* Create(UObject* WorldContextObject);

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

	/* Sets nested object data to the post array */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Data Field"), Category = "JSON")
	UJsonFieldData* SetObject(const FString& key, const UJsonFieldData* objectData);

	/* Adds Vector data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Vector Field"), Category = "JSON")
	UJsonFieldData* SetVector(const FString& key, FVector value);

	/* Adds Vector array data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Vector Array Field"), Category = "JSON")
	UJsonFieldData* SetVectorArray(const FString& key, const TArray<FVector>& arrayData);

	/* Adds Color data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Color Field"), Category = "JSON")
	UJsonFieldData* SetColor(const FString& key, FColor value);

	/* Adds Vector array data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Color Array Field"), Category = "JSON")
	UJsonFieldData* SetColorArray(const FString& key, const TArray<FColor>& arrayData);

	/* Adds Rotator data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Rotator Field"), Category = "JSON")
	UJsonFieldData* SetRotator(const FString& key, FRotator value);

	/* Adds Tranform data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Transform Field"), Category = "JSON")
	UJsonFieldData* SetTranform(const FString& key, FTransform value);

	/* Adds string data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Class Field"), Category = "JSON")
	UJsonFieldData* SetClass(const FString& key, UClass* value);
	
	/* Adds a Bool array to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Class Array Field"), Category = "JSON")
	UJsonFieldData* SetClassArray(const FString& key, const TArray<UClass*> arrayData);


	/* Adds string data to the post data */
	//https://forums.unrealengine.com/showthread.php?56537-Tutorial-How-to-accept-wildcard-structs-in-your-UFUNCTIONs&p=206131#post206131
	//UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Struct Field", CustomStructureParam = "value"), Category = "JSON")
	//UJsonFieldData* SetStruct(const FString& key, const UProperty* value);

	// Example Blueprint function that receives any struct as input
	/*
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "AnyStruct"), Category = "JSON")
		void SetStructProperty(UProperty* AnyStruct);

	DECLARE_FUNCTION(execSetStructProperty)
	{
		// Steps into the stack, walking to the next property in it
		Stack.Step(Stack.Object, NULL);

		// Grab the last property found when we walked the stack
		// This does not contains the property value, only its type information
		UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);

		// Grab the base address where the struct actually stores its data
		// This is where the property value is truly stored
		void* StructPtr = Stack.MostRecentPropertyAddress;

		// We need this to wrap up the stack
		P_FINISH;

	}
	*/

	/* Adds a new post data field to the specified data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Data Array Field"), Category = "JSON")
	UJsonFieldData* SetObjectArray(const FString& key, const TArray<UJsonFieldData*> arrayData);



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

	/* Gets Vector data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Vector Field"), Category = "JSON")
	FVector GetVector(const FString& key) const;

	/* Gets Vector data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Vector Array Field"), Category = "JSON")
	TArray<FVector> GetVectorArray(const FString& key) const;

	/* Gets Color data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Color Field"), Category = "JSON")
	FColor GetColor(const FString& key) const;

	/* Gets Vector data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Color Array Field"), Category = "JSON")
	TArray<FColor> GetColorArray(const FString& key) const;

	/* Gets Rotator data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Rotator Field"), Category = "JSON")
	FRotator GetRotator(const FString& key) const;

	/* Gets Transform data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Transform Field"), Category = "JSON")
	FTransform GetTransform(const FString& key) const;

	/* Fetches nested post data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Data Field"), Category = "JSON")
	UJsonFieldData* GetObject(const FString& key) const;

	/* Fetches nested post data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Class Field"),Category = "JSON")
	UClass* GetClass(const FString& key) const;

	/* Gets an array with post data with the specified key */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Class Array Field"), Category = "JSON")
	TArray<UClass*> GetClassArray(const FString& key) const;

	/* Gets an array with post data with the specified key */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Array Field"), Category = "JSON")
	TArray<UJsonFieldData*> GetObjectArray(const FString& key) const;

	/* Get all keys from the object */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Keys"), Category = "JSON")
	TArray<FString> GetObjectKeys() const;

	/* Creates new data from the input string */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From String"), Category = "JSON")
	UJsonFieldData* FromString(const FString& dataString);

	/* Creates new data from the input compressed JSON string */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "From Archive"), Category = "JSON")
	UJsonFieldData* FromCompressed(const TArray<uint8>& CompressedData, bool& bIsValid);



	FORCEINLINE static TSharedRef<FJsonValue> CreateJsonValueFromVector(const FVector& InVec) 
	{
		TArray<TSharedPtr<FJsonValue>> *StructJsonArray = new TArray<TSharedPtr<FJsonValue>>();
		StructJsonArray->Add(MakeShareable(new FJsonValueNumber(InVec.X)));
		StructJsonArray->Add(MakeShareable(new FJsonValueNumber(InVec.Y)));
		StructJsonArray->Add(MakeShareable(new FJsonValueNumber(InVec.Z)));
		return MakeShareable(new FJsonValueArray(*StructJsonArray));


	}

	FORCEINLINE static FVector CreateVectorFromJsonValue(const TSharedPtr<FJsonValue>& InJson)
	{
		check(InJson.IsValid());
		FVector OutVector;
		TArray<TSharedPtr<FJsonValue>> JsonArray = InJson->AsArray();
		OutVector.X = JsonArray[0]->AsNumber();
		OutVector.Y = JsonArray[1]->AsNumber();
		OutVector.Z = JsonArray[2]->AsNumber();
		return OutVector;
	}

	FORCEINLINE static FColor CreateColorFromJsonValue(const TSharedPtr<FJsonValue>& InJson)
	{
		check(InJson.IsValid());
		FColor outColor;
		TArray<TSharedPtr<FJsonValue>> JsonArray = InJson->AsArray();
		if (JsonArray.Num() == 3) {
			outColor.R = JsonArray[0]->AsNumber();
			outColor.G = JsonArray[1]->AsNumber();
			outColor.B = JsonArray[2]->AsNumber();
			outColor.A = 1.0;
		}
		else if (JsonArray.Num() == 4) {
			outColor.R = JsonArray[0]->AsNumber();
			outColor.G = JsonArray[1]->AsNumber();
			outColor.B = JsonArray[2]->AsNumber();
			outColor.A = JsonArray[3]->AsNumber();
		}
		
		return outColor;
	}
};
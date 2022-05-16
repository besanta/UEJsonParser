# JSONParser

Easy way to read, create and manipulate JSON in Blueprints.

# Technical Details

* Handle JSON structured string
* Easy to use. No C++ coding required, everything can be managed via blueprints.
* Supported Types: Bool, String, Name, Byte, Number(float), Vector, LinearColor, Rotator, Transform, Class and arrays of these types.
* Encode anything with AddAnyField (LinearColor, SlateFont, Custom Blueprint Struct ... also works with UObject and every other Property type...). Only encode, no decoding.
* Encode properties of your UObjects (With AddUObjectField) recusively if they are flagged with SaveGame. 
* Compress JSON string (Archive). Read form archived JSON string.
* Read From File (Async)
* GET from HTTP (Async)
* Get Texture from Data64 string.
* Include C++ Source for C++ Projects.

# TODO
* Save JSON to File.

# Documentation
Simple example
![Alt serialize](Docs/simple.png?raw=true "Serialize")

## All Nodes
* Save / Load
![API LOAD](Docs/apiloadsave.png)

* UObject
![API UOBJ](Docs/apisetuobject.png)

* Add
![API ADD](Docs/apiadd.png)

* Get
![API GET](Docs/apiget.png)

## Sample
* To serialize datas to JSON
![Alt serialize](Docs/serialize.png?raw=true "Serialize")

* To unserialize datas from JSON
![unserialize](Docs/unserialize.png?raw=true "Unserialize")

* To successfully use AddUObjectField on your UObjects, you have to flag the relevant variables with the SaveGameFlag. 
You can locate it in the extended option of your variable.\
![Alt savegame](Docs/savegamevariableproperty.png?raw=true "SaveGame")

# Support
nicosanta@brightnightgames.net

# License
This is an open source project, you can use it freely. 
If you think this project is useful, please give me a star if you like it.



#include "PatternFinder.hpp"
#include "ObjectsStore.hpp"
#include "../utils.h"
#include "log.h"
#include "EngineClasses.hpp"

class FUObjectItem
{
public:
	UObject* Object; //0x0000
	int32_t Flags; //0x0008
	int32_t ClusterIndex; //0x000C
	int32_t SerialNumber; //0x0010
	//char Unknown[0x4];
	//char pad2[0x0010];
	//char pad3[0x0000];
};

class TUObjectArray
{
public:
	FUObjectItem* Objects;
	int32_t MaxElements;
	int32_t NumElements;
};

class FUObjectArray
{
public:
	int32_t ObjFirstGCIndex;
	int32_t ObjLastNonGCIndex;
	int32_t MaxObjectsNotConsideredByGC;
	int32_t OpenForDisregardForGC;
	TUObjectArray ObjObjects;
};
FUObjectArray* GUObjectArray = nullptr;

bool ObjectsStore::Initialize()
{
	static bool blGNames = false;
	if (!blGNames) {
        LOGE("1");
        uintptr_t UE4 = Tools::GetBaseAddress("libUE4.so");
        LOGE("UE4 ADDRESS: %zu", UE4);
        while (!UE4) {
            LOGE("2");
            UE4 = Tools::GetBaseAddress("libUE4.so");
            sleep(1);
        }
		/*auto GUObjectArray_Offset = Tools::FindPattern("libUE4.so", "?? ?? ?? E5 1F 01 C2 E7 04 00 84 E5 00 20 A0 E3");
        LOGE("GUObjectArray_Offset: %zu", GUObjectArray_Offset);
		if (GUObjectArray_Offset) {
            LOGE("3");
			GUObjectArray_Offset += *(uintptr_t *) ((GUObjectArray_Offset + *(uint8_t *) (GUObjectArray_Offset) + 0x8)) + 0x18;
			LOGE("GUObjectArray_Offset: %zu", GUObjectArray_Offset - UE4);
		}*/
        LOGE("4");
		GUObjectArray = (FUObjectArray*) (0x9422cd8);
        //LOGE("GUObjectArray_Offset: %d", GUObjectArray);
        LOGE("5");
		blGNames = true;
	}
	return true;
}

void* ObjectsStore::GetAddress()
{
	//LOGE("7!");
	return GUObjectArray;
}

size_t ObjectsStore::GetObjectsNum() const
{
	//LOGE("8!");
	return GUObjectArray->ObjObjects.NumElements;
}

UEObject ObjectsStore::GetById(size_t id) const
{
	//LOGE("9!");
	return GUObjectArray->ObjObjects.Objects[id].Object;
}





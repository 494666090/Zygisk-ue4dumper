
#include "PatternFinder.hpp"
#include "NamesStore.hpp"
#include "EngineClasses.hpp"
#include "../utils.h"

class FNameEntry {
public:
	/*class FNameEntry* Next;
    int32_t Index;*/
#ifdef __LP64__
	char pad[0xC];
#else
	char pad[0x8];
#endif

	union {
		char AnsiName[1024];
		wchar_t WideName[1024];
	};

	const char *GetName() const {
		return AnsiName;
	}
};

template<typename ElementType, int32_t MaxTotalElements, int32_t ElementsPerChunk>
class TStaticIndirectArrayThreadSafeRead
{
public:
	int32_t Num() const
	{
		return NumElements;
	}

	bool IsValidIndex(int32_t index) const
	{
		return index >= 0 && index < Num() && GetById(index) != nullptr;
	}

	ElementType const* const& GetById(int32_t index) const
	{
		return *GetItemPtr(index);
	}

private:
	ElementType const* const* GetItemPtr(int32_t Index) const
	{
		int32_t ChunkIndex = Index / ElementsPerChunk;
		int32_t WithinChunkIndex = Index % ElementsPerChunk;
		ElementType** Chunk = Chunks[ChunkIndex];
		return Chunk + WithinChunkIndex;

		/*int32_t ChunkIndex = Index / ElementsPerChunk;
		int32_t WithinChunkIndex = Index % ElementsPerChunk;
		ElementType** Chunk = Chunks[ChunkIndex];
		if (ChunkIndex > NumChunks) return nullptr;
		if (Index > MaxTotalElements) return nullptr;
		if (!Chunk) return nullptr;
		//0x8 for 64bits and 0x4 for 32bits
		int offset = WithinChunkIndex * 0x4;
		uintptr_t ptrAddress = *reinterpret_cast<uintptr_t*>(reinterpret_cast<unsigned char*>(Chunk) + offset);
		ElementType* ItemPtr = reinterpret_cast<ElementType*>(ptrAddress);
		return Chunk + WithinChunkIndex;
		*/
	}

	enum
	{
		ChunkTableSize = (MaxTotalElements + ElementsPerChunk - 1) / ElementsPerChunk
	};

	ElementType** Chunks[ChunkTableSize];
	__int32 NumElements;
	__int32 NumChunks;
};

using TNameEntryArray = TStaticIndirectArrayThreadSafeRead<FNameEntry, 2 * 1024 * 1024, 16384>;

TNameEntryArray* GlobalNames = nullptr;

bool NamesStore::Initialize()
{
	static bool blGNames = false;




	if (!blGNames) {
	//	auto GNames_Offset = Tools::FindPattern("libUE4.so", "E0 01 9F E5 00 00 8F E0 30 70 90 E5");


		GlobalNames = (TNameEntryArray *) (((uintptr_t (*)())(0x467d5e4))());

		blGNames = true;
	}
	return true;
	
}

void* NamesStore::GetAddress()
{
	return GlobalNames;
}

size_t NamesStore::GetNamesNum() const
{
	return GlobalNames->Num();
}

bool NamesStore::IsValid(size_t id) const
{
	return GlobalNames->IsValidIndex(static_cast<int32_t>(id));
}

std::string NamesStore::GetById(size_t id) const
{
	return GlobalNames->GetById(static_cast<int32_t>(id))->GetName();
}

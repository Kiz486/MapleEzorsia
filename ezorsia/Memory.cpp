#include "stdafx.h"
#include "Memory.h"
#include "detours.h"

bool Memory::SetHook(bool attach, void** ptrTarget, void* ptrDetour)
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	(attach ? DetourAttach : DetourDetach)(ptrTarget, ptrDetour);
	DetourTransactionCommit();
	DetourTransactionAbort();
	return true;
}

void Memory::FillBytes(const DWORD dwOriginAddress, const unsigned char ucValue, const int nCount) {
	//memset((void*)dwOriginAddress, ucValue, nCount);
    DWORD dwOldProtect;
    VirtualProtect((LPVOID)dwOriginAddress, nCount, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    memset((void*)dwOriginAddress, ucValue, nCount);
    VirtualProtect((LPVOID)dwOriginAddress, nCount, dwOldProtect, &dwOldProtect);
}

void Memory::WriteString(const DWORD dwOriginAddress, const char* sContent, const size_t nSize) {
	//memset((void*)dwOriginAddress, *sContent, nSize);
    DWORD dwOldProtect;
    VirtualProtect((LPVOID)dwOriginAddress, nSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    memset((void*)dwOriginAddress, *sContent, nSize);
    VirtualProtect((LPVOID)dwOriginAddress, nSize, dwOldProtect, &dwOldProtect);
}

void Memory::WriteByte(const DWORD dwOriginAddress, const unsigned char ucValue) {
	//*(unsigned char*)dwOriginAddress = ucValue;
    DWORD dwOldProtect;
    VirtualProtect((LPVOID)dwOriginAddress, sizeof(unsigned char), PAGE_EXECUTE_READWRITE, &dwOldProtect);
    *(unsigned char*)dwOriginAddress = ucValue;
    VirtualProtect((LPVOID)dwOriginAddress, sizeof(unsigned char), dwOldProtect, &dwOldProtect);
}

void Memory::WriteShort(const DWORD dwOriginAddress, const unsigned short usValue) {
	//*(unsigned short*)dwOriginAddress = usValue;
    DWORD dwOldProtect;
    VirtualProtect((LPVOID)dwOriginAddress, sizeof(unsigned short), PAGE_EXECUTE_READWRITE, &dwOldProtect);
    *(unsigned short*)dwOriginAddress = usValue;
    VirtualProtect((LPVOID)dwOriginAddress, sizeof(unsigned short), dwOldProtect, &dwOldProtect);
}

void Memory::WriteInt(const DWORD dwOriginAddress, const unsigned int dwValue) {
	//*(unsigned int*)dwOriginAddress = dwValue;
    DWORD dwOldProtect;
    VirtualProtect((LPVOID)dwOriginAddress, sizeof(unsigned int), PAGE_EXECUTE_READWRITE, &dwOldProtect);
    *(unsigned int*)dwOriginAddress = dwValue;
    VirtualProtect((LPVOID)dwOriginAddress, sizeof(unsigned int), dwOldProtect, &dwOldProtect);
}

void Memory::WriteMemory(const DWORD dwOriginAddress, const void* src, const size_t nSize) {
    DWORD dwOldProtect;
    VirtualProtect((LPVOID)dwOriginAddress, nSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    memcpy((void*)dwOriginAddress, src, nSize);
    VirtualProtect((LPVOID)dwOriginAddress, nSize, dwOldProtect, &dwOldProtect);
}

void Memory::CodeCave(void* ptrCodeCave, const DWORD dwOriginAddress, const int nNOPCount) {
	__try {
		if (nNOPCount) FillBytes(dwOriginAddress, 0x90, nNOPCount); // create space for the jmp
		WriteByte(dwOriginAddress, 0xe9); // jmp instruction
		WriteInt(dwOriginAddress + 1, (int)(((int)ptrCodeCave - (int)dwOriginAddress) - 5)); // [jmp(1 byte)][address(4 bytes)]
	} __except (EXCEPTION_EXECUTE_HANDLER) {}
}

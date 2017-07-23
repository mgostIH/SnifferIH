#include "HookFunctions.h"
BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
) {
	
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		
		
		CreateDirectoryA("Recv", NULL);
		CreateDirectoryA("Send", NULL);
		PutJMP(Get_Recv(), Hook_Recv);
		PutJMP(Get_Send(), Hook_Send);
		break;
	default:
		break;
	}
	return 1;
}


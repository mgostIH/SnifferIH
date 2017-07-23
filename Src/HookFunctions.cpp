#include "HookFunctions.h"
void* RecvAddr;
void* SendAddr;
__declspec(naked) int __stdcall Real_Recv(
	_In_  SOCKET s,
	_Out_ char   *buf,
	_In_  int    len,
	_In_  int    flags
)
{
	__asm{
		mov edi,edi
		push ebp
		mov ebp,esp
		mov eax, [RecvAddr]
		add eax, 5
		jmp eax
	}
}

__declspec(naked) int __stdcall Real_Send(
	_In_       SOCKET s,
	_In_ const char   *buf,
	_In_       int    len,
	_In_       int    flags
)
{
	__asm{
		mov edi, edi
		push ebp
		mov ebp, esp
		mov eax,[SendAddr]
		add eax,5
		jmp eax
	}
}

void * Get_Recv()
{
	RecvAddr = (void*)GetProcAddress(GetModuleHandleA("WS2_32.dll"), "recv");
	return RecvAddr;
}

void * Get_Send()
{
	SendAddr = (void*)GetProcAddress(GetModuleHandleA("WS2_32.dll"), "send");
	return SendAddr;
}

void PutJMP(void * WriteTo, void * HookFunction)
{
	DWORD old;
	DWORD bkup;
	VirtualProtect(WriteTo, 0x5, PAGE_EXECUTE_READWRITE, &old);
	memset(WriteTo, 0xE9, 1);
	DWORD RelOffset = (DWORD)HookFunction - (DWORD)WriteTo - 5;
	memcpy((void*)((DWORD)WriteTo+1), &RelOffset, 4);
	VirtualProtect(WriteTo, 0x5, old, &bkup);
	return;
}

int __stdcall Hook_Recv(SOCKET s, char * buf, int len, int flags)
{
	static int N = 0;
	auto ret = Real_Recv(s, buf, len, flags);
	std::string FileName = "Recv\\Log-";
	FileName += std::to_string(N++) + ".txt";
	auto File = std::ofstream(FileName);
	
	File.write(buf, len);
	return ret;
}

int __stdcall Hook_Send(SOCKET s, const char * buf, int len, int flags)
{
	static int N = 0;
	auto ret = Real_Send(s, buf, len, flags);
	std::string FileName = "Send\\Log-";
	FileName += std::to_string(N++) + ".txt";
	auto File = std::ofstream(FileName);
	
	File.write(buf, len);
	return ret;
}

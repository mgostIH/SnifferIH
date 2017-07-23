#pragma once
#include <Windows.h>
#include <winsock.h>
#include <winsock.h>
#include <string>
#include <fstream>
extern "C" __declspec(dllexport) int __stdcall Real_Recv(
	_In_  SOCKET s,
	_Out_ char   *buf,
	_In_  int    len,
	_In_  int    flags
);
extern "C" __declspec(dllexport) int __stdcall Real_Send(
	_In_       SOCKET s,
	_In_ const char   *buf,
	_In_       int    len,
	_In_       int    flags
);


extern "C" __declspec(dllexport) void* Get_Recv();
extern "C" __declspec(dllexport) void* Get_Send();

void PutJMP(void* WriteTo, void* HookFunction);

extern "C" __declspec(dllexport) int __stdcall Hook_Recv(
	_In_  SOCKET s,
	_Out_ char   *buf,
	_In_  int    len,
	_In_  int    flags
);
extern "C" __declspec(dllexport) int __stdcall Hook_Send(
	_In_       SOCKET s,
	_In_ const char   *buf,
	_In_       int    len,
	_In_       int    flags
);

#pragma once
#include <Windows.h> 
 #include<string>
using namespace std;
class WinDbg
{
public:
	WinDbg(void);
	~WinDbg(void);

	void ProcessDebugEvent(LPDEBUG_EVENT pDebug_event,const PROCESS_INFORMATION& pi);
	string GetFileNameFromHandle(HANDLE hFile);
};


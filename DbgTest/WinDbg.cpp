#include "StdAfx.h"
#include "WinDbg.h" 
 

WinDbg::WinDbg(void)
{

	STARTUPINFO si; 
	PROCESS_INFORMATION pi; 
	ZeroMemory( &si, sizeof(si) ); 
	si.cb = sizeof(si); 
	ZeroMemory( &pi, sizeof(pi) );

	::CreateProcess( (LPCWSTR)"d", NULL, NULL, NULL, FALSE, 
			DEBUG_ONLY_THIS_PROCESS, NULL,NULL, &si, &pi );

	DEBUG_EVENT debug_event = {0};
	for(;;)
	{
		if (!WaitForDebugEvent(&debug_event, INFINITE))
			return;
		ProcessDebugEvent(&debug_event, pi);  // User-defined function, not API
		ContinueDebugEvent(debug_event.dwProcessId,
			debug_event.dwThreadId,
			DBG_CONTINUE);
	}
}

void WinDbg::ProcessDebugEvent(LPDEBUG_EVENT pDebug_event,const PROCESS_INFORMATION& pi)
{ 
	switch(pDebug_event->dwDebugEventCode)
	{
	case OUTPUT_DEBUG_STRING_EVENT:
		{
		//	CStringW strEventMessage;  // Force Unicode
			OUTPUT_DEBUG_STRING_INFO & DebugString = pDebug_event->u.DebugString;

			WCHAR *msg=new WCHAR[DebugString.nDebugStringLength];
			// Don't care if string is ANSI, and we allocate double...

			ReadProcessMemory(pi.hProcess,       // HANDLE to Debuggee
				DebugString.lpDebugStringData, // Target process' valid pointer
				msg,                           // Copy to this address space
				DebugString.nDebugStringLength, NULL);

// 			if ( DebugString.fUnicode )
// 				strEventMessage = msg;
// 			else
// 				strEventMessage = (char*)msg; // char* to CStringW (Unicode) conversion.
			MessageBox(NULL,msg,NULL,0);
			delete []msg;
		}
		break;
	case CREATE_PROCESS_DEBUG_EVENT:

		{
			string strEventMessage = GetFileNameFromHandle(pDebug_event->u.CreateProcessInfo.hFile);
			// Use strEventMessage, and other members
			// of CreateProcessInfo to intimate the user of this event.
		}
		break;

	}
}

string WinDbg::GetFileNameFromHandle(HANDLE hFile)
{
	string str;

	return str;
}

WinDbg::~WinDbg(void)
{
}

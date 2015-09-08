/* 	
	This is a basic win32 DLL.
	
	Lucien S.
	Metrowerks Tech. Support.
*/

#include <windows.h>
#include <stdio.h>
#define EXP __declspec(dllexport)

extern "C" {
BOOL WINAPI DllMain ( HINSTANCE hInst, DWORD wDataSeg, LPVOID lpvReserved );

EXP int RectFrame(HDC hdc, int x1, int y1, int x2, int y2, int t);
EXP int EllipseFrame(HDC hdc, int x1, int y1, int x2, int y2, int t);
}
					
BOOL WINAPI DllMain( HINSTANCE hInst, DWORD wDataSeg, LPVOID lpReserved )
{
	switch(wDataSeg)
	{
    	case DLL_PROCESS_ATTACH:
    		MessageBox ( GetFocus(),
                  "attaching",
                  "Process attaching to testdll.dll...",
                  MB_OK|MB_SYSTEMMODAL );
      		return 1;
	  		break;
		case DLL_PROCESS_DETACH:
			MessageBox ( GetFocus(),
                  "detaching",
                  "Process detaching from testdll.dll...",
                  MB_OK|MB_SYSTEMMODAL );
			break;

	  	default:
	  		return 1;
      		break;
   	}
   	return 0;
}


EXP int RectFrame(HDC hdc, int x1, int y1, int x2, int y2, int t)
{
	Rectangle(hdc, x1, y1, x2, y2);
	Rectangle(hdc, x1+t, y1+t, x2-t, y2-t);
	return 1;
}

EXP int EllipseFrame(HDC hdc, int x1, int y1, int x2, int y2, int t)
{
	Ellipse(hdc, x1, y1, x2, y2);
	Ellipse(hdc, x1+t, y1+t, x2-t, y2-t);
	return 1;
}

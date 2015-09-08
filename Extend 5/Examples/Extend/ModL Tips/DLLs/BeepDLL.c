/***************************************************************************************/
/*									Beep DLL								            */
/*	This is a very simple DLL that does nothing more then beep when it is called. 		*/
/*	This is useful as a skeleton for actual DLLs that you may write.					*/
/*  if you're developing DLLs in a language other then C, you should try to get hold 	*/
/*  of a standard DLL skeleton in that language.										*/
/*																						*/
/*  Note:  you will need to Export the function names of the functions 					*/
/*         you wish to call from Extend in the Def file for this DLL.					*/
/*         If you copy the declaration for the beep function below, it will 			*/
/*         default to having a calling convention of __cdecl. 							*/
/*	J. Steven Lamperti, 9/23/94															*/
/***************************************************************************************/

#include	"ExtndDLL.h"
#include 	"Windows.h"

int WINAPI LibMain(HANDLE hInstance, WORD wDataSeg, WORD wHeapSize, LPSTR lpszCmdLine)
{
// This routine initializes data for the DLL
//  You can do any global initialization for the DLL here, if
//   you need to.  Most DLL's won't need to have anything more then
//   just an empty LibMain routine

	return(TRUE);
}


/*********************************************************************/
/* This is an exported routine for the DLL. 						 */
/*********************************************************************/

__declspec(dllexport) void BEEP(DataPtr ParamPtr)
{
	char    returnStr[255] = {"Beeped"};
	HANDLE  theReturnHand;
	char    *lpstr;

// The next line is the heart of the XCMD, in this case this XCMD is just
// issuing a SysBeep, but you should be able to do anything you want to here.
// To see how to access passed in parameters, read up on XCMDs in a book on
// them, or look at the sort example supplied with Extend.  (The sort example
// has two parameters passed to it when it is called, this beep XCMD has none.)

	Beep(100, 100);

//	here we just return a string in our return value.
    theReturnHand = (HANDLE) GlobalAlloc(GHND, 256);

    lpstr = GlobalLock(theReturnHand);
        strcpy(lpstr, returnStr);
    GlobalUnlock(theReturnHand);

	ParamPtr->returnValue = theReturnHand;
}
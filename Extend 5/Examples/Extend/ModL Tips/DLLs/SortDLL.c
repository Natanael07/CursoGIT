/***************************************************************************************/
/*												sort DLL								*/
/*	This is a simple DLL that sorts an array of numbers.                         		*/
/*	This is useful as a skeleton for actual DLLs that you may write.					*/
/*  if you're developing DLLs in a language other then C, you should try to get hold 	*/
/*  of a standard DLL skeleton in that language.										*/
/*																						*/
/*  Note:  you will need to Export the function names of the functions 					*/
/*         you wish to call from Extend in the Def file for this DLL.					*/
/*         If you copy the declaration for the sort function below, it will 			*/
/*         default to having a calling convention of __cdecl.  This is the correct 		*/
/* 		   convention for being called from Extend.									    */
/*	J. Steven Lamperti, 3/13/95     													*/
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

__declspec(dllexport) void Sort(DataPtr ParamPtr)
{
	double		    temp;
	long			i, j, rows;
	char		    theString[256], returnStr[256] = {"sorted"};
    HANDLE          theReturnHand;
    char            *lpstr;

// this if statement checks to see if a valid parameter was passed in for the
// second parameter, which is just supposted to be a long which contains a count of
// the number of cells to be sorted.

	if (ParamPtr->params[1] != NULL)
		{
		strcpy((char *) theString, (char *) *ParamPtr->params[1]);
		rows = atof(theString);
		}
	else
		rows = 0;

// this section does the actual sorting.  The dynamic array is in parameter 0, and
// elements of the dynamic array are indexed as follows;
// ((double *) *(ParamPtr->params[0]))[i]
// What we're doing here, is accessing the thing pointed to by paramPtr->params[0],
// casting it to be a double pointer, and indexing into that double pointer.

	if (ParamPtr->params[0] != NULL && rows > 0)
		{
		for (i = 0; i < rows-1; i++)
			{
			for (j = i+1; j < rows; j++)
				{
				if (((double *) *(ParamPtr->params[0]))[i] > ((double *) *(ParamPtr->params[0]))[j])
					{
					temp = ((double *) *(ParamPtr->params[0]))[i];
					((double *) *(ParamPtr->params[0]))[i] = ((double *) *(ParamPtr->params[0]))[j];
					((double *) *(ParamPtr->params[0]))[j] = temp;
					}
				}
			}
		}

//	here we just return a string in our return value.
    theReturnHand = (HANDLE) GlobalAlloc(GHND, 256);

    lpstr = GlobalLock(theReturnHand);
        strcpy(lpstr, returnStr);
    GlobalUnlock(theReturnHand);

	ParamPtr->returnValue = theReturnHand;
}


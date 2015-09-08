/***************************************************************************************/
/*												add DLL									*/
/*	This is a simple DLL that just adds two numbers, and returns the result.         	*/
/*	This is useful as a skeleton for actual DLLs that you may write.					*/
/*  if you're developing DLLs in a language other then C, you should try to get hold 	*/
/*  of a standard DLL skeleton in that language.										*/
/*																						*/
/*  Note:  you will need to Export the function names of the functions 					*/
/*         you wish to call from Extend.												*/
/*       																			    */
/*  Note that this is an example of a Standard DLL.  The sort, and Beep examples        */
/*  in this same folder, are examples of XCMD/DLLs, which are useful for cross 			*/
/*  platform compatibility with the macintosh.											*/
/*																						*/
/*	J. Steven Lamperti, 2/1/2000    													*/
/***************************************************************************************/

#include 	"Windows.h"

/*********************************************************************/
/* This is an exported routine for the DLL. 						 */
/*********************************************************************/

__declspec(dllexport) double add(double x, double y)
{
	return(x+y);
}


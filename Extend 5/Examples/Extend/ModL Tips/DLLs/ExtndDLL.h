/*
	File:		ExtndDLL.h

	Based on HyperXCMD.h
	Copyright:	© 1983-1993 by Apple Computer, Inc.
				All rights reserved.
*/

#ifndef	__ExtndDLL__
#define	__ExtndDLL__


// JSL - these definations are of several basic types
//  that are defined on the macintosh system, and which
//  the callback definations below rely on.

typedef char *Ptr;
typedef Ptr *Handle;
typedef unsigned char Boolean;
typedef unsigned char *StringPtr;
typedef struct { short exp[1], man[4]; } extended80;

// JSL -- alignment code these structures need to be 
// aligned on 2 bytes boundries
#pragma pack(2)

struct Point
	{
	short v;
	short h;
	};
typedef struct Point Point;

struct Rect {
short	top;
short	left;
short 	bottom;
short 	right;
};
typedef struct Rect Rect;

#define F_PASCAL( thetype ) thetype __stdcall /* __export */

/* result codes */
#define xresSucc				0
#define xresFail				1
#define xresNotImp				2

/* XCMDBlock constants for event.what... */
#define xOpenEvt				1000	/* the first event after you are created */
#define xCloseEvt				1001	/* your window is being forced close (Quit?) */
#define xGiveUpEditEvt			1002	/* you are losing Edit... */
#define xGiveUpSoundEvt			1003	/* you are losing the sound channel... */
#define xHidePalettesEvt		1004	/* someone called HideHCPalettes */
#define xShowPalettesEvt		1005	/* someone called ShowHCPalettes */
#define xEditUndo				1100	/* EditÑÑUndo */
#define xEditCut				1102	/* EditÑÑCut */
#define xEditCopy				1103	/* EditÑÑCopy */
#define xEditPaste				1104	/* EditÑÑPaste */
#define xEditClear				1105	/* EditÑÑClear */
#define xSendEvt				1200	/* script has sent you a message (text) */
#define xSetPropEvt				1201	/* set a window property */
#define xGetPropEvt				1202	/* get a window property */
#define xCursorWithin			1300	/* cursor is within the window */
#define xMenuEvt				1400	/* user has selected an item in your menu */
#define xMBarClickedEvt			1401	/* a menu is about to be shown--update if needed */

#define xShowWatchInfoEvt		1501	/* for variable and message watchers */
#define xScriptErrorEvt			1502	/* place the insertion point */
#define xDebugErrorEvt			1503	/* user clicked "Debug" at a complaint */
#define xDebugStepEvt			1504	/* hilite the line */
#define xDebugTraceEvt			1505	/* same as step but tracing */
#define xDebugFinishedEvt		1506	/* script ended */

#define paletteProc				2048	/* Windoid with grow box */
#define palNoGrowProc			2052	/* standard Windoid defproc */
#define palZoomProc				2056	/* Windoid with zoom and grow */
#define palZoomNoGrow			2060	/* Windoid with zoom and no grow */
#define hasZoom					8
#define hasTallTBar				2
#define toggleHilite			1


#define maxCachedChecks			16		/* maximum number of checkpoints in a script */


/* paramCount is set to these constants when first calling special XThings */
#define xMessageWatcherID		= -2;
#define xVariableWatcherID		= -3;
#define xScriptEditorID			= -4;
#define xDebuggerID				= -5;

/* XTalkObjectPtr->objectKind values */
#define stackObj				1
#define bkgndObj				2
#define cardObj					3
#define fieldObj				4
#define buttonObj				5


typedef struct XCmdBlock *XCmdPtr;
struct XCmdBlock {
	short paramCount;		 /* If = -1 then new use for XWindoids */
	Handle params[16];
	Handle returnValue;
	Boolean passFlag;

	Ptr entryPoint;			 /* to call back to HyperCard */
	short request;
	short result;
	long inArgs[8];
	long outArgs[4];
};

typedef XCmdPtr DataPtr;

typedef struct XTalkObject *XTalkObjectPtr;
struct XTalkObject {
	short objectKind;		/* stack, bkgnd, card, field, or button */
	long stackNum;			/* reference number of the source stack */
	long bkgndID;
	long cardID;
	long buttonID;
	long fieldID;
};


typedef struct CheckPts *CheckPtPtr;
typedef CheckPtPtr *CheckPtHandle;
struct CheckPts {
	short checks[maxCachedChecks];
};

// JSL - reset alignment
#pragma pack()

#ifdef __cplusplus
extern "C" {
#endif

/****  Memory Utilities  ****/
F_PASCAL( Handle ) GetGlobal(XCmdPtr paramPtr, StringPtr globName);
F_PASCAL( void ) SetGlobal(XCmdPtr paramPtr, StringPtr globName, Handle globValue);
F_PASCAL( void ) ZeroBytes(XCmdPtr paramPtr, Ptr dstPtr, long longCount);

/****  String Utilities  ****/
F_PASCAL( void ) ScanToReturn(XCmdPtr paramPtr, Ptr *scanPtr);
F_PASCAL( void ) ScanToZero(XCmdPtr paramPtr, Ptr *scanPtr);
F_PASCAL( Boolean ) StringEqual(XCmdPtr paramPtr, StringPtr str1, StringPtr str2);
F_PASCAL( long ) StringLength(XCmdPtr paramPtr, Ptr strPtr);
F_PASCAL( Ptr ) StringMatch(XCmdPtr paramPtr, StringPtr pattern, Ptr target);
F_PASCAL( void ) ZeroTermHandle(XCmdPtr paramPtr, Handle hndl);

/****  String Conversions  ****/
F_PASCAL( void ) BoolToStr(XCmdPtr paramPtr, Boolean bool, StringPtr str);
F_PASCAL( void ) ExtToStr(XCmdPtr paramPtr, extended80 num, StringPtr str);
F_PASCAL( void ) LongToStr(XCmdPtr paramPtr, long posNum, StringPtr str);
F_PASCAL( void ) NumToHex(XCmdPtr paramPtr, long num, short nDigits, StringPtr str);
F_PASCAL( void ) NumToStr(XCmdPtr paramPtr, long num, StringPtr str);
F_PASCAL( Handle ) PasToZero(XCmdPtr paramPtr, StringPtr str);
F_PASCAL( void ) PointToStr(XCmdPtr paramPtr, Point pt, StringPtr str);
F_PASCAL( void ) RectToStr(XCmdPtr paramPtr, Rect *rct, StringPtr str);
F_PASCAL( void ) ReturnToPas(XCmdPtr paramPtr, Ptr zeroStr, StringPtr pasStr);
F_PASCAL( Boolean ) StrToBool(XCmdPtr paramPtr, StringPtr str);
F_PASCAL( extended80 ) StrToExt(XCmdPtr paramPtr, StringPtr str);
F_PASCAL( long ) StrToLong(XCmdPtr paramPtr, StringPtr str);
F_PASCAL( long ) StrToNum(XCmdPtr paramPtr, StringPtr str);
F_PASCAL( void ) StrToPoint(XCmdPtr paramPtr, StringPtr str, Point *pt);
F_PASCAL( void ) StrToRect(XCmdPtr paramPtr, StringPtr str, Rect *rct);
F_PASCAL( void ) ZeroToPas(XCmdPtr paramPtr, Ptr zeroStr, StringPtr pasStr);

/****  Field Utilities  ****/
F_PASCAL( Handle ) GetFieldByID(XCmdPtr paramPtr, Boolean cardFieldFlag, short fieldID);
F_PASCAL( Handle ) GetFieldByName(XCmdPtr paramPtr, Boolean cardFieldFlag, StringPtr fieldName);
F_PASCAL( Handle ) GetFieldByNum(XCmdPtr paramPtr, Boolean cardFieldFlag, short fieldNum);
F_PASCAL( void ) SetFieldByID(XCmdPtr paramPtr, Boolean cardFieldFlag, short fieldID,
	Handle fieldVal);
F_PASCAL( void ) SetFieldByName(XCmdPtr paramPtr, Boolean cardFieldFlag,
	StringPtr fieldName, Handle fieldVal);
F_PASCAL( void ) SetFieldByNum(XCmdPtr paramPtr, Boolean cardFieldFlag, short fieldNum,
	Handle fieldVal);

#ifdef __cplusplus
}
#endif


#endif


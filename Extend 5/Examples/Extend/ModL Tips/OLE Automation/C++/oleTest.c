/* Win32 GUI app skeleton */

#define H_NO_MACHEADERS 1

#define H_NO_RENAME 1
#define H_MacTypes 1
#define H_ResTypes 1

#undef MAXLONG
#undef InsertMenuItem

#include <windows.h>
#include <ole2.h>

#undef DEFINE_GUID

#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    extern const GUID name = { l, w1, w2, b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 }


DEFINE_GUID(IID_IDispatch, 0x00020400L, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

DEFINE_GUID(IID_NULL, 0x00000000L, 0, 0, 0x00,0,0,0,0,0,0,0x00);

void 	CallExtend();
long	OLEInit();
void	OLEUninit();


char *pGuidString = "{E167B362-7044-11d2-99DE-00C0230406DF}" ;

char *pTypeLibGuidString = "{E167B361-7044-11d2-99DE-00C0230406DF}" ;

// {E167B362-7044-11d2-99DE-00C0230406DF}
DEFINE_GUID(CLSID_ExtendApp, 0xe167b362, 0x7044, 0x11d2, 0x99, 0xde, 0x0, 0xc0, 0x23, 0x4, 0x6, 0xdf);

						
int WINAPI WinMain( HINSTANCE hInst, 			/*Win32 entry-point routine */
					HINSTANCE hPreInst, 
					LPSTR lpszCmdLine, 
					int nCmdShow )
{	
	OLEInit();
	CallExtend();
	OLEUninit();

	return(0);
}


// JSL -- OLE errors will be in "winerror.h"
void CallExtend()
{
	HRESULT 	hr		= 0;
	HRESULT		err1 	= REGDB_E_CLASSNOTREG, 	err2 	= REGDB_E_INVALIDVALUE;
	HRESULT		err3 	= REGDB_E_IIDNOTREG, 	err4 	= REGDB_E_READREGDB;
	HRESULT		err5 	= CO_E_NOTINITIALIZED, 	err6 	= CO_E_SERVER_EXEC_FAILURE;
	HRESULT 	err7    = DISP_E_UNKNOWNNAME, 	err8	= DISP_E_BADPARAMCOUNT;
	HRESULT		err9 	= RPC_E_SERVERFAULT;
	LPDISPATCH 	m_pDisp = NULL;
	LPUNKNOWN	m_pUnknown = NULL;
	WCHAR 		*Name 	= (WCHAR *) L"Execute";
	DISPID		executeID, pokeID, requestID;
	EXCEPINFO 	ei;
	UINT 		uiErr;
	DISPPARAMS 	dispparamsNoArgs = {NULL, NULL, 0, 0}, dp, dp2, dp3;
	VARIANTARG 	*pokeVariant, *requestVariant, vString;
	BSTR 		itemStr, topicStr, valueStr, bStr;
	HKEY 		hKey;
	char 		ClsidString [80], buf[100];
	long 		length = sizeof (ClsidString), theErr;
	CLSID 		clsid;
	WCHAR 		wClsidString [80];
	VARIANT 	var;

	RegOpenKey(HKEY_CLASSES_ROOT, "Extend.Application", &hKey);
	RegQueryValue(hKey, "CLSID",  ClsidString, &length);
	RegCloseKey(hKey);

	MultiByteToWideChar(CP_ACP, 0, ClsidString, -1, wClsidString, 80); 
	CLSIDFromString (wClsidString, &clsid);
	
/*
Try to create an instance of the Extend object and get a pointer to its
IDispatch interface. Store pointer to object in global variable. If 
unsuccessful, signal with message box and abort.
*/

	hr = GetActiveObject(clsid, NULL, (IUnknown **) &m_pUnknown);

	if (hr == S_OK)
		{
		// JSL - found a existing instance
		hr = m_pUnknown->QueryInterface(IID_IDispatch, (void **) &m_pDisp);
		hr = m_pUnknown->Release();
		}
	else
		{
		theErr = GetLastError();
		MessageBox (NULL, TEXT("GetActiveObject Failed, creating a new Object"), TEXT("OleTest"), MB_OK) ;

		hr = CoCreateInstance (
			clsid, 					// class ID of object
			NULL,                   // controlling IUnkown
			CLSCTX_LOCAL_SERVER,	// context
			IID_IDispatch,			// interface wanted
			(LPVOID *) &m_pDisp) ;	// output variable
	
		
		if (hr != NOERROR)
			{
			theErr = GetLastError();
			MessageBox (NULL, TEXT("Create Instance Not Successful"), TEXT("OleTest"), MB_OK) ;
	       	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, theErr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, sizeof(buf), NULL);
	        MessageBox (NULL, buf, "Error", MB_OK);
			return;
			}
		}

/*
Get the ID numbers associated with the names of the methods and properties
in the IDispatch interface; store in member variables.  The L preceding the 
text strings in quotes means that the strings are always wide characters. If 
either ID cannot be found, signal the error and abort. 
*/
	
	// JSL -- Get DispID of Execute method
	
	hr = m_pDisp->GetIDsOfNames (
		IID_NULL,				// reserved
		&Name,					// Array of names to get IDs for
		1,        				// # of names in the array
		LOCALE_SYSTEM_DEFAULT,	// System locale
		&executeID) ;			// Array of IDs to fill on output
			
	if (hr)
		{
		MessageBox (NULL, TEXT("Get Execute Unsuccessful"), TEXT(""), MB_OK);  
		theErr = GetLastError();
	    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, theErr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, sizeof(buf), NULL);
	    MessageBox (NULL, buf, "Error", MB_OK);
		return;
		} 
	     
	// JSL -- Get DispID of Poke method
	
	Name = (WCHAR *) L"Poke";
	         
	hr = m_pDisp->GetIDsOfNames (
		IID_NULL,				// reserved
		&Name,					// Array of names to get IDs for
		1,        				// # of names in the array
		LOCALE_SYSTEM_DEFAULT,	// System locale
		&pokeID);				// Array of IDs to fill on output
			
	if (hr)
		{
		MessageBox (NULL, TEXT("Get Poke Unsuccessful"), TEXT(""), MB_OK);
		return;
		}
		
	// JSL -- Get DispID of Request method

	Name = (WCHAR *) L"Request";
	         
	hr = m_pDisp->GetIDsOfNames(
		IID_NULL,				// reserved
		&Name,					// Array of names to get IDs for
		1,        				// # of names in the array
		LOCALE_SYSTEM_DEFAULT,	// System locale
		&requestID);			// Array of IDs to fill on output
			
	if (hr)
		{
		MessageBox (NULL, TEXT("Get Request Unsuccessful"), TEXT(""), MB_OK) ;
		return;
		} 

/*
Poke a Value into Extend

Initialize the variant that will hold the BSTR.  Set the variant's
type flag to indicate the fact that this variant holds a BSTR. Place the
BSTR into the variant structure.
*/

	pokeVariant 			= malloc(sizeof(VARIANTARG) *3);
	
 	valueStr 				= SysAllocString((WCHAR *) L"34.6");
	VariantInit(&pokeVariant[0]); 
	pokeVariant[0].vt 		= VT_BSTR;
	pokeVariant[0].bstrVal 	= valueStr;

 	itemStr 				= SysAllocString((WCHAR *) L"global0:#0:0:0:0:0");
	VariantInit(&pokeVariant[1]); 
	pokeVariant[1].vt 		= VT_BSTR;
	pokeVariant[1].bstrVal 	= itemStr;

  	topicStr 				= SysAllocString((WCHAR *) L"system");
	VariantInit(&pokeVariant[2]); 
	pokeVariant[2].vt 		= VT_BSTR;
	pokeVariant[2].bstrVal 	= topicStr;

//	Set the DISPPARAMS structure that holds the variant.

	dp.rgvarg 					= pokeVariant;
	dp.cArgs 					= 3;
	dp.rgdispidNamedArgs 		= NULL;
	dp.cNamedArgs 				= 0;

//	Call IDispatch::Invoke()

	hr = m_pDisp->Invoke(
		pokeID,
		IID_NULL,
		LOCALE_SYSTEM_DEFAULT,
		DISPATCH_METHOD,
		&dp,
		NULL,
		&ei,
		&uiErr);

	SysFreeString(topicStr);
	SysFreeString(itemStr);
	SysFreeString(valueStr);

//
//  Request a value from Extend
//
//	Initialize the variant that will hold the BSTR.  Set the variant's
//	type flag to indicate the fact that this variant holds a BSTR. Place the
//	BSTR into the variant structure.

	requestVariant 				= malloc(sizeof(VARIANTARG) *2);
	
 	itemStr 					= SysAllocString((WCHAR *) L"global0:#0:0:0:0:0");
	VariantInit(&requestVariant[0]); 
	requestVariant[0].vt 		= VT_BSTR;
	requestVariant[0].bstrVal 	= itemStr;

  	topicStr 					= SysAllocString((WCHAR *) L"system");
	VariantInit(&requestVariant[1]); 
	requestVariant[1].vt 		= VT_BSTR;
	requestVariant[1].bstrVal 	= topicStr;

//	Set the DISPPARAMS structure that holds the variant.

	dp2.rgvarg 					= requestVariant;
	dp2.cArgs 					= 2;
	dp2.rgdispidNamedArgs 		= NULL;
	dp2.cNamedArgs 				= 0;

 	var.vt = VT_EMPTY;

//	Call IDispatch::Invoke()

	hr = m_pDisp->Invoke(
		requestID,
		IID_NULL,
		LOCALE_SYSTEM_DEFAULT,
		DISPATCH_METHOD,
		&dp2,
		&var,
		&ei,
		&uiErr);

	SysFreeString(topicStr);
	SysFreeString(itemStr);

/*

Call Execute in Extend

Initialize the variant that will hold the BSTR.  Set the variant's
type flag to indicate the fact that this variant holds a BSTR. Place the
BSTR into the variant structure.
*/

 	bStr 			= SysAllocString((WCHAR *) L"userError(global0);");

	VariantInit(&vString); 
	vString.vt 		= VT_BSTR;
	vString.bstrVal = bStr;
    
//	Set the DISPPARAMS structure that holds the variant.

   	dp3.rgvarg 				= &vString;
	dp3.cArgs 				= 1;
	dp3.rgdispidNamedArgs 	= NULL;
	dp3.cNamedArgs 			= 0;

//	Call IDispatch::Invoke()

	hr = m_pDisp->Invoke(
		executeID,
		IID_NULL,
		LOCALE_SYSTEM_DEFAULT,
		DISPATCH_METHOD,
		&dp3,
		NULL,
		&ei,
		&uiErr);  

	SysFreeString(bStr);

	m_pDisp->Release();

	return;
}


// JSL -- the following function initializes OLE

long	OLEInit()
{
// initialize COM for free-threading
OleInitialize(NULL);

return(TRUE);
}


// JSL -- the following function uninitializes OLE
void	OLEUninit()
{
	OleUninitialize();
}
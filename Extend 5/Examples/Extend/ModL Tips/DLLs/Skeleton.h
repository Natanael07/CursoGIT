
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SKELETON_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SKELETON_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef SKELETON_EXPORTS
#define SKELETON_API __declspec(dllexport)
#else
#define SKELETON_API __declspec(dllimport)
#endif

// This class is exported from the Skeleton.dll
class SKELETON_API CSkeleton {
public:
	CSkeleton(void);
	// TODO: add your methods here.
};

extern SKELETON_API int nSkeleton;

SKELETON_API int fnSkeleton(void);


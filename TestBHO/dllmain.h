// dllmain.h : Declaration of module class.

class CTestBHOModule : public CAtlDllModuleT< CTestBHOModule >
{
public :
	DECLARE_LIBID(LIBID_TestBHOLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TESTBHO, "{145B34FE-6D9B-4E82-B9B2-AB356BB5001E}")
};

extern class CTestBHOModule _AtlModule;

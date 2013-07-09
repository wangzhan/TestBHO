// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "TestBHO_i.h"
#include "dllmain.h"

CTestBHOModule _AtlModule;

class CTestBHOApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CTestBHOApp, CWinApp)
END_MESSAGE_MAP()

CTestBHOApp theApp;

BOOL CTestBHOApp::InitInstance()
{
	return CWinApp::InitInstance();
}

int CTestBHOApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}

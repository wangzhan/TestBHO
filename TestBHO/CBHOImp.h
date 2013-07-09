/**
 * @file    CBHOIm.h
 * @author  Zhan WANG <wangzhan@rd.netease.com>
 */
// CBHOImp.h : Declaration of the CCBHOImp

#pragma once
#include "resource.h"       // main symbols

#include "TestBHO_i.h"
#include "exdispid.h"  
#include "shlguid.h"  


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CCBHOImp

class ATL_NO_VTABLE CCBHOImp :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCBHOImp, &CLSID_CBHOImp>,
	public IObjectWithSiteImpl<CCBHOImp>,
	public IDispatchImpl<ICBHOImp, &IID_ICBHOImp, &LIBID_TestBHOLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
    public IDispEventImpl<1, CCBHOImp, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, 1, 1>,
    public IOleCommandTarget
{
public:
	CCBHOImp()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CBHOIMP)

DECLARE_NOT_AGGREGATABLE(CCBHOImp)

BEGIN_COM_MAP(CCBHOImp)
	COM_INTERFACE_ENTRY(ICBHOImp)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IObjectWithSite)
    COM_INTERFACE_ENTRY(IOleCommandTarget)
END_COM_MAP()

BEGIN_SINK_MAP(CCBHOImp)  
    SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, OnDocumentComplete)  
END_SINK_MAP()  



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
    // IObjectWithSiteImpl
    STDMETHOD(SetSite)(IUnknown * pUnkSite);

    // IOleCommandTarget
    STDMETHOD(Exec)(const GUID*, DWORD nCmdID, DWORD, VARIANTARG*, VARIANTARG* pvaOut);
    STDMETHOD(QueryStatus)(const GUID* pguidCmdGroup, ULONG cCmds, OLECMD prgCmds[], OLECMDTEXT* pCmdText);


private:
    void STDMETHODCALLTYPE OnDocumentComplete(IDispatch* pDisp, VARIANT* URL);
    void RemoveImages(IHTMLDocument2* pDocument);

private:
    CComPtr<IWebBrowser2> m_spWebBrowser;//保存Browser指针的私有变量
    BOOL m_fAdvised;
};

OBJECT_ENTRY_AUTO(__uuidof(CBHOImp), CCBHOImp)

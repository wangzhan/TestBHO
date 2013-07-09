/**
 * @file    CBHOIm.cpp
 * @author  Zhan WANG <wangzhan@rd.netease.com>
 */
// CBHOImp.cpp : Implementation of CCBHOImp

#include "stdafx.h"
#include "CBHOImp.h"


// CCBHOImp

STDMETHODIMP CCBHOImp::SetSite(IUnknown*pUnkSite)
{
    if(pUnkSite!=NULL)
    {
        HRESULT hr;
        CComPtr<IServiceProvider> sp;

        hr = pUnkSite->QueryInterface(&sp);
        if(SUCCEEDED(hr) && sp)
        {
            //缓存指向IWebBrowser2的指针
            hr = sp->QueryService(IID_IWebBrowserApp, IID_IWebBrowser2, (void**)&m_spWebBrowser);

            if(SUCCEEDED(hr)&&m_spWebBrowser!=0)
            {
                //注册DWebBrowserEvents2事件。
                hr = DispEventAdvise(m_spWebBrowser);
                if(SUCCEEDED(hr))
                {
                    m_fAdvised=TRUE;
                }
            }
        }
        m_spUnkSite = pUnkSite;
    }
    else
    {
        //取消注册事件。
        if(m_fAdvised)
        {
            DispEventUnadvise(m_spWebBrowser);
            m_fAdvised=FALSE;
        }
        //在此释放缓存的指针和其他资源。
        m_spWebBrowser.Release();
        //m_spTarget.Release();
    }
    //调用基类实现。
    return IObjectWithSiteImpl<CCBHOImp>::SetSite(pUnkSite);
}

void STDMETHODCALLTYPE CCBHOImp::OnDocumentComplete(IDispatch*pDisp,VARIANT*pvarURL)  
{  
    HRESULT hr = S_OK;   
    // 查询 IWebBrowser2 接口。   
    CComQIPtr<IWebBrowser2> spTempWebBrowser = pDisp;   
    // 此事件是否与顶级浏览器相关联?   
    if (spTempWebBrowser && m_spWebBrowser && m_spWebBrowser.IsEqualObject(spTempWebBrowser))   
    {   
        // 从浏览器中获取当前文档对象……   
        CComPtr<IDispatch>  spDispDoc;   
        hr = m_spWebBrowser->get_Document(&spDispDoc);   
        if (SUCCEEDED(hr))   
        {   
            // ……并查询 HTML 文档。   
            CComQIPtr<IHTMLDocument2> spHTMLDoc = spDispDoc;   
            if (spHTMLDoc != NULL) {   
                // 最后，删除这些图像。   
                RemoveImages(spHTMLDoc);   
            }   
        }   
    }   
}  

void CCBHOImp::RemoveImages(IHTMLDocument2* pDocument)   
{   
    CComPtr<IHTMLElementCollection> spImages;   
    // 从 DOM 中获取图像集。   
    HRESULT hr = pDocument->get_images(&spImages);   
    if (hr == S_OK && spImages != NULL) {   
        // 获取集合中的图像数。   
        long cImages = 0;   
        hr = spImages->get_length(&cImages);   
        if (hr == S_OK && cImages > 0)   
        {   
            for (int i = 0; i < cImages; i++)   
            {   
                CComVariant svarItemIndex(i);   
                CComVariant svarEmpty;   
                CComPtr<IDispatch> spdispImage;   
                // 按索引从集合中获取图像。   
                hr = spImages->item(svarItemIndex, svarEmpty, &spdispImage);   
                if (hr == S_OK && spdispImage != NULL)   
                {   
                    // 首先，查询通用 HTML 元素接口……   
                    CComQIPtr<IHTMLElement> spElement = spdispImage;   
                    if (spElement)   
                    {   
                        // ……然后请求样式接口。   
                        CComPtr<IHTMLStyle> spStyle;   
                        hr = spElement->get_style(&spStyle);   
                        // 设置 display="none" 以隐藏图像。   
                        if (hr == S_OK && spStyle != NULL)   
                        {   
                            static const CComBSTR sbstrNone(L"none");   
                            spStyle->put_display(sbstrNone);  
                        }  
                    }   
                }   
            }   
        }   
    }   
} 

STDMETHODIMP CCBHOImp::QueryStatus(const GUID* pguidCmdGroup, ULONG cCmds, OLECMD prgCmds[], OLECMDTEXT* pCmdText)  
{  
    if (cCmds == 0) return E_INVALIDARG;  
    if (prgCmds == 0) return E_POINTER;  
    prgCmds[0].cmdf = OLECMDF_ENABLED;  

    return S_OK;  
}  

STDMETHODIMP CCBHOImp::Exec(const GUID*, DWORD nCmdID, DWORD, VARIANTARG*, VARIANTARG*)
{
    if(m_spUnkSite == 0 || m_spWebBrowser == 0) return S_OK;
    HRESULT hRes = S_OK;

    CComPtr<IDispatch>        pDocDisp;
    CComQIPtr<IHTMLDocument2> pHtmlDoc2;
    hRes = m_spWebBrowser->get_Document(&pDocDisp);

    if(SUCCEEDED(hRes) && pDocDisp)
    {
        hRes = pDocDisp->QueryInterface(IID_IHTMLDocument2, (void**)&pHtmlDoc2);
        if(SUCCEEDED(hRes) && pHtmlDoc2)
        {
            SHANDLE_PTR nBrowser = 0;
            m_spWebBrowser->get_HWND(&nBrowser);
            HWND hWndParent = (HWND)nBrowser;

            HINSTANCE hInstance = _AtlBaseModule.GetModuleInstance();

            MessageBox(NULL, _T("Hello world!"), _T("Hello"), MB_OK|MB_ICONEXCLAMATION);
        }
    }
    return S_OK;
}

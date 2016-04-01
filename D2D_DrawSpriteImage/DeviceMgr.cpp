#include "stdafx.h"
#include "DeviceMgr.h"
#include "Base.h"


CDeviceMgr::CDeviceMgr()
	:m_p3D(NULL)
	, m_pDevice(NULL)
	, m_pSprite(NULL)
	, m_pFont(NULL)
{

}

CDeviceMgr::~CDeviceMgr()
{
}

void CDeviceMgr::Render_Begin()
{
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDeviceMgr::Render_End()
{
	m_pSprite->End();
	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}

void CDeviceMgr::Draw()
{
	
}


HRESULT CDeviceMgr::InitDevice(WINMODE Mode)
{
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	//장치의 성능을 조사한다
	D3DCAPS9		devicecaps;
	ZeroMemory(&devicecaps, sizeof(D3DCAPS9));

	if (FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &devicecaps)))
	{
		ERR_MSG(g_hWnd, L"장치 정보 얻어오기 실패 (Device.cpp)");
	}

	DWORD BehaviorFlag = 0;

	if (devicecaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		BehaviorFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		BehaviorFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = WINSIZEX;
	d3dpp.BackBufferHeight = WINSIZEY;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = true;

	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = Mode;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	if (FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, BehaviorFlag, &d3dpp, &m_pDevice)))
	{
		ERR_MSG(g_hWnd, L"D3D 장치 생성 실패");
		return E_FAIL;
	}

	//if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)));
	D3DXCreateSprite(m_pDevice, &m_pSprite);

	D3DXCreateFont(m_pDevice, 10, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Federation", &m_pFont);

	if (FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
	{
		ERR_MSG(g_hWnd, L"라인 생성 실패");
		return E_FAIL;
	}

	return S_OK;
}


void CDeviceMgr::Release()
{
	m_pSprite->Release();
	m_pDevice->Release();
	m_p3D->Release();
}


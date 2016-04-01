#pragma once
#include "stdafx.h"
#include "Base.h"

class CDeviceMgr
{
	DECLARE_SINGLETON(CDeviceMgr);
private:
	//장치의 성능을 조사한다. m_pDevice 생성해준다.
	LPDIRECT3D9			m_p3D;

	//장치를 대표하는 객체
	LPDIRECT3DDEVICE9			m_pDevice;
	LPD3DXSPRITE				m_pSprite;
	LPD3DXFONT					m_pFont;
	LPD3DXLINE			m_pLine;
public:
	LPD3DXLINE GetLine() { return m_pLine; }
	LPD3DXFONT GetFont() { return m_pFont; }
	LPD3DXSPRITE GetSprite() { return m_pSprite; }
	LPDIRECT3DDEVICE9 GetDevice() { return m_pDevice; }
public:
	HRESULT InitDevice(WINMODE Mode);

public:
	void Render_Begin();
	void Render_End();
	void Draw();
	void Release();

private:
	CDeviceMgr();
public:
	~CDeviceMgr();
};


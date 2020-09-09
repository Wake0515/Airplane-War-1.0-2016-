#include "StdAfx.h"
#include "Zidan.h"
#include "resource.h"


CImageList CZidan::m_Images;


CZidan::CZidan(int x, int y) :CGameObject(x, y)
{

}

CZidan::~CZidan(void)
{
}
BOOL CZidan::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP10, RGB(0, 0, 0), 60, 69, 1);
}
BOOL CZidan::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y - 8;
	}

	if (m_ptPos.y < -ZIDAN_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
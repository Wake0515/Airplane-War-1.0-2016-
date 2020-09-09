#include "StdAfx.h"
#include "bossball.h"
#include "resource.h"

CImageList Cbossball::m_Images;

Cbossball::Cbossball(int x, int y, int nMontion, int nn) :CGameObject(x, y), m_nMotion(nMontion)
{
	n = nn;
}

Cbossball::~Cbossball(void)
{
}
BOOL Cbossball::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause&&n>0)
	{

		m_ptPos.y = m_ptPos.y + 8;
		m_ptPos.x = m_ptPos.x - 3;

	}
	if (!bPause&&n<0)
	{

		m_ptPos.y = m_ptPos.y + 8;
		m_ptPos.x = m_ptPos.x + 3;

	}
	if (!bPause&&n == 0)
	{

		m_ptPos.y = m_ptPos.y + 8;

	}

	if (m_ptPos.y > GAME_HEIGHT + BOSSBALL_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOSSBALL_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL Cbossball::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP23, RGB(255, 255, 255), 44, 50, 1);
}
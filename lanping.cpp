#include "stdafx.h"
#include "lanping.h"
#include "resource.h"

CImageList Clanping::m_Images;

Clanping::Clanping()
{
	//随机确定X位置
	m_ptPos.x = m_ptPos.x = rand() % (GAME_WIDTH - LANPING_HEIGHT) + 1;


	m_nImgIndex = rand() % 2;

	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = -LANPING_HEIGHT;

	//随机确定速度
	m_V = rand() % 3 + 2;

	m_nWait = 0;
}


Clanping::~Clanping()
{

}
BOOL Clanping::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP13, RGB(0, 0, 0), 66, 62, 2);
}
BOOL Clanping::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>20)
		m_nWait = 0;

	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + LANPING_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -LANPING_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}


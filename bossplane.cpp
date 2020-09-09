#include "StdAfx.h"
#include "Bossplane.h"
#include "resource.h"

CImageList CBossplane::m_Images;

CBossplane::CBossplane(void)
{
	//随机确定X位置
	//随机确定图像索引
	m_nImgIndex = rand() % 2;

	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = BOSSPLANE_HEIGHT;
	m_ptPos.x = BOSSPLANE_HEIGHT;
	
	//随机确定速度
	m_V = rand() % 3 +2 ;

	m_nWait = 0;
}

CBossplane::~CBossplane(void)
{
}
BOOL CBossplane::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP9, RGB(255, 255, 255), 180, 160, 2);
}
BOOL CBossplane::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>20)
		m_nWait = 0;

	if (!bPause)
	{
		if (m_ptPos.x  > 500 || m_ptPos.x < -35)
			m_V = -m_V;
		m_ptPos.x = m_ptPos.x + m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + BOSSPLANE_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOSSPLANE_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
BOOL CBossplane::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}
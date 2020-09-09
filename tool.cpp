#include "stdafx.h"
#include "tool.h"
#include "resource.h"

CImageList Ctool::m_Images;

Ctool::Ctool()
{
	//随机确定X位置
	m_ptPos.x = m_ptPos.x = rand() % (GAME_WIDTH - TOOL_HEIGHT) + 1;


	m_nImgIndex = rand() % 2;

	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = -TOOL_HEIGHT;

	//随机确定速度
	m_V = rand() % 3 + 2;

	m_nWait = 0;
}


Ctool::~Ctool()
{

}
BOOL Ctool::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP14, RGB(0, 0, 0), 60, 34, 2);
}
BOOL Ctool::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>20)
		m_nWait = 0;

	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + TOOL_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -TOOL_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}


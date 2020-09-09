#include "StdAfx.h"
#include "Bomb.h"
#include "resource.h"
#include <math.h>


CImageList CBomb::m_Images;


CBomb::CBomb(int x,int y,int zidan):CGameObject(x,y)
{
	bullet = zidan;
}

CBomb::~CBomb(void)
{
}
BOOL CBomb::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BITMAP20,RGB(0,0,0),20,26,1);
}
BOOL CBomb::Draw(CDC* pDC,BOOL bPause)
{
	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y - 15;
		
		if (abs(bullet)>= 4)
		{
			if(bullet>0)
				m_ptPos.x = m_ptPos.x - 7;
				
			else
				m_ptPos.x = m_ptPos.x + 7;
		}
		
	}

	if(m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}
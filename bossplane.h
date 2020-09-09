#pragma once
#include "gameobject.h"
#include "minwindef.h"
#include "afxwin.h"
class CBossplane :public CGameObject
{
public:
	CBossplane(void);
	~CBossplane(void);
	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BOSSPLANE_HEIGHT, m_ptPos.y + BOSSPLANE_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	//是否可以开火发射子弹
	BOOL Fired();
	int bo_hp = 300;
private:
	static const int BOSSPLANE_HEIGHT = 180;
	static const int BOSSPLANE_WIDTH = 160;
	static CImageList m_Images;
	int    m_nMotion;//方向 1->向下 0->停止 -1->向上
					 //图像索引
	int m_nImgIndex;
	//速度
	int m_V;
	int    m_nWait;//发射延时
	
};

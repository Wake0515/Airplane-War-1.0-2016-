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
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
	int bo_hp = 300;
private:
	static const int BOSSPLANE_HEIGHT = 180;
	static const int BOSSPLANE_WIDTH = 160;
	static CImageList m_Images;
	int    m_nMotion;//���� 1->���� 0->ֹͣ -1->����
					 //ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_V;
	int    m_nWait;//������ʱ
	
};

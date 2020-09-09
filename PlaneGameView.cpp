// PlaneGameView.cpp : CPlaneGameView 类的实现
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "Bossplane.h"
#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"
#include "bossplane.h"
#include "Tool.h"
#include "zidan.h"
#include "lanping.h"
#include "bossball.h"
#include "bishaping.h"
#include <atlimage.h>
#include <mmsystem.h> //必须包含这文件
#pragma comment( lib, "Winmm.lib" ) //必须包含这文件


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
static int lll = 0;
static int xueping = 0;
static int daoju = 0;
static int wudi = 0;
static int lanping = 0;
static int zidan = 1;
static int bishaping = 0;
int background111 = 0;
// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

END_MESSAGE_MAP()

// CPlaneGameView 构造/析构

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: 在此处添加构造代码
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘制

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CPlaneGameView 打印

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneGameView 诊断

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView 消息处理程序
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//初始化游戏
	InitGame();
}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}

BOOL CPlaneGameView::InitGame()
{
	CRect rc;
	GetClientRect(rc);

	//产生随机数种子
	srand( (unsigned)time( NULL ) );

	//建立设备DC
	m_pDC = new CClientDC(this);

	//建立内存DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//建立内存位图
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//将位图选入内存DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();
	CBossplane::LoadImage();
	Ctool::LoadImage();
	Cbossball::LoadImage();
	CZidan::LoadImage();
	Clanping::LoadImage();
	Cbishaping::LoadImage();
	//产生主角(战机)
	m_pMe = new CMyPlane;

	//启动游戏
	SetTimer(1,30,NULL);
	background111 = 0;

	//背景音乐
	PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	return TRUE;
}
void CPlaneGameView::newgame()//重新开始
{
	if (inn == 0)
	{
		KillTimer(1);
		m_pMe = new CMyPlane;
		my_grade = 0;
		my_hp = 3;
		my_mp;
		bisha = 3;
		my_zidan = 1;
		zidan = 0;
		 lll = 0;
		 xueping = 0;
		 daoju = 0;
		 wudi = 0;
		 lanping = 0;
		 zidan = 1;
		 bishaping = 0;
		 background111 = 0;
		for (int i = 0; i < 8; i++)
			m_ObjList[i].RemoveAll();

		SetTimer(1, 30, NULL);
	}

}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	
	CRect m_client;
	GetClientRect(&m_client);

	CDC dcMen;
	dcMen.CreateCompatibleDC(pMemDC);
	CBitmap m_bmp;
	switch (my_grade/1000%5) {
	case 0:
		m_bmp.LoadBitmap(IDB_BITMAP8);
		break;
	case 1:
		m_bmp.LoadBitmap(IDB_BITMAP15);
		break;
	case 2:
		m_bmp.LoadBitmap(IDB_BITMAP16);
		break;
	case 3:
		m_bmp.LoadBitmap(IDB_BITMAP17);
		break;
	case 4:
		m_bmp.LoadBitmap(IDB_BITMAP18);
		break;
	}
	BITMAP bitmap;
	m_bmp.GetBitmap(&bitmap);
	CBitmap* pbmpOld = dcMen.SelectObject(&m_bmp);
	pMemDC->StretchBlt(0, 0, m_client.Width(), m_client.Height(), &dcMen, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

		
	/*
	//绘制天空
	CRect rctClient;
	GetClientRect(rctClient);
	CDC dcMem;
	dcMem.CreateCompatibleDC(pMemDC);
	CBitmap m_bmp;
	m_bmp.LoadBitmap(IDB_BITMAP8);
	BITMAP bitmap;
	m_bmp.GetBitmap(&bitmap);
	CBitmap   *pbmpOld = dcMem.SelectObject(&m_bmp);
	pMemDC->StretchBlt(0, 0, rctClient.Width(), rctClient.Height(), &dcMem, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

		*/
	//显示分数，显示血量，蓝量
	CString grade;
	grade.Format(_T("Your score:%d"),my_grade);
	pMemDC->SetBkMode(TRANSPARENT);
	//pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(GAME_WIDTH / 2-330, GAME_HEIGHT / 2 -300, grade);

	CString shuoming1;
	shuoming1.Format(_T("按W键开启无敌模式"));
	pMemDC->SetBkMode(TRANSPARENT);
	//pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(GAME_WIDTH / 2 - 330, GAME_HEIGHT / 2 - 250,shuoming1);

	CString shuoming2;
	shuoming2.Format(_T("按E键关闭无敌模式"));
	pMemDC->SetBkMode(TRANSPARENT);
	//pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(GAME_WIDTH / 2 - 330, GAME_HEIGHT / 2 - 220, shuoming2);


	CString shuoming3;
	shuoming3.Format(_T("！按B键释放ACE大招！"));
	pMemDC->SetBkMode(TRANSPARENT);
	//pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(GAME_WIDTH / 2 - 330, GAME_HEIGHT / 2 - 180, shuoming3);

	CString hp;
	hp.Format(_T("Your hp:%d"), my_hp);
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2 - 300, hp);

	CString mp;
	mp.Format(_T("Your Weapon grade:%d"), my_zidan);
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2 - 270, mp);

	CString ace;
	ace.Format(_T("Your ACE:%d"), bisha);
	pMemDC->SetBkMode(TRANSPARENT);
	//pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(GAME_WIDTH -100 , GAME_HEIGHT /2 -300 , ace);

	CString shuoming4;
	shuoming4.Format(_T("方向键控制飞机移动"));
	pMemDC->SetBkMode(TRANSPARENT);
	//pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(GAME_WIDTH - 100, GAME_HEIGHT / 2 - 270, shuoming4);

	CString shuoming5;
	shuoming5.Format(_T("空格键发射子弹"));
	pMemDC->SetBkMode(TRANSPARENT);
	//pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(GAME_WIDTH - 100, GAME_HEIGHT / 2 - 240, shuoming5);

	CString shuoming6;
	shuoming6.Format(_T("P键暂停"));
	pMemDC->SetBkMode(TRANSPARENT);
	//pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(GAME_WIDTH - 100, GAME_HEIGHT / 2 - 210, shuoming6);

	//绘制我方战机
	if(m_pMe!=NULL)
	{
	   m_pMe->Draw(m_pMemDC,FALSE);
	}
	else
	{   //Game Over
		if (my_hp <= 0)
		{
			CString str = _T("Game Over!");
			pMemDC->SetBkMode(TRANSPARENT);
			pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetTextColor(RGB(255, 0, 0));
			pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);

			grade.Format(_T("Your score:%d"), my_grade);
			pMemDC->SetBkMode(TRANSPARENT);
			//pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetTextColor(RGB(255, 0, 0));
			pMemDC->TextOut(GAME_WIDTH / 2, 3 * GAME_HEIGHT / 5, grade);

			CString str1 = _T("重新开始请按 ENTER");
			pMemDC->SetBkMode(TRANSPARENT);
			//pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetTextColor(RGB(255, 0, 0));
			pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 3, str1);
			if (GetKey(VK_RETURN) == 1)
				newgame();
		}
		}
	
	//绘制 导弹、爆炸、敌机、子弹
	for(int i=0;i<15;i++)
	{
		POSITION pos1,pos2;
		for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
			if(!pObj->Draw(pMemDC,FALSE))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
				//my_grade += 10;
			}
		}
	}

	//复制内存DC到设备DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	static int nCreator = rand() % 5 + 10;

	//随机产生敌机
	if (nCreator <= 0)
	{
		nCreator = rand() % 5 + 10;
		m_ObjList[enEnemy].AddTail(new CEnemy);
	}
	nCreator--;
	//随机爆出道具
	if (my_grade %600==0&&my_grade!=0&&daoju==0)
	{
		daoju = 1;
		for (int i = 1; i <= 3; i++)
			m_ObjList[enTool].AddTail(new Ctool);
	}
	//随机爆出蓝瓶
	if (my_grade %300==0 && my_grade != 0 && lanping == 0)
	{
		lanping = 1;
		for (int i = 1; i <= 3; i++)
			m_ObjList[enlanping].AddTail(new Clanping);
	}
	//随机爆出必杀瓶
	if (my_grade %400==0 && my_grade != 0 && bishaping == 0)
	{
		bishaping = 1;
		for (int i = 1; i <= 3; i++)
			m_ObjList[enbishaping].AddTail(new Cbishaping);
	}
	//产生boss

	if (my_grade >= 800 && lll == 0)
	{
		lll = 1;
		for (int i = 1; i <= 7; i++)
			m_ObjList[enBossplane].AddTail(new CBossplane);
	}

	if (my_grade >= 15000 && lll == 0)
	{
		lll = 1;
		for (int i = 1; i <= 7; i++)
			m_ObjList[enBossplane].AddTail(new CBossplane);
	}
	if (my_grade >= 25000 && lll == 0)
	{
		lll = 1;
		for (int i = 1; i <= 7; i++)
			m_ObjList[enBossplane].AddTail(new CBossplane);
	}

	if (m_pMe == NULL)
		return;

	//检测四个方向键，移动战机
	for (int i = 0; i < 4; i++)
	{
		int nMeMotion = 0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(VK_UP);
		if (nMeMotion == 1)
			m_pMe->SetVerMotion(1);

		nMeMotion = GetKey(VK_DOWN);
		if (nMeMotion == 1)
			m_pMe->SetVerMotion(-1);

		nMeMotion = GetKey(VK_RIGHT);
		if (nMeMotion == 1)
			m_pMe->SetHorMotion(1);

		nMeMotion = GetKey(VK_LEFT);
		if (nMeMotion == 1)
			m_pMe->SetHorMotion(-1);
	}

	//产生战机导弹
	if (GetKey(VK_SPACE) == 1)//按下了空格键
	{
		if (m_pMe != NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			if (my_zidan == 1) {
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 23, pt.y + 23));
			}
			else if (my_zidan == 2)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 12, pt.y + 12));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 34, pt.y + 34));
			}
			
			else if (my_zidan == 3)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 12, pt.y + 12));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 23, pt.y + 23));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 34, pt.y + 34));
			}
			else if(my_zidan ==4)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 12, pt.y + 12,my_zidan));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 34, pt.y + 34,my_zidan*-1));
			}
			else
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 12, pt.y + 12,my_zidan));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 23, pt.y + 23));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 34, pt.y + 34,my_zidan*-1));
			}
			}
	}
	//开启或关闭无敌模式
	if (GetKey('W') == 1)//按下了"W"键（大小写均可），控制无敌模式（1表示开启，0表示关闭）
	{
		
			wudi = 1;
		
	}
	if (GetKey('E') == 1)//按下了"E"键（大小写均可），控制无敌模式（1表示开启，0表示关闭）
	{
		
			wudi = 0;

	}
	//发射必杀技
	if (GetKey('B') == 1 && bisha)
	{
		if (m_pMe != NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			for (int ii = -50; ii < 50; ii++)
			{
				if (ii < 0)
					m_ObjList[enzidan].AddTail(new CZidan(pt.x + ii * 15, pt.y - 5 * ii));
				else
					m_ObjList[enzidan].AddTail(new CZidan(pt.x + ii * 15, pt.y + 5 * ii));

			}
			bisha--;
		}
	}
	//暂停
	if (GetKey('P') == 1)
	{
		KillTimer(1);
		if (AfxMessageBox(_T("暂停！"), MB_OK) == 1)
			SetTimer(1, 30, NULL);
		else (1);
	}

	//敌机发射子弹

	CPoint PlanePt = m_pMe->GetPoint();
	for (POSITION ePos = m_ObjList[enEnemy].GetHeadPosition(); ePos != NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		if (!pEnemy->Fired())
			continue;
		CPoint  ePt = pEnemy->GetPoint();

		BOOL by = FALSE;

		//敌机在战机前面
		if (pEnemy->GetMontion() == 1 && ePt.y < PlanePt.y)
			by = TRUE;
		//敌机在战机后面
		if (pEnemy->GetMontion() == -1 && ePt.y > PlanePt.y)
			by = TRUE;

		if (by && ePt.x >= PlanePt.x && ePt.x < PlanePt.x + CMyPlane::PLANE_WIDTH)
		{
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, pEnemy->GetMontion()));
		}
	}
	//boss发射子弹

	for (POSITION ePos = m_ObjList[enBossplane].GetHeadPosition(); ePos != NULL;)
	{
		CBossplane* pboss = (CBossplane*)m_ObjList[enBossplane].GetNext(ePos);
		if (!pboss->Fired())
		{
			continue;
		}
		CPoint  ePt = pboss->GetPoint();
		if (ePt.x + 35 >= PlanePt.x && ePt.x + 35 < PlanePt.x + CMyPlane::PLANE_WIDTH)
		{
			m_ObjList[enbossball].AddTail(new Cbossball(ePt.x + 30, ePt.y + 10, pboss->GetMontion(), 1));
			m_ObjList[enbossball].AddTail(new Cbossball(ePt.x + 40, ePt.y + 10, pboss->GetMontion(), 0));
			m_ObjList[enbossball].AddTail(new Cbossball(ePt.x + 50, ePt.y + 10, pboss->GetMontion(), 0));
			m_ObjList[enbossball].AddTail(new Cbossball(ePt.x + 60, ePt.y + 10, pboss->GetMontion(), 0));
			m_ObjList[enbossball].AddTail(new Cbossball(ePt.x + 70, ePt.y + 10, pboss->GetMontion(), -1));
		}

	}
	//敌机子弹炸掉战机
	POSITION bPos1 = NULL, bPos2 = NULL;
	CRect mRect = m_pMe->GetRect();
	for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//添加爆炸效果
			m_ObjList[enEnemy].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);

			//删除子弹
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;

			//战机生命值-1
			if(wudi==0)
			my_hp--;
			//删除战机
			if (my_hp <= 0)
			{
				delete m_pMe;
				m_pMe = NULL;
				break;
			}
		}
	}

	//战机导弹炸掉敌机
	POSITION mPos1 = NULL, mPos2 = NULL;
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//删除敌机
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
				my_grade += 10;
				break;

			}
		}
	}
	//战机必杀炸掉敌机
	POSITION mPosss1 = NULL, mPosss2 = NULL;
	for (mPosss1 = m_ObjList[enzidan].GetHeadPosition(); (mPosss2 = mPosss1) != NULL;)
	{
		CZidan* pBomb = (CZidan*)m_ObjList[enzidan].GetNext(mPosss1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				//删除导弹
				m_ObjList[enzidan].RemoveAt(mPosss2);
				delete pBomb;

				//删除敌机
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
				my_grade += 10;
				break;

			}
		}
	}
	//boss 子弹击中战机
	if (m_pMe != NULL)

	{
		POSITION bPos3 = NULL, bPos4 = NULL;
		CRect mRect3 = m_pMe->GetRect();
		for (bPos3 = m_ObjList[enbossball].GetHeadPosition(); (bPos4 = bPos3) != NULL;)
		{
			Cbossball* pbossball = (Cbossball*)m_ObjList[enbossball].GetNext(bPos3);
			CRect bRect1 = pbossball->GetRect();
			CRect tmpRect3;
			if (tmpRect3.IntersectRect(&bRect1, mRect3))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect3.left, mRect3.top)
				);

				//删除子弹
				m_ObjList[enbossball].RemoveAt(bPos4);
				delete pbossball;
				if (wudi == 0)
				{
					--my_hp;
					--my_hp;
				}
				if (my_hp <= 0)
				{
					delete m_pMe;
					m_pMe = NULL;
					break;
				}


			}
		}
	}
	//战机吃血瓶
	if (m_pMe != NULL)
	{
		POSITION tPos1 = NULL, tPos2 = NULL;
		CRect tRect = m_pMe->GetRect();
		for (tPos1 = m_ObjList[enTool].GetHeadPosition(); (tPos2 = tPos1) != NULL;)
		{
			Ctool* tool = (Ctool*)m_ObjList[enTool].GetNext(tPos1);
			CRect bRect7 = tool->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&tRect, bRect7))
			{

				//删除血瓶
				m_ObjList[enTool].RemoveAt(tPos2);
				my_hp++;
				xueping = 1;
				delete tool;
				daoju = 0;

			}
		}
	}
	//战机吃蓝瓶
	if (m_pMe != NULL)
	{
		POSITION tPoss1 = NULL, tPoss2 = NULL;
		CRect tRect = m_pMe->GetRect();
		for (tPoss1 = m_ObjList[enlanping].GetHeadPosition(); (tPoss2 = tPoss1) != NULL;)
		{
			Clanping* lanping2 = (Clanping*)m_ObjList[enlanping].GetNext(tPoss1);
			CRect bRect7 = lanping2->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&tRect, bRect7))
			{

				//删除蓝瓶
				m_ObjList[enlanping].RemoveAt(tPoss2);
				my_zidan++;
				delete lanping2;
				lanping = 0;

			}
		}
	}
	//战机吃必杀瓶
	if (m_pMe != NULL)
	{
		POSITION tPosss1 = NULL, tPosss2 = NULL;
		CRect tRect = m_pMe->GetRect();
		for (tPosss1 = m_ObjList[enbishaping].GetHeadPosition(); (tPosss2 = tPosss1) != NULL;)
		{
			Cbishaping* bishaping2 = (Cbishaping*)m_ObjList[enbishaping].GetNext(tPosss1);
			CRect bRect7 = bishaping2->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&tRect, bRect7))
			{

				//删除必杀瓶
				m_ObjList[enbishaping].RemoveAt(tPosss2);
				bisha++;
				delete bishaping2;
				bishaping = 0;

			}
		}
	}
	//敌机撞毁我方战机
	if (m_pMe != NULL)
	{
		POSITION tPos1 = NULL, tPos2 = NULL;
		CRect tRect = m_pMe->GetRect();
		for (tPos1 = m_ObjList[enEnemy].GetHeadPosition(); (tPos2 = tPos1) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(tPos1);
			CRect bRect5 = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&tRect, bRect5))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(tRect.left, tRect.top)
				);
				//删除敌机
				m_ObjList[enEnemy].RemoveAt(tPos2);
				delete pEnemy;
				//删除战机
				if(wudi==0)
				--my_hp;
				if (my_hp <= 0)
				{
					delete m_pMe;
					m_pMe = NULL;

					break;
				}
			}
		}
	}
	//战机导弹击中boss机
	POSITION mposs1 = NULL, mposs2 = NULL;
	for (mposs1 = m_ObjList[enBomb].GetHeadPosition(); (mposs2 = mposs1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mposs1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enBossplane].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CBossplane* pBossplane = (CBossplane*)m_ObjList[enBossplane].GetNext(ePos1);

			CRect mRect = pBossplane->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mposs2);
				delete pBomb;
				//boss机掉血,分数增加
				if (my_zidan > 5)
					pBossplane->bo_hp -= my_zidan - 5;
				else
					pBossplane->bo_hp--;
				my_grade += 10;
				//删除boss机
				if (pBossplane->bo_hp <= 0)
				{
						m_ObjList[enBossplane].RemoveAt(ePos2);
					delete pBossplane;
				}
				break;
			}
		}
	}
	//战机必杀击中boss机
	POSITION mPoss1 = NULL, mPoss2 = NULL;
	for (mPoss1 = m_ObjList[enzidan].GetHeadPosition(); (mPoss2 = mPoss1) != NULL;)
	{
		CZidan* pZidan = (CZidan*)m_ObjList[enzidan].GetNext(mPoss1);
		CRect bRect = pZidan->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enBossplane].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CBossplane* pBossplane = (CBossplane*)m_ObjList[enBossplane].GetNext(ePos1);

			CRect mRect = pBossplane->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				//删除导弹
				m_ObjList[enzidan].RemoveAt(mPoss2);
				delete pZidan;
				//boss机掉血,分数增加
				pBossplane->bo_hp-=2;
				my_grade += 50;
				//删除boss机
				if (pBossplane->bo_hp <= 0)
				{
					m_ObjList[enBossplane].RemoveAt(ePos2);
					delete pBossplane;
				}
				break;
			}
		}
	}
}
void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	//刷新游戏帧画面: 在内存DC上绘图
	UpdateFrame(m_pMemDC);
	if ((background111 != GAME_HEIGHT))
		background111 += 3;
	else
		background111 = 0;

	AI();

	CView::OnTimer(nIDEvent);

	AI();
	
	CView::OnTimer(nIDEvent);
}



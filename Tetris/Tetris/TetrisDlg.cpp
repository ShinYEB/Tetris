
// TetrisDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Tetris.h"
#include "TetrisDlg.h"
#include "afxdialogex.h"
#include "algorithm"
#include "iostream"
#include "string"
#include "cmath"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTetrisDlg 대화 상자



CTetrisDlg::CTetrisDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TETRIS_DIALOG, pParent)
	//, Level(_T(""))
	//, Score(_T(""))
	, s_score(_T("0"))
	, s_level(_T("1"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTetrisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_STATIC_LEVEL, Level);
	//  DDX_Text(pDX, IDC_STATIC_SCORE, Score);
	DDX_Control(pDX, IDC_STATIC_LEVEL, m_Level);
	DDX_Control(pDX, IDC_STATIC_SCORE, m_Score);
	DDX_Text(pDX, IDC_STATIC_SCORE, s_score);
	DDX_Text(pDX, IDC_STATIC_LEVEL, s_level);
}

BEGIN_MESSAGE_MAP(CTetrisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTetrisDlg 메시지 처리기

BOOL CTetrisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTetrisDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTetrisDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
	}

	vector<CRect> tempv;
	CRect background(0, 0, 400, 440);
	dc.FillSolidRect(background, RGB(100, 100, 100));
	for (int i = 0; i < 22; i++)
	{
		board.push_back(vector<int>(12, 0));

		tempv.clear();
		for (int j = 0; j < 20; j++)
		{
			CRect tempRect;
			tempv.push_back(tempRect);
			tempv[j].SetRect(20 * j, 20 * i, 19 + 20 * j, 19 + 20 * i);
			dc.FillSolidRect(tempv[j], RGB(50, 50, 50));
		}
		blocks.push_back(tempv);

	}

	{ // UI
		CRect backgroundIn(20, 20, 219, 419);
		dc.FillSolidRect(backgroundIn, RGB(25, 25, 25));

		CRect MiddleLine(240, 0, 259, 440);
		dc.FillSolidRect(MiddleLine, RGB(10, 10, 10));

		CRect backgroundNext(280, 140, 379, 419);
		dc.FillSolidRect(backgroundNext, RGB(25, 25, 25));

		for (int i = 0; i < 14; i++)
		{
			tempv.clear();
			for (int j = 0; j < 5; j++)
			{
				CRect tempRect;
				tempv.push_back(tempRect);
				tempv[j].SetRect(280 + 20 * j, 140 + 20 * i, 299 + 20 * j, 159 + 20 * i);
				dc.FillSolidRect(tempv[j], RGB(10, 10, 10));
			}
			nextBlock.push_back(tempv);
		}
	}

	if (newBlock)
	{
		makeBlock();
		End();
	}

	{ // Next Blocks
		for (int i = 0; i < 3; i++)
		{
			tempv.clear();
			for (int j = 0; j < 3; j++)
			{
				CRect tempRect;
				tempv.push_back(tempRect);
				tempv[j].SetRect(300 + 20 * j, 180 + 20 * i, 320 + 20 * j, 200 + 20 * i);

				if (category[categoryNext[0]][i][j] == 1)
					dc.FillSolidRect(tempv[j], colors[colorNext[0]]);

			}
			firstBlock.push_back(tempv);
		}

		for (int i = 0; i < 3; i++)
		{
			tempv.clear();
			for (int j = 0; j < 3; j++)
			{
				CRect tempRect;
				tempv.push_back(tempRect);
				tempv[j].SetRect(300 + 20 * j, 260 + 20 * i, 320 + 20 * j, 280 + 20 * i);

				if (category[categoryNext[1]][i][j] == 1)
					dc.FillSolidRect(tempv[j], colors[colorNext[1]]);

			}
			secondBlock.push_back(tempv);
		}

		for (int i = 0; i < 3; i++)
		{
			tempv.clear();
			for (int j = 0; j < 3; j++)
			{
				CRect tempRect;
				tempv.push_back(tempRect);
				tempv[j].SetRect(300 + 20 * j, 340 + 20 * i, 320 + 20 * j, 360 + 20 * i);

				if (category[categoryNext[2]][i][j] == 1)
					dc.FillSolidRect(tempv[j], colors[colorNext[2]]);

			}
			thirdBlock.push_back(tempv);
		}
	}

	for (int i = 0; i < 20; i++)
	{
		board.push_back(vector<int>(12, 0));

		tempv.clear();
		for (int j = 0; j < 10; j++)
		{
			CRect tempRect;
			tempv.push_back(tempRect);
			tempv[j].SetRect(20 + 20 * j, 20 + 20 * i, 39 + 20 * j, 39 + 20 * i);
			dc.FillSolidRect(tempv[j], colors[board[i][j + 1]]);
		}
		blocks.push_back(tempv);

	}
	board.push_back(vector<int>(12, 0));

	// 랜덤으로 생성된 블럭 화면에 출력함
	for (int i = 0; i < 3; i++)
	{
		tempv.clear();
		for (int j = 0; j < 3; j++)
		{
			CRect tempRect;
			tempv.push_back(tempRect);
			tempv[j].SetRect(20 + 20 * blockx[i][j] + pointx * 20, 20 + 20 * blocky[i][j] + pointy * 20,
				39 + 20 * blockx[i][j] + pointx * 20, 39 + 20 * blocky[i][j] + pointy * 20);

			if (block[i][j] == 1)
				dc.FillSolidRect(tempv[j], colors[PresentColor]);

		}
		presentBlock.push_back(tempv);
	}

	if(!isEnd)
		SetTimer(1, 1100 / pow(1.1, _ttoi(s_level)), NULL);

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTetrisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CTetrisDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_LEFT && isMove('l'))
		{
			pointx--;
		}
		if (pMsg->wParam == VK_RIGHT && isMove('r'))
		{
			pointx++;
		}
		if (pMsg->wParam == VK_UP && isMove('d'))
		{
			while (isMove('d'))
			{
				pointy++;
			}
		}
		if (pMsg->wParam == VK_DOWN && isMove('d'))
		{
			pointy++;
		}
		if (pMsg->wParam == VK_SPACE)
		{
			int tempblock_ix[3][3] = { {blockx[2][0], blockx[1][0], blockx[0][0]},
									   {blockx[2][1], blockx[1][1], blockx[0][1]},
									   {blockx[2][2], blockx[1][2], blockx[0][2]} };

			int tempblock_iy[3][3] = { {blocky[2][0], blocky[1][0], blocky[0][0]},
									   {blocky[2][1], blocky[1][1], blocky[0][1]},
									   {blocky[2][2], blocky[1][2], blocky[0][2]} };

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
				{
					blockx[i][j] = tempblock_ix[i][j];
					blocky[i][j] = tempblock_iy[i][j];
				}


		}
		Invalidate();

	}

	return CDialogEx::PreTranslateMessage(pMsg);
}



bool CTetrisDlg::isMove(char p)
{
	if (p == 'u')
	{

	}
	else if (p == 'd')
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if ((block[blocky[i][j]][blockx[i][j]] == 1 && board[i + pointy + 1][j + pointx + 1] != 0) || (i + pointy > 18 && block[blocky[i][j]][blockx[i][j]] == 1))
					return false;
			}
		}
	}
	else if (p == 'l')
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if ((block[blocky[i][j]][blockx[i][j]] == 1 && board[i + pointy][j + pointx] != 0) || (j + pointx < 1 && block[blocky[i][j]][blockx[i][j]] == 1))
					return false;
			}
		}
	}
	else if (p == 'r')
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if ((block[blocky[i][j]][blockx[i][j]] == 1 && board[i + pointy][j + pointx + 2] != 0) || (j + pointx > 8 && block[blocky[i][j]][blockx[i][j]] == 1))
					return false;
			}
		}
	}

	return true;
}

void CTetrisDlg::makeBlock()
{

	if (colorNext[0] == 0)
	{
		srand(time(NULL));
		for (int i = 0; i < 3; i++)
		{
			colorNext[i] = rand() % 7 + 1;
			categoryNext[i] = rand() % 6;
		}
	}

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (block[i][j] == 1)
				board[blocky[i][j] + pointy][blockx[i][j] + pointx + 1] = PresentColor;


	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			block[i][j] = 0;
			blockx[i][j] = i;
			blocky[i][j] = j;
		}

	pointx = 3;
	pointy = 0;

	PresentCategory = categoryNext[0];
	PresentColor = colorNext[0];

	categoryNext[0] = categoryNext[1];
	categoryNext[1] = categoryNext[2];
	categoryNext[2] = rand() % 6;

	colorNext[0] = colorNext[1];
	colorNext[1] = colorNext[2];
	colorNext[2] = rand() % 7 + 1;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			block[i][j] = category[PresentCategory][i][j];

	isMakeLine();
	LevelUp();
	newBlock = false;
}



void CTetrisDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);

	switch (nIDEvent)
	{
	case 1:
		if (isMove('d'))
			pointy++;
		
		else
			newBlock = true;
		
		Invalidate();
		break;
	}
}

void CTetrisDlg::isMakeLine()
{
	bool check;
	vector<int> isNotLine;
	vector<vector<int>> tempboard;

	

	for (int i = 0; i < 20; i++)
	{
		check = true;
		for (int j = 1; j < 11; j++)
			if (board[i][j] == 0)
				check = false;
		if (!check)
			isNotLine.push_back(i);
	}

	string s = to_string(_ttoi(s_score) + (20 - isNotLine.size()) * 10);
	s_score = s.c_str();
	UpdateData(false);

	if (isNotLine.size() != 20)
	{
		for (int i = 0; i < 20 - isNotLine.size(); i++)
			tempboard.push_back(vector<int>(12, 0));
		

		for (int i = 0; i < isNotLine.size(); i++)
			tempboard.push_back(board[isNotLine[i]]);

		tempboard.push_back(vector<int>(12, 0));


		for(int i=0; i<20; i++)
			for (int j = 1; j < 11; j++)
			{
				board[i][j] = tempboard[i][j];
			}
	}
}

void CTetrisDlg::LevelUp()
{
	if (_ttoi(s_score) > _ttoi(s_level) * 100)
	{
		string s = to_string(_ttoi(s_level) + 1);
		s_level = s.c_str();
		UpdateData(false);
	}
}

bool CTetrisDlg::End()
{
	bool temp = false;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (board[i][j + 3] != 0)
				temp = true;
		
	if (temp)
		isEnd = true;

	return temp;
}


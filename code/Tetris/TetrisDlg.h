
// TetrisDlg.h: 헤더 파일
//

#pragma once

#include <vector>
#include <time.h>

using namespace std;

// CTetrisDlg 대화 상자
class CTetrisDlg : public CDialogEx
{
private:

	vector<vector<CRect>> blocks;
	vector<vector<int>> board;
	vector<vector<CRect>> presentBlock;
	vector<vector<CRect>> nextBlock;
	vector<vector<CRect>> firstBlock;
	vector<vector<CRect>> secondBlock;
	vector<vector<CRect>> thirdBlock;

	int block[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	int blockx[3][3] = { {0, 1, 2}, {0, 1, 2}, {0, 1, 2} };
	int blocky[3][3] = { {0, 0, 0}, {1, 1, 1}, {2, 2, 2} };

	int line[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };

	COLORREF colors[9] = { RGB(10, 10, 10),  RGB(255, 0, 0), RGB(255, 50, 0), RGB(255, 255, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(0, 5, 255), RGB(100, 0, 255), RGB(255, 255, 255) };
	int category[6][3][3] = { {{0, 0, 0},
							   {1, 1, 1},
							   {0, 1, 0}},
							  {{0, 1, 1},
							   {1, 1, 0},
							   {0, 0, 0}},
							  {{1, 1, 0},
							   {0, 1, 1},
							   {0, 0, 0}},
							  {{1, 0, 0},
							   {1, 1, 1},
							   {0, 0, 0}},
							  {{0, 0, 1},
							   {1, 1, 1},
							   {0, 0, 0}},
							  {{1, 1, 0},
							   {1, 1, 0},
							   {0, 0, 0}} };

	bool newBlock = true;
	bool setBlock = false;
	int pointx = 0, pointy = 0;
	int PresentCategory = 0;
	int PresentColor = 0;

	int categoryNext[3] = { 0, 0, 0 };
	int colorNext[3] = { 0, 0, 0 };
// 생성입니다.
public:
	CTetrisDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TETRIS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	bool isMove(char p);
	void makeBlock();

};

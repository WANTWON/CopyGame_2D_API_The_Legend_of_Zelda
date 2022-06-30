// Default.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "API.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND	g_hWnd;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);		// 창 생성 시 각종 외관적인 디자인을 담당하는 함수
BOOL                InitInstance(HINSTANCE, int);			// 창 생성 메세지
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);	// 윈도우 메세지를 처리하는 중앙 함수

															// TSTR :  유니코드, 아스키코드 모두 호환하는 WINDOW의 TCHAR로 만든 STRING 클래스
															// LP : 포인터를 의미
															// LPTSTR : 문자열 포인터를 의미


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,				// 메모리에 할당되는 실체, 즉 객체, 현재 프로그램의 고유 식별 번호
	_In_opt_ HINSTANCE hPrevInstance,		// 전에 실행되었던 인스턴스으 핸들이 넘어온다, 없을 경우 null로 채워짐(win32기반에서는 항상 null, 단지 호환성을 위해 존재)
	_In_ LPWSTR    lpCmdLine,			//	문자열의 지원 형식
	_In_ int       nCmdShow)			// 실행한 창의 스타일(모양 / 최소화 모양, 최대화 모양 등)인자 값이 자동으로 채워짐
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TEST, szWindowClass, MAX_LOADSTRING);

	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST));

	MSG msg;
	msg.message = WM_NULL;

	srand(unsigned(time(NULL)));
	CMainGame*		pMainGame = new CMainGame;
	pMainGame->Initialize();

	DWORD		dwTime = GetTickCount();

	// 기본 메시지 루프입니다.
	while (true)
	{
		// 메세지가 있으면 true, 메시지가 없으면 false 를 리턴

		// PM_REMOVE : 메세지 큐로부터 메세지를 읽어옴과 동시에 메세지 큐에서 메세지를 제거.
		// PM_NOREMOVE : 메세지 큐로부터 메세지가 존재하는지만 파악하고 메세지를 가져오지는 않음.

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			// TranslateAccelerator : 메뉴 기능의 단축키가 제대로 작동하도록 검사하는 함수
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg); // 키보드 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록 해줌
				DispatchMessage(&msg);	// 시스템 메세지 큐에서 꺼낸 메세지를 프로그램의 메세지 처리 함수(WndProc)로 전달하는 기능
			}
		}
		else
		{
			if (dwTime + 5 < GetTickCount())
			{
				pMainGame->Update();
				pMainGame->Late_Update();
				pMainGame->Render();

				dwTime = GetTickCount();
			}

			/*pMainGame->Update();
			pMainGame->Late_Update();
			pMainGame->Render();*/

		}
	}

	if (nullptr != pMainGame)
	{
		delete pMainGame;
		pMainGame = nullptr;
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW );
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	RECT	rc{ 0, 0 , WINCX, WINCY };

	//  최종적인 RC = rc + 기본 왼도우 창 스타일 + 메뉴 바 사이즈 고려 여부
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hWnd = CreateWindowW(szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW,
		100, 100,	// 창이 생성되는 left, top위 위치
		rc.right - rc.left,
		rc.bottom - rc.top,	// 창의 가로, 세로 사이즈
		nullptr, nullptr,
		hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	g_hWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(g_hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}

		break;

		// DC : 출력에 관한 정보를 담는 구조체, 그리기를 담당하는 도화지 역할을 하는 메모리
		// DC는 GDI가 관리를 하며, 어떤 포인트, 선의 색상, 굵기, 무늬 등에 대한 정보를 가진다.

		// 윈도우의 기본 구성 라이브러리

		/*1. 커널(KERNEL) : 메모리를 관리하고 프로그램을 실행시킴
		2. 유저(USER) : 유저 인터페이스와 윈도우 창을 관리
		3. GDI : 화면 처리와 그래픽을 담당*/

		// DC를 얻어오는 함수
		// BeginPaint 
		// GetDC
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


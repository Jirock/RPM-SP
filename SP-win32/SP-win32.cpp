// SP-win32.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "SP-win32.h"

#define MAX_LOADSTRING 100

//BOOL Rectangle(HDC hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);
//BOOL Polyline(HDC hdc, const POINT* lppt, int cPoints);
//BOOL PolylineTo(HDC hdc, const POINT* lppt, int cPoints);
//BOOL Ellipse(HDC hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);


//void ClientDraw(HWND hwnd, WPARAM wParam, LPARAM lParam) {
//	PAINTSTRUCT ps;
//	HDC hdc = BeginPaint(hwnd, &ps);
//
//	MoveToEx(hdc, 100, 100, NULL);
//	LineTo(hdc, 400, 100);
//	LineTo(hdc, 400, 200);
//	MoveToEx(hdc, 100, 100, NULL);
//	LineTo(hdc, 100, 100);
//
//	LOGBRUSH lb; // структура, описывающая заливку линии
//	lb.lbStyle = BS_SOLID; // стиль заливки - сплошной 
//	lb.lbColor = RGB(255, 0, 0); // цвет - красный 
//	lb.lbHatch = 0;
//
//	HGDIOBJ hPen = ExtCreatePen(PS_GEOMETRIC | PS_SOLID, 5, &lb, 0, NULL);
//	HGDIOBJ hPenOld = SelectObject(hdc, hPen);
//	DeleteObject(hPen);
//
//
//	SelectObject(hdc, hPenOld);
//	POINT Points[] = { 300,300, 350,300, 350,350, 200,300 }; 
//	Polyline(hdc, Points, 4);
//
//	Rectangle(hdc, 200, 20, 300, 50);
//	SelectObject(hdc, GetStockObject(GRAY_BRUSH));// выбираем кисть
//	Rectangle(hdc, 50, 200, 100, 300);
//
//	
//	SelectObject(hdc, GetStockObject(GRAY_BRUSH));
//	Ellipse(hdc, 50, 350, 150, 450);
//	SelectObject(hdc, GetStockObject(NULL_BRUSH));
//	Ellipse(hdc, 200, 350, 500, 450);
//
//	EndPaint(hwnd, &ps);
//}


void ClientDraw(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	MoveToEx(hdc, 100, 100, NULL);
	LineTo(hdc, 100, 500);


	EndPaint(hwnd, &ps);
}



// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SPWIN32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPWIN32));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}





//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPWIN32));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SPWIN32);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK
WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_MOUSEMOVE:
		// действия в ответ на перемещение мыши
		break;
	case WM_PAINT:
		ClientDraw(hwnd, wParam, lParam); break;
		break;
	case WM_DESTROY:
		// действия в ответ на уничтожение окна
		break;
		// и так далее
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}


// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

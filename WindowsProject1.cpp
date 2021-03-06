// WindowsProject1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WindowsProject1.h"

												///////////////////////////
struct Node
{
	int x, y;
	int nShift;
	int idDrawKind;
	int R;
	int G;
	int B;
	int penR;
	int penG;
	int penB;
};
enum DrawKind {RECTANGLE, ELLIPSE, POLIGON};
#define MAX_LOADSTRING 100
											  //////////////////////////////

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING] = L"TestWndClass_circaFeb25";            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
int SaveToFile(int nSize, struct pNodesAr, HWND hWnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;
	//msg.

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = CreateSolidBrush(RGB(210, 35, 160));// (HBRUSH)(COLOR_WINDOW + 7);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   //UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Node * pNodesAr = 0;
	static int nSize = 5;
	static int iCurind = 0;
	static DrawKind iDrawKind = RECTANGLE;

    switch (message)
    {
	case WM_CREATE:
		pNodesAr = new Node[nSize];
		break;
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
		// left-top-  right-bottom
	
		if(wParam & MK_LBUTTON)
		{
			HDC hDC = GetDC(hWnd);

			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			int nShift = 20;
			int R= rand() % 256;
			int G = rand() % 256;
			int B = rand() % 256;
			int penR = rand() % 256;
			int penG = rand() % 256;
			int penB = rand() % 256;

			//RECTANGLE, ELLIPSE
			HPEN hPen = CreatePen(PS_SOLID, 3, RGB(penR, penG, penB));
			HBRUSH hBr = CreateSolidBrush(RGB(R, G, B));

			HBRUSH hOldBr = (HBRUSH)SelectObject(hDC, hBr);
			HBRUSH hOldPen = (HBRUSH)SelectObject(hDC, hPen);
			switch (iDrawKind)
			{
			case RECTANGLE:
				Rectangle(hDC, x - nShift, y - nShift, x + nShift, y + nShift);
				break;
			case ELLIPSE:
				Ellipse(hDC, x - nShift, y - nShift, x + nShift, y + nShift);
				break;
			}
			
			if (iCurind == nSize)
			{				
				int nNewSize = nSize + nSize / 2;
				Node * pTemp = new Node[nNewSize];
				memcpy(pTemp, pNodesAr, sizeof(Node) * nSize);
				delete[] pNodesAr;
				pNodesAr = pTemp;
				nSize = nNewSize;
			}
			pNodesAr[iCurind].x = x;
			pNodesAr[iCurind].y = y;
			pNodesAr[iCurind].nShift = nShift;
			pNodesAr[iCurind].idDrawKind = iDrawKind;
			pNodesAr[iCurind].R = R;
			pNodesAr[iCurind].G = G;
			pNodesAr[iCurind].B = B;
			pNodesAr[iCurind].penR = penR;
			pNodesAr[iCurind].penG = penG;
			pNodesAr[iCurind].penB = penB;
			iCurind++;

			SelectObject(hDC, hOldBr);
			SelectObject(hDC, hOldPen);
			DeleteObject(hBr);
			DeleteObject(hPen);
			ReleaseDC(hWnd, hDC);
		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_ACTIONS_REDRAW:
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_DRAW_ELLIPSE:				
				iDrawKind = ELLIPSE;
				break;
			case ID_DRAW_RECTANGLE:
				iDrawKind = RECTANGLE;
				break;
			/*case ID_FILE_SAVE:
				SaveToFile(nSize, *pNodesAr, hWnd);*/
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			HBRUSH hBr; 
			HBRUSH hOldBr; 

			HPEN hPen; 
			HBRUSH hOldPen; 

		    if (pNodesAr != 0)
				for (int i = 0; i < iCurind; i++)
				{
					switch (pNodesAr[i].idDrawKind)
					{
					case RECTANGLE:
						hBr = CreateSolidBrush(RGB(pNodesAr[i].R, pNodesAr[i].G, pNodesAr[i].B));
						hOldBr = (HBRUSH)SelectObject(hdc, hBr);

						hPen = CreatePen(PS_SOLID, 3, RGB(pNodesAr[i].penR, pNodesAr[i].penG, pNodesAr[i].penB));
						hOldPen = (HBRUSH)SelectObject(hdc, hPen);
						
						Rectangle(hdc, pNodesAr[i].x - pNodesAr[i].nShift,
							pNodesAr[i].y - pNodesAr[i].nShift,
							pNodesAr[i].x + pNodesAr[i].nShift,
							pNodesAr[i].y + pNodesAr[i].nShift);
			
						SelectObject(hdc, hOldBr);
						SelectObject(hdc, hOldPen);
						DeleteObject(hBr);
						DeleteObject(hPen);

						break;
					case ELLIPSE:
						hBr = CreateSolidBrush(RGB(pNodesAr[i].R, pNodesAr[i].G, pNodesAr[i].B));
						hOldBr = (HBRUSH)SelectObject(hdc, hBr);

						hPen = CreatePen(PS_SOLID, 3, RGB(pNodesAr[i].penR, pNodesAr[i].penG, pNodesAr[i].penB));
						hOldPen = (HBRUSH)SelectObject(hdc, hPen);

						Ellipse(hdc, pNodesAr[i].x - pNodesAr[i].nShift,
							pNodesAr[i].y - pNodesAr[i].nShift,
							pNodesAr[i].x + pNodesAr[i].nShift,
							pNodesAr[i].y + pNodesAr[i].nShift);

						SelectObject(hdc, hOldBr);
						SelectObject(hdc, hOldPen);
						DeleteObject(hBr);
						DeleteObject(hPen);

						break;
					}		
				}
		
			EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
		delete[] pNodesAr;
        PostQuitMessage(0);
        break;
	
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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

//int SaveToFile(int nSize, Node pNodesAr, HWND hWnd)
//{
//	static int v; // # version of file
//	FILE * f;
//	errno_t err = _wfopen_s(&f,"file.txt", "wb");
//	if (f = NULL)
//	{
//		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//		return 0;
//	}
//
//}
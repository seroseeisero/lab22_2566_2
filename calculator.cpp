#include <windows.h>
#include <stdio.h>
/* This is where all the input to the window goes to */
char input1[28];
char input2[28];
HWND textfield,plusBtn,minusBtn,multiplyBtn,divisionBtn,textBox1,textBox2;
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_CREATE: {
			textfield = CreateWindow("STATIC","Please input two numbers ",WS_VISIBLE | WS_CHILD ,20,20,200,25,hwnd,NULL,NULL,NULL);
			
			plusBtn = CreateWindow("BUTTON","+",WS_VISIBLE|WS_CHILD |WS_BORDER,
			40,110,20,20,
			hwnd,(HMENU) 1,NULL,NULL);

			minusBtn = CreateWindow("BUTTON","-",WS_VISIBLE|WS_CHILD |WS_BORDER,
			80,110,20,20,
			hwnd,(HMENU) 2,NULL,NULL);

			multiplyBtn = CreateWindow("BUTTON","*",WS_VISIBLE|WS_CHILD |WS_BORDER,
			120,110,20,20,
			hwnd,(HMENU) 3,NULL,NULL);

			divisionBtn = CreateWindow("BUTTON","/",WS_VISIBLE|WS_CHILD |WS_BORDER,
			160,110,20,20,
			hwnd,(HMENU) 4,NULL,NULL);

			textBox1 = CreateWindow("EDIT"," ",WS_VISIBLE|WS_CHILD |WS_BORDER,
			20,50,200,25,
			hwnd,NULL,NULL,NULL);

			textBox2 = CreateWindow("EDIT"," ",WS_VISIBLE|WS_CHILD |WS_BORDER,
			20,80,200,25,
			hwnd,NULL,NULL,NULL);
			break;

		}
		case WM_COMMAND:{
			switch(LOWORD(wParam)){
				case 1:{
					float ip1,ip2;
					ip1 = GetWindowText(textBox1,&input1[0],28);
					ip2 = GetWindowText(textBox2,&input2[0],28);
					char ans[10] ;
					sprintf(ans, "%f", atof(input1)+atof(input2) );
					::MessageBox( hwnd,ans,"answer",MB_OK);
					break;
				}
				case 2:{
					float ip1,ip2;
					ip1 = GetWindowText(textBox1,&input1[0],28);
					ip2 = GetWindowText(textBox2,&input2[0],28);
					char ans[10] ;
					sprintf(ans, "%f", atof(input1)-atof(input2) );
					::MessageBox( hwnd,ans,"answer",MB_OK);
					break;
				}
				case 3:{
					float ip1,ip2;
					ip1 = GetWindowText(textBox1,&input1[0],28);
					ip2 = GetWindowText(textBox2,&input2[0],28);
					char ans[10] ;
					sprintf(ans, "%f", atof(input1)*atof(input2) );
					::MessageBox( hwnd,ans,"answer",MB_OK);
					break;
				}
				case 4:{
					float ip1,ip2;
					ip1 = GetWindowText(textBox1,&input1[0],28);
					ip2 = GetWindowText(textBox2,&input2[0],28);
					char ans[10] ;
					sprintf(ans, "%f", atof(input1)/atof(input2) );
					::MessageBox( hwnd,ans,"answer",MB_OK);
					break;
				}
			}
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+22);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE | WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
#include <windows.h>
#include <iostream>
#include <string>
#include "resource.h"

#include "kaho.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	Frame frame(hInstance, L"TestClName", e_frame_type::msg_based);
	//frame.addtr = WS_OVERLAPPED | WS_VISIBLE;
	//frame.manSet(WndProc);
	frame.size({600, 600});
	frame.title(L"Title xD");
	frame.icon(LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));
	frame.addtr = WS_VISIBLE | WS_OVERLAPPEDWINDOW;

	Button* bt = new Button(L"Abt");
	bt->cotr(200, 100, 100, 30);
	bt->hc = (HMENU) 101;
	bt->setAct([](LPARAM) {
		MessageBox(NULL, L"This is spaghetti lib!", L"About!", MB_OK);
		});
	frame.impl(bt);

	Text* bt2 = new Text(L"My shitty lib: ");
	bt2->cotr(60, 110, 100, 30);
	frame.impl(bt2);

	frame.gen();
	return frame.assemble();
}
#include "framebase.h"
#include <string>
#include "itr.h"

/*
	allowed class db:
	button
	static
	edit
	scrollbar
	combolbox
*/

std::map<HWND, Frame*> LINKER = std::map<HWND, Frame*>();
Frame* Frame::lastF = nullptr;

Frame::Frame(HINSTANCE hInst, LPCWSTR name, e_frame_type type) {
	this->inst = hInst;
	this->cName = name;
	this->type = type;
}

LPVOID CALLBACK Frame::gen() {
	this->cls.hInstance = this->inst;
	if (!this->bWndSet) {
		this->cls.lpfnWndProc = Frame::stratis;
		this->bWndSet = true;
	}
	this->cls.lpszClassName = this->cName;
	this->cls.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	return NULL;
}

LPVOID CALLBACK Frame::manSet(WNDPROC proc) {
	this->cls.lpfnWndProc = proc;
	this->bWndSet = true;
	return NULL;
}

LRESULT CALLBACK Frame::stratis(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_NCDESTROY) return DefWindowProc(hwnd, msg, wParam, lParam);
	Frame* fr = LINKER[hwnd];
	if (fr == NULL) {
		Frame::lastF->mHwnd = hwnd;
		LINKER[hwnd] = Frame::lastF;
		fr = Frame::lastF;
		Frame::lastF = nullptr;
	}
	return fr->wndF(msg, wParam, lParam);
}

LRESULT Frame::wndF(UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CREATE:
		//CreateWindow(L"dynamic", L"Txt", WS_CHILD | WS_VISIBLE, 0, 0, 50, 50, this->mHwnd, (HMENU)0, this->inst, NULL);
		for (size_t i = 0; i < this->vcomp.size(); i++) {
			vcomp[i]->reg(&this->mHwnd);
		}
		break;
	case WM_DESTROY:
		Frame::close(this->mHwnd, 0);
		break;
	case WM_PAINT:
		break;
	case WM_COMMAND:
		for (size_t i = 0; i < this->vcomp.size(); i++) {
			if (instanceof<kaho::Actable>(vcomp[i])) {
				kaho::Actable* ct = dynamic_cast<kaho::Actable*>(vcomp[i]);
				if (ct->hCode() == (HMENU) LOWORD(wParam)) {
					ct->act(lParam, this->mHwnd);
				}
			}
		}
		break;
	}
	return DefWindowProc(this->mHwnd, msg, wParam, lParam);
}

int CALLBACK Frame::assemble() {
	MSG msg;
	this->fclass = RegisterClass(&this->cls);
	lastF = this;
	if (this->addtr == 0x00000000000L) this->addtr = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	CreateWindow(this->cls.lpszClassName, this->fInf.title, addtr, 
		this->fInf.x, this->fInf.y, this->fInf.size.dx, this->fInf.size.dy, 0, 0, this->inst, NULL);
	
	//Main loop
	switch (this->type)
	{
	case e_frame_type::msg_based:
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		break;
	case e_frame_type::draw_based:
		break;
	}
	return (int) msg.wParam;
}

HMENU CALLBACK Frame::impl(kaho::IComponent* comp) {
	this->vcomp.push_back(comp);
	return (instanceof<kaho::Actable>(comp) ? dynamic_cast<kaho::Actable*>(comp)->hCode() : (HMENU) 0);
}

VOID Frame::size(DIM dimension) {
	this->fInf.size = dimension;
}

VOID Frame::title(LPCWSTR text) {
	this->fInf.title = text;
}

VOID Frame::icon(HICON icon) {
	this->cls.hIcon = icon;
}

LPVOID Frame::close(HWND hwnd, int code) {
	LINKER.erase(hwnd);
	PostQuitMessage(code);
	return NULL;
}
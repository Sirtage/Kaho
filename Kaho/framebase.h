#pragma once
#include <Windows.h>
#include <map>
#include "htc.h"
#include <vector>
#include "component.h"

extern enum e_frame_type : UINT {
	msg_based, frame_based, draw_based
};

typedef struct ABTF {
	LPCWSTR title;
	UINT x;
	UINT y;
	DIM size;
};

class Frame {
public:
	LONG addtr = 0x00000000000L;

	HWND mHwnd;
	static Frame* lastF;

	e_frame_type type;
	
	std::vector<Frame*> frames;
	VIC vcomp;

	ABTF fInf;
	WNDCLASS cls = { 0 };
	Frame(HINSTANCE, LPCWSTR, e_frame_type);

	int CALLBACK assemble();
	LPVOID manSet(WNDPROC);
	LPVOID CALLBACK gen();

	VOID size(DIM dim);
	VOID title(LPCWSTR text);
	VOID icon(HICON);

	HMENU CALLBACK impl(kaho::IComponent*);
protected:
	static LRESULT CALLBACK stratis(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LPVOID close(HWND, int);
	LRESULT wndF(UINT msg, WPARAM wParam, LPARAM lParam);

	BOOL bWndSet = false;

	ATOM fclass;
	LPCWSTR cName;
	HINSTANCE inst;
};

extern std::map<HWND, Frame*> LINKER;
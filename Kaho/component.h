#pragma once
#include <Windows.h>
#include "framebase.h"
#include <functional>

#include "htc.h"

namespace kaho {
	extern enum e_component_type : UINT {
		unid, button, text, edit
	};

	__interface IComponent
	{
	public:
		LPCWSTR cClass();
		e_component_type eType();
		BOOL reg(HWND* pHwnd);
	};

	class Styled {
	public:
		LONG wsStyle;
		LPARAM longPrs;

		VOID CALLBACK addit(LONG dl) {
			this->wsStyle = wsStyle | dl;
		}

		VOID CALLBACK setPrs(LPARAM lParam) {
			this->longPrs = lParam;
		}
	};

	class Actable : public IComponent {
	public:
		HMENU hc = (HMENU) 0;
		std::function<VOID(LPARAM, HWND&)> act = [](LPARAM, HWND&){};

		HMENU hCode() { return hc; }
		VOID setAct(std::function<VOID(LPARAM, HWND&)> ast) { this->act = ast; }
	};

	class Positioned {
	public:
		UINT x;
		UINT y;
		UINT w;
		UINT h;

		VOID cotr(UINT x, UINT y, UINT w, UINT h) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}

		VOID cotr(DIM pos, DIM size) {
			this->x = pos.dx;
			this->y = pos.dy;
			this->w = size.dx;
			this->h = size.dy;
		}
	};
	
	class Button : public Actable, public Positioned, public Styled {
	public:
		LPCWSTR title;
		Button(LPCWSTR title) {
			this->title = title;
		}
		Button() {}
		LPCWSTR cClass() override { return L"button"; }
		e_component_type eType() override { return e_component_type::button; }
		BOOL reg(HWND* pHwnd) override {
			auto atv = CreateWindow(this->cClass(), this->title, WS_CHILD | WS_VISIBLE | this->wsStyle, this->x, this->y, this->w, this->h, *pHwnd, this->hCode(), NULL, &this->longPrs);
			return atv != nullptr;
		}
	};

	class Text : public IComponent, public Positioned, public Styled {
	public:
		LPCWSTR inner;
		Text(LPCWSTR text) {
			this->inner = text;
		}
		Text() {};
		LPCWSTR cClass() override { return L"static"; }
		e_component_type eType() override { return e_component_type::button; }
		BOOL reg(HWND* pHwnd) override {
			auto atv = CreateWindow(this->cClass(), this->inner, WS_CHILD | WS_VISIBLE | this->wsStyle, this->x, this->y, this->w, this->h, *pHwnd, NULL, NULL, &this->longPrs);
			return atv != nullptr;
		}
	};

	class Editfield : public Actable, public Positioned, public Styled {
	public:
		LPCWSTR lDef = L"";
		Editfield(LPCWSTR deft) {
			this->lDef = deft;
		}
		Editfield() {}
		LPCWSTR cClass() override { return L"edit"; }
		e_component_type eType() override { return e_component_type::edit; }
		BOOL reg(HWND* pHwnd) override {
			auto atv = CreateWindow(this->cClass(), this->lDef, WS_CHILD | WS_VISIBLE | this->wsStyle, this->x, this->y, this->w, this->h, *pHwnd, this->hCode(), NULL, &this->longPrs);
			return atv != nullptr;
		}
	};
}

typedef std::vector<kaho::IComponent*> VIC;
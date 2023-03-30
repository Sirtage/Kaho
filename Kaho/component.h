#pragma once
#include <Windows.h>
#include "framebase.h"
#include <functional>

#include "htc.h"

namespace kaho {
	extern enum e_component_type : UINT {
		unid, button, text
	};

	__interface IComponent
	{
	public:
		LPCWSTR cClass();
		e_component_type eType();
		BOOL reg(HWND* pHwnd);
	};

	class Actable : public IComponent {
	public:
		HMENU hc = (HMENU) 0;
		std::function<VOID(LPARAM)> act = [](LPARAM){};

		HMENU hCode() { return hc; }
		VOID setAct(std::function<VOID(LPARAM)> ast) { this->act = ast; }
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
	
	class Button : public Actable, public Positioned {
	public:
		LPCWSTR title;
		Button(LPCWSTR title) {
			this->title = title;
		}
		Button() {}
		LPCWSTR cClass() override { return L"button"; }
		e_component_type eType() override { return e_component_type::button; }
		BOOL reg(HWND* pHwnd) override {
			auto atv = CreateWindow(this->cClass(), this->title, WS_CHILD | WS_VISIBLE, this->x, this->y, this->w, this->h, *pHwnd, this->hCode(), NULL, NULL);
			return atv != nullptr;
		}
	};

	class Text : public IComponent, public Positioned {
	public:
		LPCWSTR inner;
		Text(LPCWSTR text) {
			this->inner = text;
		}
		Text() {};
		LPCWSTR cClass() override { return L"static"; }
		e_component_type eType() override { return e_component_type::button; }
		BOOL reg(HWND* pHwnd) override {
			auto atv = CreateWindow(this->cClass(), this->inner, WS_CHILD | WS_VISIBLE, this->x, this->y, this->w, this->h, *pHwnd, NULL, NULL, NULL);
			return atv != nullptr;
		}
	};
}

typedef std::vector<kaho::IComponent*> VIC;
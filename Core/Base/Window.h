#pragma once

#include<iostream>

#include"./Types.h"
#include"./Application.h"
#include<functional>

struct WindowInfo
{
	int width, height;
	String title;

	WindowInfo() {}
	WindowInfo(int w, int h, String t): width(w), height(h), title(t) {}	

	WindowInfo operator=(const WindowInfo &winInfo)
	{
		this->width = winInfo.width;
		this->height = winInfo.height;
		this->title = winInfo.title;

		return *this;
	}	
};

namespace Abs
{
    class Window
    {
        public:
        Window() {}

        virtual void SetActive() = 0;
        virtual inline bool ShouldCloseWindow() = 0;
        virtual void SetColor(float r, float g, float b, float a) = 0;
        virtual void SwapFrameBuffer() = 0;
        inline iVec2 GetWindowSize() { return iVec2(m_wi.width, m_wi.height); }
        inline WindowInfo GetWindowInfo() { return m_wi; }
        inline dVec2 GetMousePos() {   return this->m_mouPos;  }
        void SetWindowInfo(WindowInfo &wi) {  m_wi = wi; }
        void SetKeySubscriber(String *subscriber) { m_lastStringScan = (m_keySubscriber=subscriber)? *subscriber : ""; }

        String *m_keySubscriber;
        String m_lastStringScan;
		Application *m_targetApp;
        WindowInfo m_wi;
        dVec2 m_mouPos;
    };
}
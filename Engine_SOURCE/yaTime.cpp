#include "yaTime.h"
#include "yaApplication.h"
#include "yaFontWrapper.h"
#include "..\\SEngine\\yaPlayScene.h"
#include "..\\SEngine\\yaBoss01Scene.h"

extern ya::Application application;

namespace ya
{
	double Time::mDeltaTime = 0.0l;
	double Time::mSecond = 0.0f;
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};

	void Time::Initiailize()
	{
		// CPU 고유 진동수 가져오기
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램이 처음 시작할때 진동수
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFrequency);

		double differnceFrequency = mCurFrequency.QuadPart - mPrevFrequency.QuadPart;

		mDeltaTime = differnceFrequency / mCpuFrequency.QuadPart;
		
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render()
	{
		mSecond += mDeltaTime;

		if (mSecond > 1.0f)
		{
			HWND hWnd = application.GetHwnd();

			wchar_t szFloat[50] = {};
			float FPS = 1.0f / (float)mDeltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d", (UINT)FPS);
			//int iLen = wcsnlen_s(szFloat, 50);
			SetWindowText(hWnd, szFloat);
			
			//TextOut(hdc, 0, 0, szFloat, 20);
			mSecond = 0.0f;
		}

		if (PlayScene::mHeart != 1000)// 불가능한 초기값인 경우, 씬 생성 안된 경우
		{
			std::wstring str0 = std::to_wstring(PlayScene::mHeart);
			std::wstring str1 = std::to_wstring(PlayScene::mHp);
			std::wstring str2 = std::to_wstring(PlayScene::mSp);

			wchar_t szFloat[50] = L"BIN";
			wcscpy_s(szFloat, str0.c_str());

			wchar_t szFloat2[50] = L"BIN2";
			wcscpy_s(szFloat2, str1.c_str());

			wchar_t szFloat3[50] = L"BIN3";
			wcscpy_s(szFloat3, str2.c_str());

			FontWrapper::DrawFont(szFloat, 170.f, 22.f, 90, FONT_RGBA(0, 255, 27, 255));
			FontWrapper::DrawFont(szFloat2, 280.f, 15.f, 50, FONT_RGBA(255, 185, 27, 255));
			FontWrapper::DrawFont(szFloat3, 310.f, 60.f, 50, FONT_RGBA(33, 155, 255, 255));
		}

		if (Boss01Scene::mHeart != 1000)// 불가능한 초기값인 경우, 씬 생성 안된 경우
		{
			std::wstring str0 = std::to_wstring(Boss01Scene::mHeart);
			std::wstring str1 = std::to_wstring(Boss01Scene::mHp);
			std::wstring str2 = std::to_wstring(Boss01Scene::mSp);

			wchar_t szFloat[50] = L"BIN";
			wcscpy_s(szFloat, str0.c_str());

			wchar_t szFloat2[50] = L"BIN2";
			wcscpy_s(szFloat2, str1.c_str());

			wchar_t szFloat3[50] = L"BIN3";
			wcscpy_s(szFloat3, str2.c_str());

			FontWrapper::DrawFont(szFloat, 170.f, 22.f, 90, FONT_RGBA(0, 255, 27, 255));
			FontWrapper::DrawFont(szFloat2, 280.f, 15.f, 50, FONT_RGBA(255, 185, 27, 255));
			FontWrapper::DrawFont(szFloat3, 310.f, 60.f, 50, FONT_RGBA(33, 155, 255, 255));
		}
	}
}

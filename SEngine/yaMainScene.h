#pragma once
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class MainScene : public Scene
	{
		enum class MenuNumber : int
		{
			StoryMode,
			NetworkGame,
			ExtraGameModex,
			UbisoftConnect,
			Achievements,
			Leaderboards,
			HelpNOptions,
			ExitGame,
		};

	public:
		MainScene();
		virtual ~MainScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		int mMenuNumber = 0;

		GameObject* mBG_MAIN_01 = nullptr;

		GameObject* mUI_MAIN_MENU = nullptr;
		GameObject* mUI_MAIN_MENU_BAR = nullptr;

		GameObject* mUI_MAIN_CHAR = nullptr;
		bool mUI_MAIN_CHAR_SizeState = true;// false 감소, true 증가

		GameObject* mBgm = nullptr;
		GameObject* mEffect = nullptr;
		GameObject* mEnter = nullptr;

		GameObject* mDirectionalLight = nullptr;
		GameObject* mPointLight = nullptr;
		bool mEnterLight = false;
		bool mExitLight = false;
		float mMaxRadius = 22.0f;// 최대 반지름
		float mMinRadius = 0.05f;// 최소 반지름
		float mCurrentRadius = 0.0f;// 현재 반지름
		float totalTimeEnter = 0.0f;// Enter 누적 시간
		float totalTimeExit = 0.0f;// Exit 누적 시간
		float duration = 3.0f;// 전체 소요 시간 (초)
	};
}
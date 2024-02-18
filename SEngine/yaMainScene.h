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
	};
}
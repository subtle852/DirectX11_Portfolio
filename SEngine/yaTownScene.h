#pragma once
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class TownScene : public Scene
	{
	public:
		TownScene();
		virtual ~TownScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* mBG_TOWN_MAP;
		GameObject* mPlayer;

		GameObject* mBgm;
		GameObject* mEffect;
		GameObject* mEnter;

		GameObject* mDirectionalLight = nullptr;
		GameObject* mPointLight = nullptr;
		bool mEnterLight = false;
		bool mExitLight = false;
		float mMaxValue = 0.95f;// 최대값
		float mMinValue = 0.05f;// 최소값
		float mCurrentValue = 0.0f;// 현재값
		float totalTimeEnter = 0.0f;// Enter 누적 시간
		float totalTimeExit = 0.0f;// Exit 누적 시간
		float duration = 3.0f;// 전체 소요 시간 (초)
	};
}
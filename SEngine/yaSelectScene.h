#pragma once
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class SelectScene : public Scene
	{
	public:
		SelectScene();
		virtual ~SelectScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* mBG_SELECT_CURTAIN = nullptr;
		GameObject* mArrow = nullptr;

		GameObject* mChar01 = nullptr;
		GameObject* mChar02 = nullptr;
		GameObject* mChar03 = nullptr;
		GameObject* mChar04 = nullptr;

		unsigned int mNumber = 0;

		GameObject* mBgm;
		GameObject* mEffect;
		GameObject* mEnter;

		GameObject* mDirectionalLight = nullptr;
		GameObject* mPointLight = nullptr;
		bool mEnterLight = false;
		bool mExitLight = false;
		float mMaxValue = 0.8f;// 최대값
		float mMinValue = 0.05f;// 최소값
		float mCurrentValue = 0.0f;// 현재값
		float totalTimeEnter = 0.0f;// Enter 누적 시간
		float totalTimeExit = 0.0f;// Exit 누적 시간
		float duration = 3.0f;// 전체 소요 시간 (초)
	};
}
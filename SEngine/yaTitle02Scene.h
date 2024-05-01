#pragma once
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class Title02Scene : public Scene
	{
	public:
		Title02Scene();
		virtual ~Title02Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* mBG_TITLE02_01 = nullptr;
		GameObject* mUI_TITLE02_ENTER = nullptr;
		bool mUI_TITLE02_ENTER_SizeState = true;// false 감소, true 증가

		GameObject* mBgm;
		GameObject* mEffect;

		GameObject* mDirectionalLight;
		GameObject* mPointLight;
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
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
		float mMaxValue = 0.95f;// �ִ밪
		float mMinValue = 0.05f;// �ּҰ�
		float mCurrentValue = 0.0f;// ���簪
		float totalTimeEnter = 0.0f;// Enter ���� �ð�
		float totalTimeExit = 0.0f;// Exit ���� �ð�
		float duration = 3.0f;// ��ü �ҿ� �ð� (��)
	};
}
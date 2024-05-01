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
		bool mUI_TITLE02_ENTER_SizeState = true;// false ����, true ����

		GameObject* mBgm;
		GameObject* mEffect;

		GameObject* mDirectionalLight;
		GameObject* mPointLight;
		bool mEnterLight = false;
		bool mExitLight = false;
		float mMaxRadius = 22.0f;// �ִ� ������
		float mMinRadius = 0.05f;// �ּ� ������
		float mCurrentRadius = 0.0f;// ���� ������
		float totalTimeEnter = 0.0f;// Enter ���� �ð�
		float totalTimeExit = 0.0f;// Exit ���� �ð�
		float duration = 3.0f;// ��ü �ҿ� �ð� (��)
	};
}
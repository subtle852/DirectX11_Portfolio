#pragma once
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class Boss01Scene : public Scene
	{
	public:
		Boss01Scene();
		virtual ~Boss01Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		static bool IsPlayerExist()
		{
			if (mRamona != nullptr)
				return true;

			return false;
		}
		static bool IsPlayerDead()
		{
			if (mRamona != nullptr)
				return mRamonaDead;
		}
		static Vector3 GetPlayerPosition()
		{
			if (mRamona != nullptr)
				return mRamonaPos;
		}
		static eDirection GetPlayerDirection()
		{
			if (mRamona != nullptr)
				return mRamonaDir;
		}
		static ePlayerState GetPlayerState()
		{
			if (mRamona != nullptr)
				return mRamonaState;
		}

	private:
		GameObject* mBG_STAGE01_BOSS01 = nullptr;
		GameObject* mUI_STAGE01_STATE = nullptr;

		static GameObject* mRamona;
		static Vector3 mRamonaPos;
		static eDirection mRamonaDir;
		static ePlayerState mRamonaState;
		static bool mRamonaDead;

		GameObject* mBoss01 = nullptr;

		GameObject* mDirectionalLight = nullptr;
		GameObject* mPointLight = nullptr;
		bool mEnterLight = false;
		bool mExitLight = false;
		float mMaxValue = 1.0f;// �ִ밪
		float mMinValue = 0.05f;// �ּҰ�
		float mCurrentValue = 0.0f;// ���簪
		float totalTimeEnter = 0.0f;// Enter ���� �ð�
		float totalTimeExit = 0.0f;// Exit ���� �ð�
		float duration = 3.0f;// ��ü �ҿ� �ð� (��)

		GameObject* mBgm;
		unsigned int mBgmPhase = 0;
		GameObject* mExitSound;

		bool mPhase02Started = false;
		bool mPhase04Started = false;


		GameObject* mMainCamera;

	public:
		static int mHeart;
		static int mHp;
		static int mSp;

		static int mAttributeTmp[3];
	};
}
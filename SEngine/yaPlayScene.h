#pragma once
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class RamonaScript;

	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

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
			if(mRamona != nullptr)
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
		void InitializeEnemy();

	private:
		GameObject* mBG_STAGE01_01 = nullptr;
		GameObject* mUI_STAGE01_STATE = nullptr;

		static GameObject* mRamona;
		static Vector3 mRamonaPos;
		static eDirection mRamonaDir;
		static ePlayerState mRamonaState;
		static bool mRamonaDead;

		GameObject* mEnemy01 = nullptr;
		GameObject* mEnemy02 = nullptr;
		GameObject* mEnemy03 = nullptr;

		GameObject* mEnemy04 = nullptr;
		GameObject* mEnemy05 = nullptr;
		GameObject* mEnemy06 = nullptr;

		GameObject* mEnemy07 = nullptr;
		GameObject* mEnemy08 = nullptr;

		GameObject* mEnemy09 = nullptr;

		GameObject* mEnemy10 = nullptr;
		GameObject* mEnemy11 = nullptr;
		GameObject* mEnemy12 = nullptr;
		GameObject* mEnemy13 = nullptr;

		GameObject* mMainCamera = nullptr;

		//GameObject* mBoss01 = nullptr;

		unsigned int mPhase = 0;

		float mPhase05Time = 3.0f;

		// static Vector3 mTargetPos;
		// 일반적인 상황에서는 플레이어
		// 특정 상황에서는 변경

		GameObject* mBgm;
		GameObject* mExitSound;

		GameObject* mDirectionalLight = nullptr;
		GameObject* mPointLight = nullptr;
		bool mEnterLight = false;
		bool mExitLight = false;
		float mMaxValue = 1.0f;// 최대값
		float mMinValue = 0.05f;// 최소값
		float mCurrentValue = 0.0f;// 현재값
		float totalTimeEnter = 0.0f;// Enter 누적 시간
		float totalTimeExit = 3.0f;// Exit 누적 시간
		float duration = 3.0f;// 전체 소요 시간 (초)

	public:
		static int mHeart;
		static int mHp;
		static int mSp;
	};
}

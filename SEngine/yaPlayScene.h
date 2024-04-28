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
		GameObject* mBG_STAGE01_01 = nullptr;
		GameObject* mUI_STAGE01_STATE = nullptr;

		static GameObject* mRamona;
		static Vector3 mRamonaPos;
		static eDirection mRamonaDir;
		static ePlayerState mRamonaState;
		static bool mRamonaDead;

		GameObject* mLuke01 = nullptr;
		GameObject* mLuke02 = nullptr;
		GameObject* mLuke03 = nullptr;

		GameObject* mBoss01 = nullptr;


		// static Vector3 mTargetPos;
		// 일반적인 상황에서는 플레이어
		// 특정 상황에서는 변경
	};
}

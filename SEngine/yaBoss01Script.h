#pragma once
#include "yaScript.h"
#include "yaEnemyScript.h"

namespace ya
{
	class Boss01Script : public EnemyScript
	{
		enum class eBoss01State
		{
			// Appear / Disappear
			L_Appear,
			R_Appear,
			L_AppearWait,
			R_AppearWait,
			L_DisAppear,
			R_DisAppear,

			// Basic
			L_Idle,
			R_Idle,
			L_Walk,
			R_Walk,
			L_Run,
			R_Run,

			L_Downed,
			R_Downed,
			L_GetUp,
			R_GetUp,

			// 방어
			L_Guard,
			R_Guard,

			// 공격
			L_AttackPunch,
			R_AttackPunch,
			L_AttackJumpPunchStr,
			R_AttackJumpPunchStr,
			L_AttackJumpPunchIng,
			R_AttackJumpPunchIng,
			L_AttackKick,
			R_AttackKick,
			L_AttackFire,
			R_AttackFire,
			L_AttackDownKick,
			R_AttackDownKick,

			L_AttackSuperStr,
			R_AttackSuperStr,
			L_AttackSuperIng,
			R_AttackSuperIng,
			L_AttackSuperEnd,
			R_AttackSuperEnd,

			// 피해
			L_DamageStun,
			R_DamageStun,
			L_DamageKnockBack,
			R_DamageKnockBack,
			L_DamageKnockDown,
			R_DamageKnockDown,
			L_DamageDown,
			R_DamageDown,
		};

		enum class eBoss01CombatState
		{
			AttackPunch,
			AttackJumpPunch,
			AttackKick,
			AttackFire,

			Guard,

			AttackDownKick,

			AttackSuperStr,
			AttackSuperIng,
			AttackSuperEnd,

			End,
		};

	public:
		Boss01Script();
		~Boss01Script();

		virtual void Initialize() override;
		virtual void Update() override;

		// 충돌 함수
		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		// private 변수관련 함수
		int GetHp() { return mHp; }
		eDirection GetDirection() { return mDirection; }
		void SetDirection(eDirection dir) { mDirection = dir; }
		eBoss01State GetState() { return mCurState; }
		void ChangeState(eBoss01State newState) { mCurState = newState; }
		void ChangeWalkDirectionNState(eDirection dir)
		{
			if (dir == eDirection::L)
			{
				mDirectionInt = -1;
				mDirection = dir;
				mCurState = eBoss01State::L_Walk;
			}
			else
			{
				mDirectionInt = +1;
				mDirection = dir;
				mCurState = eBoss01State::R_Walk;
			}
		}
		bool IsWait()
		{
			if (mCurState == eBoss01State::L_Walk || mCurState == eBoss01State::R_Walk
				|| mCurState == eBoss01State::L_Run || mCurState == eBoss01State::R_Run)
				return true;

			return false;
		}

	private:
		//// 이벤트 함수
		void AppearComplete();
		void SuperStrComplete();
		void SuperEndComplete();
		void CombatComplete();
		void GuardComplete();
		void DamageStunComplete();
		void DamageKnockDownComplete();
		void DamageDownComplete();
		void DownedComplete();
		void GetUpComplete();
		void DisAppearComplete();

		// 감지 함수 
		bool IsPlayerInDetectionRange()// 플레이어 인식 감지 함수: 대기 상태로 돌입 조건
		{
			if (mIsPlayerDead == true)
				return false;

			float distanceX = mPlayerPos.x - mPos.x;
			float distanceY = mPlayerPos.y - mPos.y;
			float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

			return distance <= mDetectionRange;
		}
		bool IsPlayerInCombatRange()// 플레이어 전투 감지 함수: 전투 상태로 돌입 조건
		{
			if (mIsPlayerDead == true)
				return false;

			float distanceX = mPlayerPos.x - mPos.x;
			float distanceY = mPlayerPos.y - mPos.y;
			float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

			return distance <= mCombatRange;
		}
		float GetRandomMoveDistance()// 랜덤 거리 추출 함수
		{
			return baseMoveDistance + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / maxMoveRange));
		}

		// State 함수
		// Appear / Disappear
		void L_appear();
		void R_appear();
		void L_appearWait();
		void R_appearWait();
		void L_disAppear();
		void R_disAppear();

		// Basic
		void L_idle();
		void R_idle();
		void L_walk();
		void R_walk();
		void L_run();
		void R_run();

		void L_downed();
		void R_downed();
		void L_getUp();
		void R_getUp();

		// 방어
		void L_guard();
		void R_guard();

		// 공격
		void L_attackPunch();
		void R_attackPunch();
		void L_attackJumpPunchStr();
		void R_attackJumpPunchStr();
		void L_attackJumpPunchIng();
		void R_attackJumpPunchIng();
		void L_attackKick();
		void R_attackKick();
		void L_attackFire();
		void R_attackFire();
		void L_attackDownKick();
		void R_attackDownKick();

		void L_attackSuperStr();
		void R_attackSuperStr();
		void L_attackSuperIng();
		void R_attackSuperIng();
		void L_attackSuperEnd();
		void R_attackSuperEnd();

		// 피해
		void L_damageStun();
		void R_damageStun();
		void L_damageKnockBack();
		void R_damageKnockBack();
		void L_damageKnockDown();
		void R_damageKnockDown();
		void L_damageDown();
		void R_damageDown();

		// 동작 내부 함수
		void Combat();
		void SetAttackedState();

		// Effect
		void SetEffectFlickering(float tick, float duration);
		void SetEffectFlashing(float tick, float duration, Vector4 color);

	private:
		// 어빌리티
		int mHp = 500;
		int mMaxHp = 500;

		// 주요 상태
		eBoss01State mCurState = eBoss01State::R_Idle;
		eBoss01State mPrevState = eBoss01State::R_Idle;

		eDirection mDirection = eDirection::R;
		int mDirectionInt = 0;// Direction L은 -1 R은 +1

		Vector3 mPos;

		// Player 상태 (Boss01Scene의 static 변수를 업데이트 계속 해줌)
		Vector3 mPlayerPos;
		eDirection mPlayerDir;
		ePlayerState mPlayerPreState;
		ePlayerState mPlayerCurState;
		bool mIsPlayerDead;

		// 플레이어 인식 감지 (단순)
		const float mDetectionRange = 1.5f;
		bool mDetected = false;

		// 플레이어 전투 감지 (공격, 방어...)
		const float mCombatRange = 0.7f;
		bool mIsCombat = false;

		// AI 기본 이동 거리와 이동 범위 제한 값
		float baseMoveDistance = 0.1f;
		float maxMoveRange = 0.3f;

		// AI 이동 방향 변경을 위한 타이머 변수
		float mMoveTimer = 0.0f;
		const float mMoveInterval = 2.0f;// 2초마다 랜덤으로 방향 변경

		// AI 전투 변경을 위한 타이머 변수
		float mCombatTimer = 2.0f;
		float mCombatInterval = 1.0f;

		// AI 탐지 거리내에 플레이어 발견 시, 대기 or 달리기 관련 변수
		int mRandWaitOrRun = -100;
		float mRunSpeed = 0.4f;

		// NormalAttack 콤보 시 충돌체는 항시 유지되어 있지만 강제로 충돌 초기화를 위한 변수
		bool mIsNormalAttackComboInit = false;

		// 충돌 상태가 처음인지 확인하기 위한 변수
		int mIsCollidingFirst = 0;

		// 랜덤 함수 이용을 위한 변수
		std::random_device rd;

		// 콜라이더
		Collider2D* mBodyCd = nullptr;
		Collider2D* mSkillCd = nullptr;

		// State 변수
		unsigned int mPhase = 0;
		unsigned int mLevelofPhase0 = 0;
		unsigned int mLevelofPhase1 = 0;
		unsigned int mLevelofPhase2 = 0;
		unsigned int mLevelofPhase3 = 0;

		const float mToPhase02HpPercent = 70.0f;
		const float mToPhase04HpPercent = 50.0f;
		const float mToPhase05HpPercent = 0.0f;

		bool mIsAppear = false;
		bool mIsDisAppear = false;
		bool mIsIdle = false;
		bool mIsWalk = false;
		bool mIsRun = false;

		bool mIsDowned = false;
		bool mIsGetup = false;

		bool mIsGuard = false;

		bool mIsAttackPunch = false;
		bool mIsAttackJumpPunchStr = false;
		bool mIsAttackJumpPunchIng = false;
		bool mIsAttackKick = false;
		bool mIsAttackFire = false;
		bool mIsAttackDownKick = false;
		bool mIsAttackSuperStr = false;
		bool mIsAttackSuperIng = false;
		bool mIsAttackSuperEnd = false;

		bool mIsDamageStun = false;
		bool mIsDamageKnockBack = false;
		bool mIsDamageKnockDown = false;
		bool mIsDamageDown = false;
		bool mCanDamageDown = false;

		bool mIsDead = false;
		float mDeadTime = 3.0f;

		int  mAttackedDamage = 20;

		// 등장 화면
		GameObject* mAppearEffect = nullptr;

		// Minion
		GameObject* mMinion01 = nullptr;
		GameObject* mMinion02 = nullptr;
		GameObject* mMinion03 = nullptr;

		GameObject* mMinion04 = nullptr;
		GameObject* mMinion05 = nullptr;

		// Minion 콜라이더
		Collider2D* mMinion01BodyCd = nullptr;
		Collider2D* mMinion01SkillCd = nullptr;
		Collider2D* mMinion02BodyCd = nullptr;
		Collider2D* mMinion02SkillCd = nullptr;
		Collider2D* mMinion03BodyCd = nullptr;
		Collider2D* mMinion03SkillCd = nullptr;

		// Shadow
		GameObject* mShadow = nullptr;

		// Effect
		// Flickering
		bool mOnFlickering = false;
		float mFlickeringCurTime = 0.0f;
		float mFlickeringMaxTime = 0.0f;
		float mFlickeringTickTime = 0.0f;

		// Flashing
		bool mOnFlashing = false;
		float mFlashingCurTime = 0.0f;
		float mFlashingMaxTime = 0.0f;
		float mFlashingTickTime = 0.0f;

		// 플레이어 공격 스킬 상태를 담고 있는 bool 배열
		std::vector<bool> mPlayerAttackState;

		// 어떤 공격 스킬을 사용중인지 담고 있는 bool vector
		std::vector<bool> mAttackState;

	public:
		const std::vector<bool>& GetAttackState() const { return mAttackState; }
	};
}
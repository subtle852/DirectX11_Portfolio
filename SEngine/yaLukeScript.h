#pragma once
#include "yaScript.h"

namespace ya
{
	class LukeScript : public Script
	{
		enum class eLukeState
		{
			L_Idle,
			R_Idle,
			L_Angry,
			R_Angry,

			L_Walk,
			R_Walk,
			L_Run,
			R_Run,

			L_ArmAttack,
			R_ArmAttack,
			L_KickAttack,
			R_KickAttack,
			L_SideKickAttack,
			R_SideKickAttack,
			L_UpperAttack,
			R_UpperAttack,

			L_Guard,
			R_Guard,

			L_Attacked1,
			R_Attacked1,
			L_Attacked2,
			R_Attacked2,
			L_Attacked3,
			R_Attacked3,
			L_Attacked4,
			R_Attacked4,

			L_GetUp,
			R_GetUp,

			L_Downed,
			R_Downed,

			L_Dead,
			R_Dead,

			L_Flying,
			R_Flying,
			L_Raiding,
			R_Raiding,
		};

		enum class eLukeCombatState
		{
			ArmAttack,
			KickAttack,
			SideKickAttack,
			UpperAttack,

			//Guard,

			End,
		};

	public:
		LukeScript();
		~LukeScript();

		virtual void Initialize() override;
		virtual void Update() override;

		// 이벤트 함수
		void JumpStart();
		void Attacked1Complete();
		void CombatComplete();
		void GuardComplete();
		void Attacked3Complete();
		void DownedComplete();
		void GetUpComplete();

		// 충돌 함수
		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	private:
		//bool NoneAnimationCondition();
		eDirection GetDirection() { return mDirection; }
		void SetDirection(eDirection dir) { mDirection = dir; }
		eLukeState GetState() { return mState; }
		void ChangeState(eLukeState newState) { mState = newState; }

		// 플레이어 감지 함수
		bool IsPlayerInDetectionRange()// 플레이어 인식 감지 함수: 대기 상태로 돌입 조건
		{
			// 적과 플레이어 사이의 거리 계산
			float distanceX = mPlayerPos.x - mPos.x;
			float distanceY = mPlayerPos.y - mPos.y;
			float distanceSquared = distanceX * distanceX + distanceY * distanceY;
			float detectionRangeSquared = mDetectionRange * mDetectionRange;

			// 플레이어가 감지 범위 내에 있는지 확인
			return distanceSquared <= detectionRangeSquared;
		}

		bool IsPlayerInCombatRange()// 플레이어 전투 감지 함수: 전투 상태로 돌입 조건
		{
			// 적과 플레이어 사이의 거리 계산
			float distanceX = mPlayerPos.x - mPos.x;
			float distanceY = mPlayerPos.y - mPos.y;
			float distanceSquared = distanceX * distanceX + distanceY * distanceY;
			float detectionRangeSquared = mCombatRange * mCombatRange;

			// 플레이어가 감지 범위 내에 있는지 확인
			return distanceSquared <= detectionRangeSquared;
		}

		// 랜덤 거리 추출 함수
		float GetRandomMoveDistance() 
		{
			return baseMoveDistance + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / maxMoveRange));
		}

		// 동작 내부 함수
		void Combat();

		void SetAttackedState();

		// State 함수
		void L_idle();
		void R_idle();

		void L_angry();
		void R_angry();

		void L_walk();
		void R_walk();

		void L_run();
		void R_run();

		void L_armattack();
		void R_armattack();
		void L_kickattack();
		void R_kickattack();
		void L_sidekickattack();
		void R_sidekickattack();
		void L_upperattack();
		void R_upperattack();

		void L_guard();
		void R_guard();

		void L_attacked1();
		void R_attacked1();
		void L_attacked2();
		void R_attacked2();
		void L_attacked3();
		void R_attacked3();
		void L_attacked4();
		void R_attacked4();

		void L_getup();
		void R_getup();

		void L_downed();
		void R_downed();

		void L_dead();
		void R_dead();

		void L_flying();
		void R_flying();
		void L_raiding();
		void R_raiding();


	private:
		// 어빌리티
		float mHp = 100.0f;

		// 주요 상태
		eLukeState mState = eLukeState::R_Idle;
		eLukeState mPreviousState = eLukeState::R_Idle;

		eDirection mDirection = eDirection::R;
		int mDirectionInt = 0;// Direction L은 -1 R은 +1

		Vector3 mPos;

		// Player 상태 (PlayScene의 static 변수를 업데이트 계속 해줌)
		Vector3 mPlayerPos;
		eDirection mPlayerDir;
		ePlayerState mPlayerPreState;
		ePlayerState mPlayerCurState;

		// 플레이어 인식 감지 (단순)
		const float mDetectionRange = 1.5f;
		bool mDetected = false;

		// 플레이어 전투 감지 (공격, 방어...)
		const float mCombatRange = 0.7f;
		bool mCombated = false;

		// AI 기본 이동 거리와 이동 범위 제한 값
		float baseMoveDistance = 0.1f;
		float maxMoveRange = 0.3f;

		// AI 이동 방향 변경을 위한 타이머 변수
		float mMoveTimer;
		const float mMoveInterval = 2.0f; // 2초마다 랜덤으로 방향 변경

		// AI 전투 변경을 위한 타이머 변수
		float mCombatTimer = 2.0f;
		float mCombatInterval = 4.0f;
		
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
		bool mIsIdle = false;
		bool mIsAngry = false;
		bool mIsWalk = false;
		bool mIsRun = false;
		
		bool mIsArm = false;
		bool mIsKick = false;
		bool mIsSideKick = false;
		bool mIsUpper = false;

		bool mIsGuard = false;

		bool mIsAttacked1 = false;
		bool mIsAttacked2 = false;
		bool mIsAttacked3 = false;
		bool mIsAttacked4 = false;

		bool mIsGetUp = false;

		bool mIsDowned = false;
		//bool mIsDead = false;

		bool mIsFlying = false;
		bool mIsRaiding = false;

		// 어떤 공격 스킬을 사용중인지 담고 있는 bool 배열
		bool mAttackState[10] = { false, };

	public:
		// mAttackState 배열 시작 주소를 보내주는 함수
		const bool* GetAttackState() { return &mAttackState[0]; }

	private:
		// 플레이어 공격 스킬 상태를 담고 있는 bool 배열
		bool mPlayerAttackState[20] = { false, };
	};
}
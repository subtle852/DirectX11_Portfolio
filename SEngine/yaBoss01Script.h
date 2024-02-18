//#pragma once
//#include "yaScript.h"
//
//namespace ya
//{
//	class Boss01Script : public Script
//	{
//		enum class eBoss01State
//		{
//			L_Appear,
//			R_Appear,
//			L_DisAppear,
//			R_DisAppear,
//
//			L_Idle,
//			R_Idle,
//			L_Walk,
//			R_Walk,
//			L_Run,
//			R_Run,
//			L_Jump,
//			R_Jump,
//
//			L_Downed,
//			R_Downed,
//			L_GetUp,
//			R_GetUp,
//
//			L_Guard,
//			R_Guard,
//
//			// 공격
//			L_AttackCombo,
//			R_AttackCombo,
//			L_AttackFire,
//			R_AttackFire,
//			L_AttackJump,
//			R_AttackJump,
//			L_AttackKick,
//			R_AttackKick,
//			L_AttackDownKick,
//			R_AttackDownKick,
//
//			L_AttackSuperStr,
//			R_AttackSuperStr,
//			L_AttackSuperIng,
//			R_AttackSuperIng,
//			L_AttackSuperEnd,
//			R_AttackSuperEnd,
//
//			// 피해
//			L_AttackedDown,
//			R_AttackedDown,
//			L_AttackedKnockDown,
//			R_AttackedKnockDown,
//			L_AttackedLower,
//			R_AttackedLower,
//			L_AttackedMiddle,
//			R_AttackedMiddle,
//			L_AttackedUpper,
//			R_AttackedUpper,
//			L_AttackedDown,
//			R_AttackedDown,
//		};
//
//		enum class eBoss01CombatState
//		{
//			AttackCombo,
//			AttackFire,
//			AttackJump,
//			AttackKick,
//			AttackKick,
//			AttackDownKick,
//
//			AttackSuperStr,
//			AttackSuperIng,
//			AttackSuperEnd,
//
//			//Guard,
//
//			End,
//		};
//
//	public:
//		Boss01Script();
//		~Boss01Script();
//
//		virtual void Initialize() override;
//		virtual void Update() override;
//
//		// 이벤트 함수
//		void AttackedDownComplete();
//
//		// 충돌 함수
//		virtual void OnCollisionEnter(Collider2D* other) override;
//		virtual void OnCollisionStay(Collider2D* other) override;
//		virtual void OnCollisionExit(Collider2D* other) override;
//
//	private:
//		//bool NoneAnimationCondition();
//		eDirection GetDirection() { return mDirection; }
//		void SetDirection(eDirection dir) { mDirection = dir; }
//		eBoss01State GetState() { return mState; }
//		void ChangeState(eBoss01State newState) { mState = newState; }
//
//		// 플레이어 감지 함수
//		bool IsPlayerInDetectionRange()// 플레이어 인식 감지 함수: 대기 상태로 돌입 조건
//		{
//			// 적과 플레이어 사이의 거리 계산
//			float distanceX = mPlayerPos.x - mPos.x;
//			float distanceY = mPlayerPos.y - mPos.y;
//			float distanceSquared = distanceX * distanceX + distanceY * distanceY;
//			float detectionRangeSquared = mDetectionRange * mDetectionRange;
//
//			// 플레이어가 감지 범위 내에 있는지 확인
//			return distanceSquared <= detectionRangeSquared;
//		}
//
//		bool IsPlayerInCombatRange()// 플레이어 전투 감지 함수: 전투 상태로 돌입 조건
//		{
//			// 적과 플레이어 사이의 거리 계산
//			float distanceX = mPlayerPos.x - mPos.x;
//			float distanceY = mPlayerPos.y - mPos.y;
//			float distanceSquared = distanceX * distanceX + distanceY * distanceY;
//			float detectionRangeSquared = mCombatRange * mCombatRange;
//
//			// 플레이어가 감지 범위 내에 있는지 확인
//			return distanceSquared <= detectionRangeSquared;
//		}
//
//		// 랜덤 거리 추출 함수
//		float GetRandomMoveDistance()
//		{
//			return baseMoveDistance + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / maxMoveRange));
//		}
//
//		// 동작 내부 함수
//		void Combat();
//
//		void SetAttackedState();
//
//		// State 함수
//		void L_appear();
//		void R_appear();
//		void L_disAppear();
//		void R_disAppear();
//
//		void L_idle();
//		void R_idle();
//		void L_walk();
//		void R_walk();
//		void L_run();
//		void R_run();
//		void L_jump();
//		void R_jump();
//
//		void L_downed();
//		void R_downed();
//		void L_getUp();
//		void R_getUp();
//		void L_guard();
//		void R_guard();
//
//		// 공격
//		void L_attackCombo();
//		void R_attackCombo();
//		void L_attackFire();
//		void R_attackFire();
//		void L_attackJump();
//		void R_attackJump();
//		void L_attackKick();
//		void R_attackKick();
//		void L_attackDownKick();
//		void R_attackDownKick();
//		void L_attackSuperStr();
//		void R_attackSuperStr();
//		void L_attackSuperIng();
//		void R_attackSuperIng();
//		void L_attackSuperEnd();
//		void R_attackSuperEnd();
//
//		// 피해
//		void L_attackedDown();
//		void R_attackedDown();
//		void L_attackedKnockDown();
//		void R_attackedKnockDown();
//		void L_attackedLower();
//		void R_attackedLower();
//		void L_attackedMiddle();
//		void R_attackedMiddle();
//		void L_attackedUpper();
//		void R_attackedUpper();
//		void L_attackedDown();
//		void R_attackedDown();
//
//	private:
//		// 어빌리티
//		float mHp = 100.0f;
//
//		// 주요 상태
//		eBoss01State mState = eBoss01State::L_Idle;
//		eBoss01State mPreviousState = eBoss01State::L_Idle;
//
//		eDirection mDirection = eDirection::R;
//		int mDirectionInt = 0;// Direction L은 -1 R은 +1
//
//		Vector3 mPos;
//
//		// Player 상태 (PlayScene의 static 변수를 업데이트 계속 해줌)
//		Vector3 mPlayerPos;
//		eDirection mPlayerDir;
//		ePlayerState mPlayerPreState;
//		ePlayerState mPlayerCurState;
//
//		// 플레이어 인식 감지 (단순)
//		const float mDetectionRange = 1.5f;
//		bool mDetected = false;
//
//		// 플레이어 전투 감지 (공격, 방어...)
//		const float mCombatRange = 0.7f;
//		bool mCombated = false;
//
//		// AI 기본 이동 거리와 이동 범위 제한 값
//		float baseMoveDistance = 0.1f;
//		float maxMoveRange = 0.3f;
//
//		// AI 이동 방향 변경을 위한 타이머 변수
//		float mMoveTimer;
//		const float mMoveInterval = 2.0f; // 2초마다 랜덤으로 방향 변경
//
//		// AI 전투 변경을 위한 타이머 변수
//		float mCombatTimer = 2.0f;
//		float mCombatInterval = 4.0f;
//
//		// AI 탐지 거리내에 플레이어 발견 시, 대기 or 달리기 관련 변수
//		int mRandWaitOrRun = -100;
//		float mRunSpeed = 0.4f;
//
//		// NormalAttack 콤보 시 충돌체는 항시 유지되어 있지만 강제로 충돌 초기화를 위한 변수
//		bool mIsNormalAttackComboInit = false;
//
//		// 충돌 상태가 처음인지 확인하기 위한 변수
//		int mIsCollidingFirst = 0;
//
//		// 랜덤 함수 이용을 위한 변수
//		std::random_device rd;
//
//		// 콜라이더
//		Collider2D* mBodyCd = nullptr;
//		Collider2D* mSkillCd = nullptr;
//
//		// 부하
//		GameObject* mUnderling01 = nullptr;
//		GameObject* mUnderling02 = nullptr;
//		GameObject* mUnderling03 = nullptr;
//		GameObject* mUnderling04 = nullptr;
//
//		// State 변수
//		bool mIsIdle = false;
//		bool mIsWalk = false;
//		bool mIsRun = false;
//		bool mIsJump = false;
//
//		bool mIsDowned = false;
//		bool mIsGetUp = false;
//		bool mIsGuard = false;
//
//		bool mIsAttackCombo = false;
//		bool mIsAttackFire = false;
//		bool mIsAttackJump = false;
//		bool mIsAttackKick = false;
//		bool mIsAttackDownKick = false;
//		bool mIsAttackSuper = false;
//
//		bool mIsAttacked = false;
//		bool mIsAttackedDown = false;
//		bool mIsAttackedKnockDown = false;
//
//		// 어떤 공격 스킬을 사용중인지 담고 있는 bool 배열
//		bool mAttackState[10] = { false, };
//
//	public:
//		// mAttackState 배열 시작 주소를 보내주는 함수
//		const bool* GetAttackState() { return &mAttackState[0]; }
//
//	private:
//		// 플레이어 공격 스킬 상태를 담고 있는 bool 배열
//		bool mPlayerAttackState[20] = { false, };
//	};
//}
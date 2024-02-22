#pragma once
#include "yaScript.h"
#include "yaPlayerScript.h"

namespace ya
{
	class RamonaScript : public Script
	{
		struct RamonaAttribute
		{
			float mHp = 100.0f;
			int mHeart = 3;
			float mGP = 0;
			float mCoin = 0.0f;
		};

	public:
		RamonaScript();
		~RamonaScript();

		virtual void Initialize() override;
		virtual void Update() override;

		// private 변수관련 함수
		eDirection GetDirection() { return mDirection; }
		ePlayerState GetState() { return mState; }

		// 이벤트 함수
		void EvadeComplete();

		void NormalAttackComplete();
		void KickComplete();

		void WeaponAttackComplete();
		void JumpAttackComplete();
		void RunAttackComplete();

		void FireBallComplete();
		void SuperComplete();

		void StunComplete();
		void KnockDownComplete();
		void DownedComplete();
		void GetUpComplete();

		bool GetIsJump() { return mIsJump; }
		bool GetIsDJump() { return mIsDJump; }

		// 충돌 함수
		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	private:

		//// 조건 함수

		// 다른 애니메이션 진행중인데 좌우상하 키가 눌린다고 해서 
		// 특정 애니메이션(ex. Walk)이 진행되면 안되기에 다른 애니메이션이 진행중인지 확인하는 조건
		bool NoneAnimationCondition();

		// 좌우상하 이동을 막아야하는 경우 ex. FireBall
		bool CanMoveCondition();

		// 점프를 막아야하는 경우
		bool CanJumpCondition();

		// 공격 스킬 도중에는 다른 공격 스킬이 실행되지 않기위한 조건
		// 콤보 스킬이나 연계 스킬(ex. D + down)은 이 조건을 사용해서는 안됨
		// 기존 스킬이 true인 상태에서 연계 스킬이 진행 되기 때문
		bool CanAttackCondition();

		// State가 바뀌면 안되는 상태 ex. Stun, KnockDown,... 이런 상태 진행중에 다른 상태로 전환되면 안됨
		bool CanChangeState();

		//// State 함수
		void L_idle();
		void R_idle();

		void L_walk();
		void R_walk();

		void L_run();
		void R_run();

		void L_jump();
		void R_jump();

		void L_djump();
		void R_djump();

		void L_guard();
		void R_guard();

		void L_evade();
		void R_evade();

		void L_normalattack1();
		void R_normalattack1();
		void L_normalattack2();
		void R_normalattack2();
		void L_normalattack3();
		void R_normalattack3();

		void L_kick();
		void R_kick();
		void L_roundkick();
		void R_roundkick();
		void L_behindkick();
		void R_behindkick();

		void L_weaponnormalattack();
		void R_weaponnormalattack();
		void L_weapondownattack();
		void R_weapondownattack();
		void L_weaponsideattack();
		void R_weaponsideattack();
		void L_weaponstabattack();
		void R_weaponstabattack();

		void L_jumpdownattack();
		void R_jumpdownattack();
		void L_jumpslideattack();
		void R_jumpslideattack();
		void L_runjumpattack();
		void R_runjumpattack();

		void L_runweaponattack();
		void R_runweaponattack();
		void L_runslideattack();
		void R_runslideattack();

		void L_fireball();
		void R_fireball();
		void L_super();
		void R_super();

		void L_stun();
		void R_stun();
		void L_backstun();
		void R_backstun();
		void L_knockdown();
		void R_knockdown();

		void L_downed();
		void R_downed();

		void L_getup();
		void R_getup();

		// Effect
		void SetEffectFlickering(float tick, float duration);

	private:
		// 속성
		RamonaAttribute mAttribute;

		// 주요 상태
		ePlayerState mState = ePlayerState::R_Idle;
		ePlayerState mPreviousState = ePlayerState::R_Idle;

		eDirection mDirection = eDirection::R;

		//// State 변수
		
		// Walk
		float mWalkSpeed = 0.7f;

		// Run
		bool mIsRun = false;
		float mRunSpeed1 = 0.4f;// 좌우 이동
		float mRunSpeed2 = 0.3f;// 상하 이동

		// Jump
		bool mIsJump = false;
		float mJumpTime = 0.0f;// 점프 체공 시간 측정
		float mJumpStartPosY = -100.0f;// 점프 시작 위치 (불가능한 -100.0f로 초기화)
		bool mIsDJump = false;
		float mJumpHalfTime = 0.3f;// 점프 체공시간의 절반
		float mJumpHeight = 1.8f;// 점프 높이
		float mDJumpHeight = 2.3f;// 더블점프 높이

		// Guard, Evade
		bool mIsGuard = false;
		bool mIsEvade = false;

		// 콤보 공격
		bool mIsNormalAttack1 = false;
		bool mIsNormalAttack2 = false;
		bool mIsNormalAttack3 = false;
		bool mCanNormalAttack2 = false;
		bool mCanNormalAttack3 = false;
		float mNormalAttack2Time = 0.0f;// NormalAttack2 실행 시간 측정

		// 콤보 공격 제외한 나머지 공격
		bool mIsKickAttack = false;
		bool mIsRoundKickAttack = false;
		bool mIsBehindKickAttack = false;

		bool mIsWeaponNormalAttack = false;
		bool mIsWeaponDownAttack = false;
		bool mIsWeaponSideAttack = false;
		bool mIsWeaponStabAttack = false;

		bool mIsJumpDownAttack = false;
		bool mIsJumpSlideAttack = false;
		bool mIsRunJumpAttack = false;

		bool mIsRunWeaponAttack = false;
		bool mIsRunSlideAttack = false;

		bool mIsFireBall = false;
		bool mIsSuper = false;

		// Under Attack
		bool mIsStun = false;
		bool mIsKnockDown = false;
		bool mIsDowned = false;
		bool mIsGetUp = false;
		bool mIsBackStun = false;

		// 충돌체
		Collider2D* mBodyCd = nullptr;
		Collider2D* mUpperCd = nullptr;
		Collider2D* mLowerCd = nullptr;
		Collider2D* mBothCd = nullptr;
		Collider2D* mBackCd = nullptr;
		Collider2D* mAllCd = nullptr;

		GameObject* mgb = nullptr;

		// 어떤 공격 스킬을 사용중인지 담고 있는 bool 배열
		bool mAttackState[20] = { false, };

		// mAttackState 배열 시작 주소를 보내주는 함수
	public:
		const bool* GetAttackState() { return &mAttackState[0]; }

	private:
		// 적 공격 스킬 상태를 담고 있는 bool 배열
		bool mEnemyAttackState[10] = { false, };

		// 충돌이 처음인지 확인하는 변수
		int mIsCollidingFirst = 0;

		// 플레이어 기준 적의 방향(왼쪽, 오른쪽)을 체크
		int mEnemyPosition = 1;// -1 (왼쪽) 플레이어 +1 (오른쪽)

		bool mOnFlickering = false;
		float mFlickeringCurTime = 0.0f;
		float mFlickeringMaxTime = 0.0f;
		float mFlickeringTickTime = 0.0f;
	};
}
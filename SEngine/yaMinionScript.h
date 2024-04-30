#pragma once
#include "yaScript.h"
#include "yaEnemyScript.h"

namespace ya
{
	class MinionScript : public EnemyScript
	{
		enum class eMinionState
		{
			L_Appear,
			R_Appear,

			L_DisAppear,
			R_DisAppear,

			L_Idle,
			R_Idle,

			L_AttackAppear,
			R_AttackAppear,
			L_Attack,
			R_Attack,
			L_AttackDisAppear,
			R_AttackDisAppear,
			L_AttackNo,
			R_AttackNo,

			L_Damage,
			R_Damage,
		};

	public:
		MinionScript();
		~MinionScript();

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
		eMinionState GetState() { return mCurState; }
		void ChangeState(eMinionState newState) { mCurState = newState; }

		bool IsDead() { return mIsDead = true; }

		unsigned int GetPhase() { return mPhase; }
		void SetPhase(unsigned int phase) { mPhase = phase; }

		void SetLevelPhase3(unsigned int levelPhase3) { mLevelPhase3 = levelPhase3; }

		void SetInitRadian(float radian) { currentRadian = radian; }

	private:
		// 이벤트 함수
		void AppearComplete();
		void DisAppearComplete();
		void DamageComplete();

		void AttackAppearComplete();
		void AttackComplete();
		void AttackDisAppearComplete();

		// State 함수
		void L_appear();
		void R_appear();

		void L_disAppear();
		void R_disAppear();

		void L_idle();
		void R_idle();

		void L_attackAppear();
		void R_attackAppear();
		void L_attack();
		void R_attack(); 
		void L_attackDisAppear();
		void R_attackDisAppear();
		void L_attackNo();
		void R_attackNo();

		void L_damage();
		void R_damage();

		// 동작 내부 함수
		//

		// Effect
		void SetEffectFlickering(float tick, float duration);
		void SetEffectFlashing(float tick, float duration, Vector4 color);

	private:
		// 속성
		int mHp = 20;

		// 주요 상태
		eMinionState mCurState = eMinionState::R_Idle;
		eMinionState mPrevState = eMinionState::R_Idle;

		eDirection mDirection = eDirection::R;
		int mDirectionInt = 0;// Direction L은 -1 R은 +1

		Vector3 mPos;

		// Player 상태 (Boss01Scene의 static 변수를 업데이트 계속 해줌)
		Vector3 mPlayerPos;
		eDirection mPlayerDir;
		ePlayerState mPlayerPreState;
		ePlayerState mPlayerCurState;
		bool mIsPlayerDead;

		// 콜라이더
		Collider2D* mBodyCd = nullptr;
		Collider2D* mSkillCd = nullptr;

		int mIsCollidingFirst = 0;

		// 총알
		GameObject* mBullet01 = nullptr;
		GameObject* mBullet02 = nullptr;

		// State 변수
		unsigned int mPhase = 0;
		unsigned int mLevelPhase3 = 0;
		float mPhase3AppearTime = 2.0f;

		bool mIsIdle = false;
		bool mIsAttack = false;
		bool mIsDamage = false;

		bool mIsDead = false;

		int  mAttackedDamage = 20;

		// 회전
		float currentRadian = 0.0f;
		float currentDegree = 0.0f;
		float rotationSpeed = 1.0f;
		float angleInDegrees = 0.0f;

		// 그림자
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
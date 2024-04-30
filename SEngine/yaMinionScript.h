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

		// �浹 �Լ�
		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		// private �������� �Լ�
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
		// �̺�Ʈ �Լ�
		void AppearComplete();
		void DisAppearComplete();
		void DamageComplete();

		void AttackAppearComplete();
		void AttackComplete();
		void AttackDisAppearComplete();

		// State �Լ�
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

		// ���� ���� �Լ�
		//

		// Effect
		void SetEffectFlickering(float tick, float duration);
		void SetEffectFlashing(float tick, float duration, Vector4 color);

	private:
		// �Ӽ�
		int mHp = 20;

		// �ֿ� ����
		eMinionState mCurState = eMinionState::R_Idle;
		eMinionState mPrevState = eMinionState::R_Idle;

		eDirection mDirection = eDirection::R;
		int mDirectionInt = 0;// Direction L�� -1 R�� +1

		Vector3 mPos;

		// Player ���� (Boss01Scene�� static ������ ������Ʈ ��� ����)
		Vector3 mPlayerPos;
		eDirection mPlayerDir;
		ePlayerState mPlayerPreState;
		ePlayerState mPlayerCurState;
		bool mIsPlayerDead;

		// �ݶ��̴�
		Collider2D* mBodyCd = nullptr;
		Collider2D* mSkillCd = nullptr;

		int mIsCollidingFirst = 0;

		// �Ѿ�
		GameObject* mBullet01 = nullptr;
		GameObject* mBullet02 = nullptr;

		// State ����
		unsigned int mPhase = 0;
		unsigned int mLevelPhase3 = 0;
		float mPhase3AppearTime = 2.0f;

		bool mIsIdle = false;
		bool mIsAttack = false;
		bool mIsDamage = false;

		bool mIsDead = false;

		int  mAttackedDamage = 20;

		// ȸ��
		float currentRadian = 0.0f;
		float currentDegree = 0.0f;
		float rotationSpeed = 1.0f;
		float angleInDegrees = 0.0f;

		// �׸���
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

		// �÷��̾� ���� ��ų ���¸� ��� �ִ� bool �迭
		std::vector<bool> mPlayerAttackState;

		// � ���� ��ų�� ��������� ��� �ִ� bool vector
		std::vector<bool> mAttackState;

	public:
		const std::vector<bool>& GetAttackState() const { return mAttackState; }
	};
}
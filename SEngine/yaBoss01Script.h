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

			// ���
			L_Guard,
			R_Guard,

			// ����
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

			// ����
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

		// �浹 �Լ�
		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		// private �������� �Լ�
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
		//// �̺�Ʈ �Լ�
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

		// ���� �Լ� 
		bool IsPlayerInDetectionRange()// �÷��̾� �ν� ���� �Լ�: ��� ���·� ���� ����
		{
			if (mIsPlayerDead == true)
				return false;

			float distanceX = mPlayerPos.x - mPos.x;
			float distanceY = mPlayerPos.y - mPos.y;
			float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

			return distance <= mDetectionRange;
		}
		bool IsPlayerInCombatRange()// �÷��̾� ���� ���� �Լ�: ���� ���·� ���� ����
		{
			if (mIsPlayerDead == true)
				return false;

			float distanceX = mPlayerPos.x - mPos.x;
			float distanceY = mPlayerPos.y - mPos.y;
			float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

			return distance <= mCombatRange;
		}
		float GetRandomMoveDistance()// ���� �Ÿ� ���� �Լ�
		{
			return baseMoveDistance + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / maxMoveRange));
		}

		// State �Լ�
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

		// ���
		void L_guard();
		void R_guard();

		// ����
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

		// ����
		void L_damageStun();
		void R_damageStun();
		void L_damageKnockBack();
		void R_damageKnockBack();
		void L_damageKnockDown();
		void R_damageKnockDown();
		void L_damageDown();
		void R_damageDown();

		// ���� ���� �Լ�
		void Combat();
		void SetAttackedState();

		// Effect
		void SetEffectFlickering(float tick, float duration);
		void SetEffectFlashing(float tick, float duration, Vector4 color);

	private:
		// �����Ƽ
		int mHp = 500;
		int mMaxHp = 500;

		// �ֿ� ����
		eBoss01State mCurState = eBoss01State::R_Idle;
		eBoss01State mPrevState = eBoss01State::R_Idle;

		eDirection mDirection = eDirection::R;
		int mDirectionInt = 0;// Direction L�� -1 R�� +1

		Vector3 mPos;

		// Player ���� (Boss01Scene�� static ������ ������Ʈ ��� ����)
		Vector3 mPlayerPos;
		eDirection mPlayerDir;
		ePlayerState mPlayerPreState;
		ePlayerState mPlayerCurState;
		bool mIsPlayerDead;

		// �÷��̾� �ν� ���� (�ܼ�)
		const float mDetectionRange = 1.5f;
		bool mDetected = false;

		// �÷��̾� ���� ���� (����, ���...)
		const float mCombatRange = 0.7f;
		bool mIsCombat = false;

		// AI �⺻ �̵� �Ÿ��� �̵� ���� ���� ��
		float baseMoveDistance = 0.1f;
		float maxMoveRange = 0.3f;

		// AI �̵� ���� ������ ���� Ÿ�̸� ����
		float mMoveTimer = 0.0f;
		const float mMoveInterval = 2.0f;// 2�ʸ��� �������� ���� ����

		// AI ���� ������ ���� Ÿ�̸� ����
		float mCombatTimer = 2.0f;
		float mCombatInterval = 1.0f;

		// AI Ž�� �Ÿ����� �÷��̾� �߰� ��, ��� or �޸��� ���� ����
		int mRandWaitOrRun = -100;
		float mRunSpeed = 0.4f;

		// NormalAttack �޺� �� �浹ü�� �׽� �����Ǿ� ������ ������ �浹 �ʱ�ȭ�� ���� ����
		bool mIsNormalAttackComboInit = false;

		// �浹 ���°� ó������ Ȯ���ϱ� ���� ����
		int mIsCollidingFirst = 0;

		// ���� �Լ� �̿��� ���� ����
		std::random_device rd;

		// �ݶ��̴�
		Collider2D* mBodyCd = nullptr;
		Collider2D* mSkillCd = nullptr;

		// State ����
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

		// ���� ȭ��
		GameObject* mAppearEffect = nullptr;

		// Minion
		GameObject* mMinion01 = nullptr;
		GameObject* mMinion02 = nullptr;
		GameObject* mMinion03 = nullptr;

		GameObject* mMinion04 = nullptr;
		GameObject* mMinion05 = nullptr;

		// Minion �ݶ��̴�
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

		// �÷��̾� ���� ��ų ���¸� ��� �ִ� bool �迭
		std::vector<bool> mPlayerAttackState;

		// � ���� ��ų�� ��������� ��� �ִ� bool vector
		std::vector<bool> mAttackState;

	public:
		const std::vector<bool>& GetAttackState() const { return mAttackState; }
	};
}
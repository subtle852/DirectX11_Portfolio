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
//			// ����
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
//			// ����
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
//		// �̺�Ʈ �Լ�
//		void AttackedDownComplete();
//
//		// �浹 �Լ�
//		virtual void OnCollisionEnter(Collider2D* other) override;
//		virtual void OnCollisionStay(Collider2D* other) override;
//		virtual void OnCollisionExit(Collider2D* other) override;
//
//	private:
//		//bool NoneAnimationCondition();
//		eDirection GetDirection() { return mDirection; }
//		void SetDirection(eDirection dir) { mDirection = dir; }
//		eBoss01State GetState() { return mCurState; }
//		void ChangeState(eBoss01State newState) { mCurState = newState; }
//
//		// �÷��̾� ���� �Լ�
//		bool IsPlayerInDetectionRange()// �÷��̾� �ν� ���� �Լ�: ��� ���·� ���� ����
//		{
//			// ���� �÷��̾� ������ �Ÿ� ���
//			float distanceX = mPlayerPos.x - mPos.x;
//			float distanceY = mPlayerPos.y - mPos.y;
//			float distanceSquared = distanceX * distanceX + distanceY * distanceY;
//			float detectionRangeSquared = mDetectionRange * mDetectionRange;
//
//			// �÷��̾ ���� ���� ���� �ִ��� Ȯ��
//			return distanceSquared <= detectionRangeSquared;
//		}
//
//		bool IsPlayerInCombatRange()// �÷��̾� ���� ���� �Լ�: ���� ���·� ���� ����
//		{
//			// ���� �÷��̾� ������ �Ÿ� ���
//			float distanceX = mPlayerPos.x - mPos.x;
//			float distanceY = mPlayerPos.y - mPos.y;
//			float distanceSquared = distanceX * distanceX + distanceY * distanceY;
//			float detectionRangeSquared = mCombatRange * mCombatRange;
//
//			// �÷��̾ ���� ���� ���� �ִ��� Ȯ��
//			return distanceSquared <= detectionRangeSquared;
//		}
//
//		// ���� �Ÿ� ���� �Լ�
//		float GetRandomMoveDistance()
//		{
//			return baseMoveDistance + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / maxMoveRange));
//		}
//
//		// ���� ���� �Լ�
//		void Combat();
//
//		void SetAttackedState();
//
//		// State �Լ�
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
//		// ����
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
//		// ����
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
//		// �����Ƽ
//		float mHp = 100.0f;
//
//		// �ֿ� ����
//		eBoss01State mCurState = eBoss01State::L_Idle;
//		eBoss01State mPrevState = eBoss01State::L_Idle;
//
//		eDirection mDirection = eDirection::R;
//		int mDirectionInt = 0;// Direction L�� -1 R�� +1
//
//		Vector3 mPos;
//
//		// Player ���� (PlayScene�� static ������ ������Ʈ ��� ����)
//		Vector3 mPlayerPos;
//		eDirection mPlayerDir;
//		ePlayerState mPlayerPreState;
//		ePlayerState mPlayerCurState;
//
//		// �÷��̾� �ν� ���� (�ܼ�)
//		const float mDetectionRange = 1.5f;
//		bool mDetected = false;
//
//		// �÷��̾� ���� ���� (����, ���...)
//		const float mCombatRange = 0.7f;
//		bool mIsCombat = false;
//
//		// AI �⺻ �̵� �Ÿ��� �̵� ���� ���� ��
//		float baseMoveDistance = 0.1f;
//		float maxMoveRange = 0.3f;
//
//		// AI �̵� ���� ������ ���� Ÿ�̸� ����
//		float mMoveTimer;
//		const float mMoveInterval = 2.0f; // 2�ʸ��� �������� ���� ����
//
//		// AI ���� ������ ���� Ÿ�̸� ����
//		float mCombatTimer = 2.0f;
//		float mCombatInterval = 4.0f;
//
//		// AI Ž�� �Ÿ����� �÷��̾� �߰� ��, ��� or �޸��� ���� ����
//		int mRandWaitOrRun = -100;
//		float mRunSpeed = 0.4f;
//
//		// NormalAttack �޺� �� �浹ü�� �׽� �����Ǿ� ������ ������ �浹 �ʱ�ȭ�� ���� ����
//		bool mIsNormalAttackComboInit = false;
//
//		// �浹 ���°� ó������ Ȯ���ϱ� ���� ����
//		int mIsCollidingFirst = 0;
//
//		// ���� �Լ� �̿��� ���� ����
//		std::random_device rd;
//
//		// �ݶ��̴�
//		Collider2D* mBodyCd = nullptr;
//		Collider2D* mSkillCd = nullptr;
//
//		// ����
//		GameObject* mUnderling01 = nullptr;
//		GameObject* mUnderling02 = nullptr;
//		GameObject* mUnderling03 = nullptr;
//		GameObject* mUnderling04 = nullptr;
//
//		// State ����
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
//		// � ���� ��ų�� ��������� ��� �ִ� bool �迭
//		bool mAttackState[10] = { false, };
//
//	public:
//		// mAttackState �迭 ���� �ּҸ� �����ִ� �Լ�
//		const bool* GetAttackState() { return &mAttackState[0]; }
//
//	private:
//		// �÷��̾� ���� ��ų ���¸� ��� �ִ� bool �迭
//		bool mPlayerAttackState[20] = { false, };
//	};
//}
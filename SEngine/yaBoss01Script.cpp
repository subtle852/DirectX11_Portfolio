#include "yaBoss01Script.h"
#include "yaCameraScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaPlayScene.h"
#include "yaCollider2D.h"
#include "yaRamonaScript.h"
#include "yaRigidbody.h"
#include "yaObject.h"
#include "yaMeshRenderer.h"
#include "..\\Editor_Window\\yaDebugLog.h"

namespace ya
{
	Boss01Script::Boss01Script()
	{
		mAttackState.resize(10, false);
		mPlayerAttackState.resize(20, false);
	}

	Boss01Script::~Boss01Script()
	{
	}

	void Boss01Script::Initialize()
	{
#pragma region �׸���
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// �׸���
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		mShadow = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 40.f)
			, Vector3::One * 3
			, eLayerType::BG);
		MeshRenderer* mr = mShadow->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_Shadow"));
		std::shared_ptr<Texture> texture
			= Resources::Load<Texture>(L"SHADOW", L"..\\Resources\\TEXTURE\\RAMONA\\Shadow.png");
		mShadow->GetComponent<Transform>()->SetScale((Vector3(texture.get()->GetImageRatioOfWidth() * 2.0f,
			texture.get()->GetImageRatioOfHeight() * 2.0f, 0.0f))
			* 1.0f);
#pragma endregion

#pragma region �ִϸ��̼�
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// �ִϸ��̼�
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"BOSS01_APPEAR", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\APPEAR\\BOSS01_APPEAR.png");
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->Create(L"R_APPEAR", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(3744.0f / 26.0f, 144.0f), 26);//, Vector2::Zero, 0.05f);
		at->Create(L"L_APPEAR", atlas, enums::eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(3744.0f / 26.0f, 144.0f), 26);

		atlas
			= Resources::Load<Texture>(L"BOSS01_DISAPPEAR", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\DISAPPEAR\\BOSS01_DISAPPEAR.png");
		at->Create(L"R_DISAPPEAR", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1872.0f / 13.0f, 144.0f), 13);
		at->Create(L"L_DISAPPEAR", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1872.0f / 13.0f, 144.0f), 13);

		atlas
			= Resources::Load<Texture>(L"BOSS01_IDLE", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\BASIC\\BOSS01_IDLE.png");
		at->Create(L"R_IDLE", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(864.0f / 6.0f, 144.0f), 6);
		at->Create(L"L_IDLE", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(864.0f / 6.0f, 144.0f), 6);

		atlas
			= Resources::Load<Texture>(L"BOSS01_WALK", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\BASIC\\BOSS01_WALK.png");
		at->Create(L"R_WALK", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1296.0f / 9.0f, 144.0f), 9);
		at->Create(L"L_WALK", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1296.0f / 9.0f, 144.0f), 9);

		atlas
			= Resources::Load<Texture>(L"BOSS01_RUN", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\BASIC\\BOSS01_RUN.png");
		at->Create(L"R_RUN", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1152.0f / 8.0f, 144.0f), 8);
		at->Create(L"L_RUN", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1152.0f / 8.0f, 144.0f), 8);

		atlas
			= Resources::Load<Texture>(L"BOSS01_DOWNED", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\BASIC\\BOSS01_DOWNED.png");
		at->Create(L"R_DOWNED", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);
		at->Create(L"L_DOWNED", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);

		atlas
			= Resources::Load<Texture>(L"BOSS01_GETUP", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\BASIC\\BOSS01_GETUP.png");
		at->Create(L"R_GETUP", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1584.0f / 11.0f, 144.0f), 1);
		at->Create(L"L_GETUP", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1584.0f / 11.0f, 144.0f), 11);

		atlas
			= Resources::Load<Texture>(L"BOSS01_GUARD", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\BASIC\\BOSS01_GUARD.png");
		at->Create(L"R_GUARD", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);
		at->Create(L"L_GUARD", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);

		atlas
			= Resources::Load<Texture>(L"BOSS01_ATTACK_PUNCH", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\ATTACK\\BOSS01_ATTACK_PUNCH.png");
		at->Create(L"R_ATTACK_PUNCH", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(2592.0f / 18.0f, 144.0f), 18);
		at->Create(L"L_ATTACK_PUNCH", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(2592.0f / 18.0f, 144.0f), 18);

		atlas
			= Resources::Load<Texture>(L"BOSS01_ATTACK_JUMPPUNCH_STR", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\ATTACK\\BOSS01_ATTACK_JUMPPUNCH_STR.png");
		at->Create(L"R_ATTACK_JUMPPUNCH_STR", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1440.0f / 10.0f, 144.0f), 10);
		at->Create(L"L_ATTACK_JUMPPUNCH_STR", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1440.0f / 10.0f, 144.0f), 10);

		atlas
			= Resources::Load<Texture>(L"BOSS01_ATTACK_JUMPPUNCH_ING", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\ATTACK\\BOSS01_ATTACK_JUMPPUNCH_ING.png");
		at->Create(L"R_ATTACK_JUMPPUNCH_ING", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(720.0f / 5.0f, 144.0f), 5);
		at->Create(L"L_ATTACK_JUMPPUNCH_ING", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(720.0f / 5.0f, 144.0f), 5);

		atlas
			= Resources::Load<Texture>(L"BOSS01_ATTACK_KICK", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\ATTACK\\BOSS01_ATTACK_KICK.png");
		at->Create(L"R_ATTACK_KICK", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(144.0f / 8.0f, 144.0f), 8);
		at->Create(L"L_ATTACK_KICK", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(144.0f / 8.0f, 144.0f), 8);

		atlas
			= Resources::Load<Texture>(L"BOSS01_ATTACK_FIRE", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\ATTACK\\BOSS01_ATTACK_FIRE.png");
		at->Create(L"R_ATTACK_FIRE", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(3024.0f / 14.0f, 216.0f), 14);
		at->Create(L"L_ATTACK_FIRE", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(3024.0f / 14.0f, 216.0f), 14);

		atlas
			= Resources::Load<Texture>(L"BOSS01_ATTACK_DOWNKICK", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\ATTACK\\BOSS01_ATTACK_DOWNKICK.png");
		at->Create(L"R_ATTACK_DOWNKICK", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);
		at->Create(L"L_ATTACK_DOWNKICK", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);

		atlas
			= Resources::Load<Texture>(L"BOSS01_ATTACK_SUPER_STR", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\ATTACK\\BOSS01_ATTACK_SUPER_STR.png");
		at->Create(L"R_ATTACK_SUPER_STR", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1008.0f / 7.0f, 432.0f), 7);
		at->Create(L"L_ATTACK_SUPER_STR", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1008.0f / 7.0f, 432.0f), 7);

		atlas
			= Resources::Load<Texture>(L"BOSS01_ATTACK_SUPER_ING", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\ATTACK\\BOSS01_ATTACK_SUPER_ING.png");
		at->Create(L"R_ATTACK_SUPER_ING", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(864.0f / 6.0f, 432.0f), 6);
		at->Create(L"L_ATTACK_SUPER_ING", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(864.0f / 6.0f, 432.0f), 6);

		atlas
			= Resources::Load<Texture>(L"BOSS01_ATTACK_SUPER_END", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\ATTACK\\BOSS01_ATTACK_SUPER_END.png");
		at->Create(L"R_ATTACK_SUPER_END", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(720.0f / 5.0f, 432.0f), 5);
		at->Create(L"L_ATTACK_SUPER_END", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(720.0f / 5.0f, 432.0f), 5);

		atlas
			= Resources::Load<Texture>(L"BOSS01_DAMAGE_STUN", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\DAMAGE\\BOSS01_DAMAGE_STUN.png");
		at->Create(L"R_DAMAGE_STUN", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);
		at->Create(L"L_DAMAGE_STUN", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);

		atlas
			= Resources::Load<Texture>(L"BOSS01_DAMAGE_KNOCKBACK", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\DAMAGE\\BOSS01_DAMAGE_KNOCKBACK.png");
		at->Create(L"R_DAMAGE_KNOCKBACK", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);
		at->Create(L"L_DAMAGE_KNOCKBACK", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);

		atlas
			= Resources::Load<Texture>(L"BOSS01_DAMAGE_KNOCKDOWN", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\DAMAGE\\BOSS01_DAMAGE_KNOCKDOWN.png");
		at->Create(L"R_DAMAGE_KNOCKDOWN", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1872.0f / 13.0f, 144.0f), 13);
		at->Create(L"L_DAMAGE_KNOCKDOWN", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1872.0f / 13.0f, 144.0f), 13);

		atlas
			= Resources::Load<Texture>(L"BOSS01_DAMAGE_DOWN", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\DAMAGE\\BOSS01_DAMAGE_DOWN.png");
		at->Create(L"R_DAMAGE_DOWN", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144), 4);
		at->Create(L"L_DAMAGE_DOWN", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144), 4);

#pragma endregion

#pragma region �̺�Ʈ
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// �̺�Ʈ 
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		at = GetOwner()->GetComponent<Animator>();

		//at->CompleteEvent(L"L_Attacked1") = std::bind(&Boss01Script::Attacked1Complete, this);
		//at->CompleteEvent(L"R_Attacked1") = std::bind(&Boss01Script::Attacked1Complete, this);

		at->CompleteEvent(L"L_DAMAGE_STUN") = std::bind(&Boss01Script::DamageStunComplete, this);
		at->CompleteEvent(L"R_DAMAGE_STUN") = std::bind(&Boss01Script::DamageStunComplete, this);
		at->CompleteEvent(L"L_DAMAGE_KNOCKBACK") = std::bind(&Boss01Script::DamageStunComplete, this);
		at->CompleteEvent(L"R_DAMAGE_KNOCKBACK") = std::bind(&Boss01Script::DamageStunComplete, this);
		//at->CompleteEvent(L"L_DAMAGE_KNOCKDOWN") = std::bind(&Boss01Script::DamageStunComplete, this);
		//at->CompleteEvent(L"R_DAMAGE_KNOCKDOWN") = std::bind(&Boss01Script::DamageStunComplete, this);
		at->CompleteEvent(L"L_DAMAGE_DOWN") = std::bind(&Boss01Script::DamageStunComplete, this);
		at->CompleteEvent(L"R_DAMAGE_DOWN") = std::bind(&Boss01Script::DamageStunComplete, this);

		at->CompleteEvent(L"L_ATTACK_PUNCH") = std::bind(&Boss01Script::CombatComplete, this);
		at->CompleteEvent(L"R_ATTACK_PUNCH") = std::bind(&Boss01Script::CombatComplete, this);
		at->CompleteEvent(L"L_ATTACK_JUMPPUNCH_STR") = std::bind(&Boss01Script::CombatComplete, this);
		at->CompleteEvent(L"R_ATTACK_JUMPPUNCH_STR") = std::bind(&Boss01Script::CombatComplete, this);
		at->CompleteEvent(L"L_ATTACK_JUMPPUNCH_ING") = std::bind(&Boss01Script::CombatComplete, this);
		at->CompleteEvent(L"R_ATTACK_JUMPPUNCH_ING") = std::bind(&Boss01Script::CombatComplete, this);
		at->CompleteEvent(L"L_ATTACK_KICK") = std::bind(&Boss01Script::CombatComplete, this);
		at->CompleteEvent(L"R_ATTACK_KICK") = std::bind(&Boss01Script::CombatComplete, this);
		at->CompleteEvent(L"L_ATTACK_FIRE") = std::bind(&Boss01Script::CombatComplete, this);
		at->CompleteEvent(L"R_ATTACK_FIRE") = std::bind(&Boss01Script::CombatComplete, this);
		at->CompleteEvent(L"L_ATTACK_DOWNKICK") = std::bind(&Boss01Script::CombatComplete, this);
		at->CompleteEvent(L"R_ATTACK_DOWNKICK") = std::bind(&Boss01Script::CombatComplete, this);

		//at->CompleteEvent(L"L_ATTACK_SUPER_STR") = std::bind(&Boss01Script::CombatComplete, this);
		//at->CompleteEvent(L"R_ATTACK_SUPER_STR") = std::bind(&Boss01Script::CombatComplete, this);
		//at->CompleteEvent(L"L_ATTACK_SUPER_ING") = std::bind(&Boss01Script::CombatComplete, this);
		//at->CompleteEvent(L"R_ATTACK_SUPER_ING") = std::bind(&Boss01Script::CombatComplete, this);
		//at->CompleteEvent(L"L_ATTACK_SUPER_END") = std::bind(&Boss01Script::CombatComplete, this);
		//at->CompleteEvent(L"R_ATTACK_SUPER_END") = std::bind(&Boss01Script::CombatComplete, this);

		at->CompleteEvent(L"L_GUARD") = std::bind(&Boss01Script::GuardComplete, this);
		at->CompleteEvent(L"R_GUARD") = std::bind(&Boss01Script::GuardComplete, this);

		at->CompleteEvent(L"L_DAMAGE_KNOCKDOWN") = std::bind(&Boss01Script::DamageKnockDownComplete, this);
		at->CompleteEvent(L"R_DAMAGE_KNOCKDOWN") = std::bind(&Boss01Script::DamageKnockDownComplete, this);

		at->CompleteEvent(L"L_DAMAGE_DOWN") = std::bind(&Boss01Script::DamageDownComplete, this);
		at->CompleteEvent(L"R_DAMAGE_DOWN") = std::bind(&Boss01Script::DamageDownComplete, this);

		at->CompleteEvent(L"L_DOWNED") = std::bind(&Boss01Script::DownedComplete, this);
		at->CompleteEvent(L"R_DOWNED") = std::bind(&Boss01Script::DownedComplete, this);

		at->CompleteEvent(L"L_GETUP") = std::bind(&Boss01Script::GetUpComplete, this);
		at->CompleteEvent(L"R_GETUP") = std::bind(&Boss01Script::GetUpComplete, this);


#pragma endregion

#pragma region �ݶ��̴�
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// �ݶ��̴�
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		mBodyCd = this->GetOwner()->AddComponent<Collider2D>();
		mBodyCd->SetSize(Vector2(0.2f, 0.2f));
		mBodyCd->SetIsBody(true);

		mSkillCd = this->GetOwner()->AddComponent<Collider2D>();
		mSkillCd->SetSize(Vector2(0.2f, 0.3f));
		mSkillCd->SetCenter(Vector2(0.3f, 0.0f));
		mSkillCd->SetActivation(eColliderActivation::InActive);

#pragma endregion

#pragma region �ʱ�ȭ
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// �ʱ�ȭ 
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// ó�� �����ϴ� ���� ����
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(0, 1);
		if (dist(mt) == 0)
		{
			mDirection = eDirection::L;
			mDirectionInt = -1;
		}
		else
		{
			mDirection = eDirection::R;
			mDirectionInt = +1;
		}

#pragma endregion

	}

	void Boss01Script::Update()
	{
#pragma region �����
		//std::wstring str = std::to_wstring(mHp);
		//ya::DebugLog::PrintDebugLog(L"mHp: " + str);

#pragma endregion

#pragma region FSM
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
													// FSM
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (mPrevState != mCurState)
		{
			switch (mCurState)
			{
			case eBoss01State::L_Appear:
				L_appear();
				break;
			case eBoss01State::R_Appear:
				R_appear();
				break;
			case eBoss01State::L_DisAppear:
				L_disAppear();
				break;
			case eBoss01State::R_DisAppear:
				R_disAppear();
				break;

			case eBoss01State::L_Idle:
				L_idle();
				break;
			case eBoss01State::R_Idle:
				R_idle();
				break;
			case eBoss01State::L_Walk:
				L_walk();
				break;
			case eBoss01State::R_Walk:
				R_walk();
				break;
			case eBoss01State::L_Run:
				L_run();
				break;
			case eBoss01State::R_Run:
				R_run();
				break;

			case eBoss01State::L_Downed:
				L_downed();
				break;
			case eBoss01State::R_Downed:
				R_downed();
				break;
			case eBoss01State::L_GetUp:
				L_getUp();
				break;
			case eBoss01State::R_GetUp:
				R_getUp();
				break;

			case eBoss01State::L_Guard:
				L_guard();
				break;
			case eBoss01State::R_Guard:
				R_guard();
				break;

			case eBoss01State::L_AttackPunch:
				L_attackPunch();
				break;
			case eBoss01State::R_AttackPunch:
				R_attackPunch();
				break;
			case eBoss01State::L_AttackJumpPunchStr:
				L_attackJumpPunchStr();
				break;
			case eBoss01State::R_AttackJumpPunchStr:
				R_attackJumpPunchStr();
				break;
			case eBoss01State::L_AttackJumpPunchIng:
				L_attackJumpPunchIng();
				break;
			case eBoss01State::R_AttackJumpPunchIng:
				R_attackJumpPunchIng();
				break;
			case eBoss01State::L_AttackKick:
				L_attackKick();
				break;
			case eBoss01State::R_AttackKick:
				R_attackKick();
				break;
			case eBoss01State::L_AttackFire:
				L_attackFire();
				break;
			case eBoss01State::R_AttackFire:
				R_attackFire();
				break;
			case eBoss01State::L_AttackDownKick:
				L_attackDownKick();
				break;
			case eBoss01State::R_AttackDownKick:
				R_attackDownKick();
				break;

			case eBoss01State::L_AttackSuperStr:
				L_attackSuperStr();
				break;
			case eBoss01State::R_AttackSuperStr:
				R_attackSuperStr();
				break;
			case eBoss01State::L_AttackSuperIng:
				L_attackSuperIng();
				break;
			case eBoss01State::R_AttackSuperIng:
				R_attackSuperIng();
				break;
			case eBoss01State::L_AttackSuperEnd:
				L_attackSuperEnd();
				break;
			case eBoss01State::R_AttackSuperEnd:
				R_attackSuperEnd();
				break;

			case eBoss01State::L_DamageStun:
				L_damageStun();
				break;
			case eBoss01State::R_DamageStun:
				R_damageStun();
				break;
			case eBoss01State::L_DamageKnockBack:
				L_damageKnockBack();
				break;
			case eBoss01State::R_DamageKnockBack:
				R_damageKnockBack();
				break;
			case eBoss01State::L_DamageKnockDown:
				L_damageKnockDown();
				break;
			case eBoss01State::R_DamageKnockDown:
				R_damageKnockDown();
				break;
			case eBoss01State::L_DamageDown:
				L_damageDown();
				break;
			case eBoss01State::R_DamageDown:
				R_damageDown();
				break;

			default:
				break;
			}
		}

		mPrevState = mCurState;

#pragma endregion

#pragma region �Ӽ�
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// �Ӽ� ������Ʈ
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ���� ��ġ ������Ʈ
		Transform* tr = this->GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		mPos = pos;

		// �÷��̾� ��ġ, ���� ������Ʈ
		if (PlayScene::IsPlayerExist())
		{
			mIsPlayerDead = PlayScene::IsPlayerDead();
			mPlayerPos = PlayScene::GetPlayerPosition();
			mPlayerDir = PlayScene::GetPlayerDirection();
		}

		// �״� ��� ������� ������ Ÿ��
		if (mIsDead == true)
		{
			mDeadTime -= Time::DeltaTime();
			if (mDeadTime <= 0.0f)
			{
				this->GetOwner()->SetState(ya::GameObject::eState::Dead);
			}
		}

#pragma endregion

#pragma region �׸���
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// �׸��� ������Ʈ
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		Transform* myTr = GetOwner()->GetComponent<Transform>();
		Vector3 myPos = myTr->GetPosition();
		myPos.y -= 0.5f;

		Transform* shadowTr = mShadow->GetComponent<Transform>();
		shadowTr->SetPosition(myPos);

		if (mDeadTime <= 0.1f)
		{
			mShadow->SetState(ya::GameObject::eState::Paused);
		}

#pragma endregion

#pragma region ����Ʈ
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// ����Ʈ ������Ʈ
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (mOnFlickering == true)
		{
			mFlickeringCurTime += Time::DeltaTime();
			mFlickeringMaxTime -= Time::DeltaTime();
			if (mFlickeringMaxTime <= 0.0f && GetOwner()->mIsEffectFlickering == false)
			{
				GetOwner()->mIsEffectFlickering = false;
				mOnFlickering = false;
			}

			else
			{
				if (GetOwner()->mIsEffectFlickering == true)
				{
					if (mFlickeringCurTime >= mFlickeringTickTime)
					{
						mFlickeringCurTime = 0.0f;
						GetOwner()->mIsEffectFlickering = false;
					}
				}
				if (GetOwner()->mIsEffectFlickering == false)
				{
					if (mFlickeringCurTime >= mFlickeringTickTime)
					{
						mFlickeringCurTime = 0.0f;
						GetOwner()->mIsEffectFlickering = true;
					}
				}
			}
		}

		if (mOnFlashing == true)
		{
			mFlashingCurTime += Time::DeltaTime();
			mFlashingMaxTime -= Time::DeltaTime();
			if (mFlashingMaxTime <= 0.0f && GetOwner()->mIsEffectFlashing == false)
			{
				GetOwner()->mIsEffectFlashing = false;
				mOnFlashing = false;
			}

			else
			{
				if (GetOwner()->mIsEffectFlashing == true)
				{
					if (mFlashingCurTime >= mFlashingTickTime)
					{
						mFlashingCurTime = 0.0f;
						GetOwner()->mIsEffectFlashing = false;
					}
				}
				if (GetOwner()->mIsEffectFlashing == false)
				{
					if (mFlashingCurTime >= mFlashingTickTime)
					{
						mFlashingCurTime = 0.0f;
						GetOwner()->mIsEffectFlashing = true;
					}
				}
			}
		}

#pragma endregion

#pragma region �ݶ��̴�
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// �ݶ��̴� ������Ʈ
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (mDirection == eDirection::L)
		{
			mSkillCd->SetCenter(Vector2(-0.3f, 0.0f));
		}
		else
		{
			mSkillCd->SetCenter(Vector2(0.3f, 0.0f));
		}

#pragma endregion

#pragma region AI
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// AI
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (mPhase == 0)
		{
			// ������ ���ϰ� ���� ���� �Ʒ��� ���� ��ȭ�� ������ �ȵ�
			// ���� ������ ���ϴ� ������ ���ļ� �Լ��� ��ü ����
			if (mIsDamageStun == false && mIsDamageKnockBack == false && mIsDamageKnockDown == false && mIsDamageDown == false
				&& mBodyCd->GetState() == eColliderState::NotColliding
				&& mIsDowned == false
				&& mIsGetup == false)
			{
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// Ž���Ÿ� �� �÷��̾� O
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if (IsPlayerInDetectionRange())// Ž���Ÿ� �� �÷��̾� O
				{
					if (mDetected == false)// ó�� �������� ���� ������ ���ǹ�
					{
						// �÷��̾� �� �������� ���� ����� ��
						if (mPlayerPos.x < mPos.x)
						{
							mDetected = true;
							mDirection = eDirection::L;
							ChangeState(eBoss01State::L_Idle);
						}
						else
						{
							mDetected = true;

							mDirection = eDirection::R;
							ChangeState(eBoss01State::R_Idle);
						}

						// �޷����� ������� ���� ����
						if (mRandWaitOrRun == -100)
						{
							std::mt19937 mt(rd());
							std::uniform_int_distribution<int> dist(0, 1);
							mRandWaitOrRun = dist(mt);

							// ������
							//mRandWaitOrRun = 1;// Wait
							//mRandWaitOrRun = 0;// Run
						}
					}

					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// Ž���Ÿ� �� �÷��̾� O �����Ÿ� �� �÷��̾� O
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if (IsPlayerInCombatRange())
					{
						if (mIsDamageStun == false && mIsDamageKnockBack == false && mIsDamageKnockDown == false && mIsDamageDown == false
							&& mIsDowned == false && mIsGetup == false
							&& mIsAttackPunch == false && mIsAttackJumpPunchStr == false && mIsAttackJumpPunchIng == false
							&& mIsAttackKick == false && mIsAttackFire == false
							&& mIsAttackDownKick == false
							&& mIsGuard == false)
							// Combat ����
						{
							// ó�� �������� ���� ������ ���ǹ�
							// �÷��̾� �� ���� �Ĵٺ���
							if (mIsCombat == false)
							{
								if (mPlayerPos.x < mPos.x)
								{
									mDirection = eDirection::L;
									ChangeState(eBoss01State::L_Idle);
								}
								else
								{
									mDirection = eDirection::R;
									ChangeState(eBoss01State::R_Idle);
								}

								// Combat ���� ���� �ʱ�ȭ ex. 2.0f
								// ��ǻ� mCombatTimer ������� �ʰ�
								// Combat���� ���� �ൿ
								mCombatTimer = 0.0f;
							}

							Combat();
						}
					}

					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// Ž���Ÿ� �� �÷��̾� O �����Ÿ� �� �÷��̾� X
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					else
					{
						mDetected = true;// �÷��̾� �� �������� ���� ���ֱ� ���� ó�� Detect �Ǵ� ���·� ��ȯ
						mIsCombat = false;

						//mCombatTimer = 0.0f;

						// �޷����� ���
						if (mRandWaitOrRun == 0)
						{
							// ���Ϳ� �÷��̾� ������ �Ÿ� ���
							Vector3 direction = mPlayerPos - mPos;
							direction.Normalize();

							// �÷��̾�� ���� ������ �Ÿ��� �ʹ� ������ ���߱�
							if (fabs(direction.x) < 0.05f)
							{
								if (mDirection == eDirection::L)
									ChangeState(eBoss01State::L_Idle);
								else
									ChangeState(eBoss01State::R_Idle);
							}
							else
							{
								// ���Ͱ� �÷��̾ ���� �̵��ϵ��� ����
								if (direction.x < 0 && (mCurState == eBoss01State::L_Idle || mCurState == eBoss01State::R_Idle || mCurState == eBoss01State::L_Run || mCurState == eBoss01State::R_Run))
								{
									mDirection = eDirection::L;
									ChangeState(eBoss01State::L_Run);

									mDirectionInt = -1;
									Transform* tr = this->GetOwner()->GetComponent<Transform>();
									Vector3 pos = tr->GetPosition();
									pos += direction * mRunSpeed * Time::DeltaTime();
									tr->SetPosition(pos);
								}
								else if (direction.x > 0 && (mCurState == eBoss01State::L_Idle || mCurState == eBoss01State::R_Idle || mCurState == eBoss01State::L_Run || mCurState == eBoss01State::R_Run))
								{
									mDirection = eDirection::R;
									ChangeState(eBoss01State::R_Run);

									mDirectionInt = +1;
									Transform* tr = this->GetOwner()->GetComponent<Transform>();
									Vector3 pos = tr->GetPosition();
									pos += direction * mRunSpeed * Time::DeltaTime();
									tr->SetPosition(pos);
								}
							}
						}

						// ����ϴ� ���
						else// (mRandWaitOrRun == +1)
						{
							if (mPlayerPos.x + 0.15f < mPos.x && (mCurState == eBoss01State::L_Idle || mCurState == eBoss01State::R_Idle || mCurState == eBoss01State::L_Run || mCurState == eBoss01State::R_Run))
							{
								mDirection = eDirection::L;
								ChangeState(eBoss01State::L_Idle);
							}
							else if (mPos.x < mPlayerPos.x - 0.15f && (mCurState == eBoss01State::L_Idle || mCurState == eBoss01State::R_Idle || mCurState == eBoss01State::L_Run || mCurState == eBoss01State::R_Run))
							{
								mDirection = eDirection::R;
								ChangeState(eBoss01State::R_Idle);
							}
						}

					}
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// Ž���Ÿ� �� �÷��̾� X && �����Ÿ� �� �÷��̾� X
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				else
				{
					// �ʱ�ȭ
					mDetected = false;
					mRandWaitOrRun = -100;


					// �̵� Ÿ�̸� ����
					mMoveTimer -= Time::DeltaTime();

					if (mMoveTimer <= 0.0f)
					{
						std::mt19937 mt(rd());
						std::uniform_int_distribution<int> dist(0, 1);

						// �����ϰ� �̵� ���� ����
						if (dist(mt) == 0)
						{
							mDirection = eDirection::L;
							mDirectionInt = -1;
						}
						else
						{
							mDirection = eDirection::R;
							mDirectionInt = +1;
						} // -1 �Ǵ� +1�� �����ϰ� ����

						// Ÿ�̸� �ʱ�ȭ
						mMoveTimer = mMoveInterval;
					}

					// ���� �̵� ����
					float moveDistance = GetRandomMoveDistance();
					Transform* tr = this->GetOwner()->GetComponent<Transform>();
					Vector3 pos = tr->GetPosition();
					pos.x += mDirectionInt * moveDistance * Time::DeltaTime();
					tr->SetPosition(pos);

					if (mDirectionInt == -1)
					{
						mDirection = eDirection::L;
						ChangeState(eBoss01State::L_Walk);
					}
					else
					{
						mDirection = eDirection::R;
						ChangeState(eBoss01State::R_Walk);
					}
				}
			}
		}

		else if (mPhase == 1)
		{

		}

		else if (mPhase == 2)
		{

		}

		else
		{

		}


#pragma endregion

#pragma region �浹���� ����ȭ
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// �浹
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// �浹���� �ʴ� ������ ��
		if (mBodyCd->GetState() == eColliderState::NotColliding)
		{
			mIsCollidingFirst = 0;
			mPlayerPreState = ePlayerState::R_Idle;
			mPlayerCurState = ePlayerState::R_Idle;
			mIsNormalAttackComboInit = false;
		}

		if (mSkillCd->GetState() == eColliderState::NotColliding)
		{
			mIsCollidingFirst = 0;
			mIsNormalAttackComboInit = false;
		}

		// mSkillCd Ȱ��ȭ ��Ȱ��ȭ ����
		if (mIsAttackPunch || mIsAttackJumpPunchIng || mIsAttackKick || mIsAttackFire || mIsAttackDownKick
			|| mIsAttackSuperIng)
		{
			mSkillCd->SetActivation(eColliderActivation::Active);
		}
		else
		{
			mSkillCd->SetActivation(eColliderActivation::InActive);
		}

#pragma endregion

#pragma region ���º��� ����ȭ
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// ���� bool ���� ����ȭ
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// ���� ���� ���� ����ȭ
		if (mCurState == eBoss01State::L_Guard || mCurState == eBoss01State::R_Guard)
		{
			mIsGuard = true;
		}
		else
		{
			mIsGuard = false;
		}

		// Attacked ���� ���� ����ȭ
		if (mCurState == eBoss01State::L_DamageStun || mCurState == eBoss01State::R_DamageStun)
		{
			if (mCurState == eBoss01State::L_DamageStun)
			{
				Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();
				rb->SetGround(true);
				rb->AddForce(Vector2(100.4f, 0.0f));
			}
			else
			{
				Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();
				rb->SetGround(true);
				rb->AddForce(Vector2(-100.4f, 0.0f));
			}

			mIsDamageStun = true;
		}
		else
		{
			mIsDamageStun = false;
		}

		if (mCurState == eBoss01State::L_DamageKnockBack || mCurState == eBoss01State::R_DamageKnockBack)
		{
			if (mCurState == eBoss01State::L_DamageKnockBack)
			{
				Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();
				rb->SetGround(true);
				rb->AddForce(Vector2(100.4f, 0.0f));
			}
			else
			{
				Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();
				rb->SetGround(true);
				rb->AddForce(Vector2(-100.4f, 0.0f));
			}

			mIsDamageKnockBack = true;
		}
		else
		{
			mIsDamageKnockBack = false;
		}

		if (mCurState == eBoss01State::L_DamageKnockDown || mCurState == eBoss01State::R_DamageKnockDown)
		{
			if (mCurState == eBoss01State::L_DamageKnockDown)
			{
				Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();
				rb->SetGround(true);
				rb->AddForce(Vector2(100.4f, 0.0f));
			}
			else
			{
				Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();
				rb->SetGround(true);
				rb->AddForce(Vector2(-100.4f, 0.0f));
			}

			mIsDamageKnockDown = true;
		}
		else
		{
			mIsDamageKnockDown = false;
		}

		if (mCurState == eBoss01State::L_DamageDown || mCurState == eBoss01State::R_DamageDown)
		{
			mIsDamageDown = true;
		}
		else
		{
			mIsDamageDown = false;
		}

		// Downed ���� ���� ����ȭ
		if (mCurState == eBoss01State::L_Downed || mCurState == eBoss01State::R_Downed)
		{
			mIsDowned = true;
		}
		else
		{
			mIsDowned = false;
		}

		// GetUp ���� ���� ����ȭ
		if (mCurState == eBoss01State::L_GetUp || mCurState == eBoss01State::R_GetUp)
		{
			mIsGetup = true;
		}
		else
		{
			mIsGetup = false;
		}

		// ���� ���� ���� ����ȭ
		if (mCurState == eBoss01State::L_AttackPunch || mCurState == eBoss01State::R_AttackPunch)
		{
			mIsAttackPunch = true;
		}
		else
		{
			mIsAttackPunch = false;
		}
		if (mCurState == eBoss01State::L_AttackJumpPunchStr || mCurState == eBoss01State::R_AttackJumpPunchStr)
		{
			mIsAttackJumpPunchStr = true;
		}
		else
		{
			mIsAttackJumpPunchStr = false;
		}
		if (mCurState == eBoss01State::L_AttackJumpPunchIng || mCurState == eBoss01State::R_AttackJumpPunchIng)
		{
			mIsAttackJumpPunchIng = true;
		}
		else
		{
			mIsAttackJumpPunchIng = false;
		}
		if (mCurState == eBoss01State::L_AttackKick || mCurState == eBoss01State::R_AttackKick)
		{
			mIsAttackKick = true;
		}
		else
		{
			mIsAttackKick = false;
		}
		if (mCurState == eBoss01State::L_AttackFire || mCurState == eBoss01State::R_AttackFire)
		{
			mIsAttackFire = true;
		}
		else
		{
			mIsAttackFire = false;
		}
		if (mCurState == eBoss01State::L_AttackDownKick || mCurState == eBoss01State::R_AttackDownKick)
		{
			mIsAttackDownKick = true;
		}
		else
		{
			mIsAttackDownKick = false;
		}
		if (mCurState == eBoss01State::L_AttackSuperStr || mCurState == eBoss01State::R_AttackSuperStr)
		{
			mIsAttackSuperStr = true;
		}
		else
		{
			mIsAttackSuperStr = false;
		}
		if (mCurState == eBoss01State::L_AttackSuperIng || mCurState == eBoss01State::R_AttackSuperIng)
		{
			mIsAttackSuperIng = true;
		}
		else
		{
			mIsAttackSuperIng = false;
		}
		if (mCurState == eBoss01State::L_AttackSuperEnd || mCurState == eBoss01State::R_AttackSuperEnd)
		{
			mIsAttackSuperEnd = true;
		}
		else
		{
			mIsAttackSuperEnd = false;
		}





#pragma endregion

#pragma region AttackState ����ȭ
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// ��ų ���� Update
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		mAttackState[0] = mIsAttackPunch;
		mAttackState[1] = mIsAttackJumpPunchIng;
		mAttackState[2] = mIsAttackKick;
		mAttackState[3] = mIsAttackFire;
		mAttackState[4] = mIsAttackDownKick;
		mAttackState[5] = mIsAttackSuperIng;

#pragma endregion

	}

#pragma region OnCollision
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// �浹
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void Boss01Script::OnCollisionEnter(Collider2D* other)
	{

	}

	void Boss01Script::OnCollisionStay(Collider2D* other)
	{
		if (dynamic_cast<PlayerScript*>(other->GetOwner()->GetComponent<PlayerScript>()))
			//if (other->GetOwner()->GetName() == L"Ramona")
		{
			if (other->GetOwner()->GetComponent<RamonaScript>()->IsDead() == true)
				return;

			if (this->GetOwner()->GetComponent<Collider2D>()->IsBody() == true && other->IsBody() == true)
				return;

			if (mCurState == eBoss01State::L_Guard || mCurState == eBoss01State::R_Guard
				|| mIsAttackPunch || mIsAttackJumpPunchIng || mIsAttackKick || mIsAttackFire || mIsAttackDownKick)
				return;

			if (mBodyCd->GetState() == eColliderState::IsColliding)
			{
				mRandWaitOrRun = 0;

				std::copy(other->GetOwner()->GetComponent<RamonaScript>()->GetAttackState().begin()
					, other->GetOwner()->GetComponent<RamonaScript>()->GetAttackState().end()
					, mPlayerAttackState.begin());

				if (mIsCollidingFirst == 0
					&& mIsDamageStun == false && mIsDamageKnockBack == false && mIsDamageKnockDown == false && mIsDamageDown == false
					&& mIsDowned == false
					&& mIsGetup == false
					&& mIsAttackPunch == false && mIsAttackJumpPunchIng == false && mIsAttackKick == false && mIsAttackFire == false && mIsAttackDownKick == false && mIsGuard == false
					&& mPlayerAttackState[17] == false)
					// ó�� �浹
					// + �浹 ����(�ٿ�Ǿ��ִµ� ���ڱ� ������ �޾Ҵٰ� �ؼ� Guard�� Idle�� �ٲ��� �ʱ� ���� ����)
					// ���� �浹 ������ ���� ������ ����
				{
					// ��� ��ų ������� ������ �������� ����
					std::mt19937 mt(rd());
					std::uniform_int_distribution<int> dist(0, 4);
					int randGuard = dist(mt);

					if (randGuard == 0)// ���� ���
					{
						if (mPlayerPos.x < mPos.x)
						{
							mDirection = eDirection::L;
							ChangeState(eBoss01State::L_Guard);

							mIsCollidingFirst = 1;
						}
						else
						{
							mDirection = eDirection::R;
							ChangeState(eBoss01State::R_Guard);

							mIsCollidingFirst = 1;
						}
					}
					else// ���� �̻�� == Attacked
					{
						other->GetOwner()->GetComponent<RamonaScript>()->AddSp(10);
						mHp -= mAttackedDamage;

						std::copy(other->GetOwner()->GetComponent<RamonaScript>()->GetAttackState().begin()
							, other->GetOwner()->GetComponent<RamonaScript>()->GetAttackState().end()
							, mPlayerAttackState.begin());

						SetAttackedState();
						mIsCollidingFirst = 1;
					}
				}
				else if (mIsCollidingFirst == 0 && mIsDowned == true// Downed ������ ���ϴ� ���ǹ�
					&& mIsDamageStun == false && mIsDamageKnockBack == false && mIsDamageKnockDown == false && mIsDamageDown == false
					&& mIsGetup == false
					&& mIsAttackPunch == false && mIsAttackJumpPunchIng == false && mIsAttackKick == false && mIsAttackFire == false && mIsAttackDownKick == false && mIsGuard == false
					&& mPlayerAttackState[17] == false)
				{
					if (mCanDamageDown == true)
					{
						//mHp -= mAttackedDamage;

						std::copy(other->GetOwner()->GetComponent<RamonaScript>()->GetAttackState().begin()
							, other->GetOwner()->GetComponent<RamonaScript>()->GetAttackState().end()
							, mPlayerAttackState.begin());

						SetAttackedState();
						mIsCollidingFirst = 1;
					}
				}
				else if (mIsCollidingFirst == 0 && mPlayerAttackState[17])
				{
					std::copy(other->GetOwner()->GetComponent<RamonaScript>()->GetAttackState().begin()
						, other->GetOwner()->GetComponent<RamonaScript>()->GetAttackState().end()
						, mPlayerAttackState.begin());

					SetAttackedState();
					mIsCollidingFirst = 1;
				}
			}
		}

		if (dynamic_cast<EnemyScript*>(other->GetOwner()->GetComponent<EnemyScript>()))
		{
			if (this->GetOwner()->GetComponent<Collider2D>()->IsBody() == true && other->IsBody() == true)
			{
				if (mBodyCd->GetState() == eColliderState::IsColliding)
				{
					if (mIsDowned || mIsGetup || mIsWalk || mIsRun)
						return;

					//Transform* obTr = other->GetOwner()->GetComponent<Transform>();
					//Vector3 obPos = obTr->GetPosition();

					//float displacement = other->GetOwner()->GetComponent<Transform>()->GetPosition().x
					//	- this->GetOwner()->GetComponent<Transform>()->GetPosition().x;
					//if (displacement > 0)
					//{
					//	obPos.x += 0.001f;
					//	obTr->SetPosition(obPos);
					//}
					//else
					//{
					//	obPos.x -= 0.001f;
					//	obTr->SetPosition(obPos);
					//}

					mRandWaitOrRun = 1;
				}
			}
		}
	}

	void Boss01Script::OnCollisionExit(Collider2D* other)
	{

	}

#pragma endregion

#pragma region �̺�Ʈ �Լ�
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// �̺�Ʈ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Boss01Script::CombatComplete()
	{
		mIsAttackPunch = false;
		mIsAttackJumpPunchStr = false;
		mIsAttackJumpPunchIng = false;
		mIsAttackKick = false;
		mIsAttackFire = false;
		mIsAttackDownKick = false;


		if (mPlayerPos.x < mPos.x)
			ChangeState(eBoss01State::L_Idle);
		else
			ChangeState(eBoss01State::R_Idle);

		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(0, 3);
		mCombatInterval = (float)(dist(mt) + 1.0f);
	}
	void Boss01Script::GuardComplete()
	{
		//������ �ϴ� �ش� ��ų�� duration�� �ٸ��� ������ duration ���� ���带 �����ϱ� ���� �κ�
		ePlayerState playerState = PlayScene::GetPlayerState();
		if (playerState == ePlayerState::L_Idle || playerState == ePlayerState::R_Idle
			|| playerState == ePlayerState::L_Walk || playerState == ePlayerState::R_Walk
			|| playerState == ePlayerState::L_Jump || playerState == ePlayerState::R_Jump
			|| playerState == ePlayerState::L_Run || playerState == ePlayerState::R_Run)
		{
			if (mPlayerPos.x < mPos.x)
				ChangeState(eBoss01State::L_Idle);
			else
				ChangeState(eBoss01State::R_Idle);
		}
		else
		{
			if (mPlayerPos.x < mPos.x)
				ChangeState(eBoss01State::L_Guard);
			else
				ChangeState(eBoss01State::R_Guard);
		}
	}
	void Boss01Script::DamageStunComplete()
	{
		mIsDamageStun = false;
		mIsDamageKnockBack = false;
		//mIsDamageKnockDown = false;
		mIsDamageDown = false;

		//mIsCollidingFirst = 0;

		if (mPlayerPos.x < mPos.x)
			ChangeState(eBoss01State::L_Idle);
		else
			ChangeState(eBoss01State::R_Idle);
	}
	void Boss01Script::DamageKnockDownComplete()
	{
		mIsDamageKnockDown = false;
		mIsDowned = true;

		mCanDamageDown = true;

		if (mHp <= 0.0f)
		{
			SetEffectFlickering(0.05f, mDeadTime);
		}

		if (mDirection == eDirection::L)
			ChangeState(eBoss01State::L_Downed);
		else
			ChangeState(eBoss01State::R_Downed);
	}
	void Boss01Script::DamageDownComplete()
	{
		mIsDamageDown = false;
		mIsDowned = true;

		mCanDamageDown = false;

		if (mHp <= 0.0f)
		{
			SetEffectFlickering(0.05f, mDeadTime);
			mIsDead = true;
		}

		if (mDirection == eDirection::L)
			ChangeState(eBoss01State::L_Downed);
		else
			ChangeState(eBoss01State::R_Downed);
	}
	void Boss01Script::DownedComplete()
	{
		if (mHp <= 0.0f)
		{
			mIsDead = true;
			return;
		}
		else
		{
			mIsDowned = false;
			mIsGetup = true;

			if (mDirection == eDirection::L)
				ChangeState(eBoss01State::L_GetUp);
			else
				ChangeState(eBoss01State::R_GetUp);
		}
	}
	void Boss01Script::GetUpComplete()
	{
		mIsGetup = false;

		if (mDirection == eDirection::L)
			ChangeState(eBoss01State::L_Idle);
		else
			ChangeState(eBoss01State::R_Idle);
	}

#pragma endregion

#pragma region �ִϸ��̼� �Լ�
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
													// ���� �ִϸ��̼� �Լ�
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void Boss01Script::L_appear()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_APPEAR", true);
	}
	void Boss01Script::R_appear()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_APPEAR", true);
	}
	void Boss01Script::L_disAppear()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_DISAPPEAR", true);
	}
	void Boss01Script::R_disAppear()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_DISAPPEAR", true);
	}
	void Boss01Script::L_idle()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_IDLE", true);
	}
	void Boss01Script::R_idle()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_IDLE", true);
	}
	void Boss01Script::L_walk()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_WALK", true);
	}
	void Boss01Script::R_walk()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_WALK", true);
	}
	void Boss01Script::L_run()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_RUN", true);
	}
	void Boss01Script::R_run()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_RUN", true);
	}
	void Boss01Script::L_downed()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_DOWNED", true);
	}
	void Boss01Script::R_downed()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_DOWNED", true);
	}
	void Boss01Script::L_getUp()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_GETUP", true);
	}
	void Boss01Script::R_getUp()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_GETUP", true);
	}
	void Boss01Script::L_guard()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_GUARD", true);
	}
	void Boss01Script::R_guard()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_GUARD", true);
	}
	void Boss01Script::L_attackPunch()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_ATTACK_PUNCH", true);
	}
	void Boss01Script::R_attackPunch()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_ATTACK_PUNCH", true);
	}
	void Boss01Script::L_attackJumpPunchStr()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_ATTACK_JUMPPUNCH_STR", true);
	}
	void Boss01Script::R_attackJumpPunchStr()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_ATTACK_JUMPPUNCH_STR", true);
	}
	void Boss01Script::L_attackJumpPunchIng()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_ATTACK_JUMPPUNCH_ING", true);
	}
	void Boss01Script::R_attackJumpPunchIng()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_ATTACK_JUMPPUNCH_ING", true);
	}
	void Boss01Script::L_attackKick()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_ATTACK_KICK", true);
	}
	void Boss01Script::R_attackKick()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_ATTACK_KICK", true);
	}
	void Boss01Script::L_attackFire()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_ATTACK_FIRE", true);
	}
	void Boss01Script::R_attackFire()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_ATTACK_FIRE", true);
	}
	void Boss01Script::L_attackDownKick()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_ATTACK_DOWNKICK", true);
	}
	void Boss01Script::R_attackDownKick()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_ATTACK_DOWNKICK", true);
	}
	void Boss01Script::L_attackSuperStr()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_ATTACK_SUPER_STR", true);
	}
	void Boss01Script::R_attackSuperStr()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_ATTACK_SUPER_STR", true);
	}
	void Boss01Script::L_attackSuperIng()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_ATTACK_SUPER_ING", true);
	}
	void Boss01Script::R_attackSuperIng()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_ATTACK_SUPER_ING", true);
	}
	void Boss01Script::L_attackSuperEnd()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_ATTACK_SUPER_END", true);
	}
	void Boss01Script::R_attackSuperEnd()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_ATTACK_SUPER_END", true);
	}
	void Boss01Script::L_damageStun()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_DAMAGE_STUN", true);
	}
	void Boss01Script::R_damageStun()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_DAMAGE_STUN", true);
	}
	void Boss01Script::L_damageKnockBack()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_DAMAGE_KNOCKBACK", true);
	}
	void Boss01Script::R_damageKnockBack()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_DAMAGE_KNOCKBACK", true);
	}
	void Boss01Script::L_damageKnockDown()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_DAMAGE_KNOCKDOWN", true);
	}
	void Boss01Script::R_damageKnockDown()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_DAMAGE_KNOCKDOWN", true);
	}
	void Boss01Script::L_damageDown()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_DAMAGE_DOWN", true);
	}
	void Boss01Script::R_damageDown()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_DAMAGE_DOWN", true);
	}


#pragma endregion

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// ���� ���� �Լ�
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void Boss01Script::Combat()
	{
		mIsCombat = true;

		mCombatTimer -= Time::DeltaTime();

		if (mCombatTimer <= 0.0f)
		{
			// ���� or ��� or ��� �� �ϳ��� �������� ����
			const int wait = 3;// wait�� ���� ���� ���� �� �� �ƴ� ����� Ȯ���� ������

			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> dist(0, (int)eBoss01CombatState::Guard + wait);
			int randStateNum = dist(mt);

			switch (static_cast<eBoss01CombatState>(randStateNum))
			{
			case eBoss01CombatState::AttackPunch:
				mIsAttackPunch = true;

				if (mPlayerPos.x < mPos.x)
					ChangeState(eBoss01State::L_AttackPunch);
				else
					ChangeState(eBoss01State::R_AttackPunch);
				break;

			case eBoss01CombatState::AttackJumpPunch:
				mIsAttackJumpPunchStr = true;

				if (mPlayerPos.x < mPos.x)
					//ChangeState(eBoss01State::L_AttackJumpPunchStr);
					ChangeState(eBoss01State::L_AttackJumpPunchIng);
				else
					//ChangeState(eBoss01State::R_AttackJumpPunchStr);
					ChangeState(eBoss01State::R_AttackJumpPunchIng);
				break;

			case eBoss01CombatState::AttackKick:
				mIsAttackKick = true;

				if (mPlayerPos.x < mPos.x)
					ChangeState(eBoss01State::L_AttackKick);
				else
					ChangeState(eBoss01State::R_AttackKick);
				break;

			case eBoss01CombatState::AttackFire:
				mIsAttackFire = true;

				if (mPlayerPos.x < mPos.x)
					ChangeState(eBoss01State::L_AttackFire);
				else
					ChangeState(eBoss01State::R_AttackFire);
				break;

			case eBoss01CombatState::Guard:
				mIsGuard = true;

				if (mPlayerPos.x < mPos.x)
					ChangeState(eBoss01State::L_Guard);
				else
					ChangeState(eBoss01State::R_Guard);
				break;

			default:
				break;
			}

			mCombatTimer = mCombatInterval;
		}
	}

	void Boss01Script::SetAttackedState()
	{
		// �÷��̾� ���� ��ų Ȯ��
		// �ش� �Լ� ������ OnCollisionStay���� ������Ʈ

		// �÷��̾� ���� ��ų�� �´� Attacked ���� ����
		// Stun (Attacked1) : mIsNormalAttack1 mIsNormalAttack2 mIsNormalAttack3 mIsRoundKickAttack
		// KnockBack (Attacked2) : mIsKickAttack mIsWeaponNormalAttack mIsWeaponSideAttack mIsWeaponStabAttack mIsRunJumpAttack mIsRunWeaponAttack
		// KnockDown (Attacked3) : mIsJumpDownAttack mIsJumpSlideAttack mIsRunSlideAttack mIsFireBall mIsSuper
		// Down (Attacked4) : mIsWeaponDownAttack (�ٿ� ���¿����� ���� ����, �ٿ� ���´� KnockDown�Ǿ� GetUp ���� ���¸� �ǹ�)

#pragma region bool ���� ����
// mAttackState[0] = mIsNormalAttack1;
// mAttackState[1] = mIsNormalAttack2;
// mAttackState[2] = mIsNormalAttack3;
// mAttackState[3] = mIsKickAttack;
// mAttackState[4] = mIsRoundKickAttack;
// mAttackState[5] = mIsBehindKickAttack;
// mAttackState[6] = mIsWeaponNormalAttack;
// mAttackState[7] = mIsWeaponDownAttack;
// mAttackState[8] = mIsWeaponSideAttack;
// mAttackState[9] = mIsWeaponStabAttack;
// mAttackState[10] = mIsJumpDownAttack;
// mAttackState[11] = mIsJumpSlideAttack;
// mAttackState[12] = mIsRunJumpAttack;
// mAttackState[13] = mIsRunWeaponAttack;
// mAttackState[14] = mIsRunSlideAttack;
// mAttackState[15] = mIsFireBall;
// mAttackState[16] = mIsSuper;
#pragma endregion

		if (mIsDowned)
			goto DOWNED_ATTACKED;

		if (mHp <= 0)
		{
			mIsDead = true;

			if (mPos.x < mPlayerPos.x)// �� - �÷��̾�
			{
				if (mIsDamageKnockDown == false)
				{
					ChangeState(eBoss01State::R_DamageKnockDown);
					mIsDamageKnockDown = true;
				}
			}
			else// �÷��̾� - ��
			{
				if (mIsDamageKnockDown == false)
				{
					ChangeState(eBoss01State::L_DamageKnockDown);
					mIsDamageKnockDown = true;
				}
			}
		}
		else
		{
			if (mPlayerAttackState[0] || mPlayerAttackState[1] || mPlayerAttackState[2] || mPlayerAttackState[4] || mPlayerAttackState[5])
			{
				//mHp -= 50.0f;

				if (mHp > 0.0f)
				{
					if (mPos.x < mPlayerPos.x)// �� - �÷��̾�
					{
						if (mIsDamageStun == false)
						{
							ChangeState(eBoss01State::R_DamageStun);
							mIsDamageStun = true;
						}
					}
					else// �÷��̾� - ��
					{
						if (mIsDamageStun == false)
						{
							ChangeState(eBoss01State::L_DamageStun);
							mIsDamageStun = true;
						}
					}
				}
			}

			else if (mPlayerAttackState[3] || mPlayerAttackState[6] || mPlayerAttackState[8] || mPlayerAttackState[9] || mPlayerAttackState[12] || mPlayerAttackState[13])
			{
				//mHp -= 50.0f;

				if (mHp > 0.0f)
				{
					if (mPos.x < mPlayerPos.x)// �� - �÷��̾�
					{
						if (mIsDamageKnockBack == false)
						{
							ChangeState(eBoss01State::L_DamageKnockBack);
							mIsDamageKnockBack = true;
						}
					}
					else// �÷��̾� - ��
					{
						if (mIsDamageKnockBack == false)
						{
							ChangeState(eBoss01State::R_DamageKnockBack);
							mIsDamageKnockBack = true;
						}
					}
				}
			}

			else if (mPlayerAttackState[10] || mPlayerAttackState[11] || mPlayerAttackState[14] || mPlayerAttackState[15] || mPlayerAttackState[16] || mPlayerAttackState[17])
			{
				//mHp -= 50.0f;

				if (mHp > 0.0f)
				{
					if (mPos.x < mPlayerPos.x)// �� - �÷��̾�
					{
						if (mIsDamageKnockDown == false)
						{
							ChangeState(eBoss01State::R_DamageKnockDown);
							mIsDamageKnockDown = true;
						}
					}
					else// �÷��̾� - ��
					{
						if (mIsDamageKnockDown == false)
						{
							ChangeState(eBoss01State::L_DamageKnockDown);
							mIsDamageKnockDown = true;
						}
					}
				}
			}
		}

	DOWNED_ATTACKED:
		if (mIsDowned == true &&
			(mPlayerAttackState[3] || mPlayerAttackState[4] || mPlayerAttackState[5] || mPlayerAttackState[6] || mPlayerAttackState[7]
				|| mPlayerAttackState[9] || mPlayerAttackState[10] || mPlayerAttackState[11] || mPlayerAttackState[12] || mPlayerAttackState[13]
				|| mPlayerAttackState[14] || mPlayerAttackState[15] || mPlayerAttackState[16]))
		{
			mHp -= mAttackedDamage;

			if (mHp >= 0.0f)
			{
				if (mPos.x < mPlayerPos.x)// �� - �÷��̾�
				{
					if (mIsDamageDown == false)
					{
						ChangeState(eBoss01State::R_DamageDown);
						mIsDamageDown = true;
					}
				}
				else// �÷��̾� - ��
				{
					if (mIsDamageDown == false)
					{
						ChangeState(eBoss01State::L_DamageDown);
						mIsDamageDown = true;
					}
				}
			}
		}
	}

	void Boss01Script::SetEffectFlickering(float tick, float duration)
	{
		GetOwner()->mIsEffectFlickering = true;
		mOnFlickering = true;
		mFlickeringCurTime = 0.0f;
		mFlickeringMaxTime = duration;
		mFlickeringTickTime = tick;
	}

	void Boss01Script::SetEffectFlashing(float tick, float duration, Vector4 color)
	{
		GetOwner()->mIsEffectFlashing = true;
		GetOwner()->mEffectColor = color;

		mOnFlashing = true;
		mFlashingCurTime = 0.0f;
		mFlashingMaxTime = duration;
		mFlashingTickTime = tick;
	}
}
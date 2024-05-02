#include "yaBoss01Script.h"
#include "yaCameraScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaPlayScene.h"
#include "yaBoss01Scene.h"
#include "yaCollider2D.h"
#include "yaRamonaScript.h"
#include "yaMinionScript.h"
#include "yaRigidbody.h"
#include "yaObject.h"
#include "yaMeshRenderer.h"
#include "..\\Editor_Window\\yaDebugLog.h"

#include "yaAudioListener.h"
#include "yaAudioClip.h"
#include "yaAudioSource.h"

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
#pragma region Minion
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// Minion
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			mMinion01 = object::Instantiate<GameObject>(Vector3(3.2f, 0.0f, 40.f)
				, Vector3::One * 3
				, eLayerType::Enemy);
			mMinion01->SetName(L"Minion01");

			MeshRenderer* mr = mMinion01->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"BASIC_MINION01_IDLE", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\MINION\\MINION_IDLE.png");
			Animator* at = mMinion01->AddComponent<Animator>();
			at->Create(L"Minion01_temp01", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(720.0f / 5.0f, 144.0f), 5);
			at->PlayAnimation(L"Minion01_temp01", true);

			Rigidbody* rb = mMinion01->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mMinion01->AddComponent<MinionScript>();
			mMinion01->GetComponent<MinionScript>()->SetInitRadian(0.0f);

			mMinion01->SetState(GameObject::eState::Paused);
		}
		{
			mMinion02 = object::Instantiate<GameObject>(Vector3(1.7f, 0.48f, 40.f)
				, Vector3::One * 3
				, eLayerType::Enemy);
			mMinion02->SetName(L"Minion02");

			MeshRenderer* mr = mMinion02->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"BASIC_MINION02_IDLE", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\MINION\\MINION_IDLE.png");
			Animator* at = mMinion02->AddComponent<Animator>();
			at->Create(L"Minion02_temp01", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(720.0f / 5.0f, 144.0f), 5);
			at->PlayAnimation(L"Minion02_temp01", true);

			Rigidbody* rb = mMinion02->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mMinion02->AddComponent<MinionScript>();
			mMinion02->GetComponent<MinionScript>()->SetInitRadian(2.0943f);

			mMinion02->SetState(GameObject::eState::Paused);
		}
		{
			mMinion03 = object::Instantiate<GameObject>(Vector3(1.8f, -0.43f, 40.f)
				, Vector3::One * 3
				, eLayerType::Enemy);
			mMinion03->SetName(L"Minion03");

			MeshRenderer* mr = mMinion03->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"BASIC_MINION03_IDLE", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\MINION\\MINION_IDLE.png");
			Animator* at = mMinion03->AddComponent<Animator>();
			at->Create(L"Minion03_temp01", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(720.0f / 5.0f, 144.0f), 5);
			at->PlayAnimation(L"Minion03_temp01", true);

			Rigidbody* rb = mMinion03->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mMinion03->AddComponent<MinionScript>();
			mMinion03->GetComponent<MinionScript>()->SetInitRadian(4.1887f);

			mMinion03->SetState(GameObject::eState::Paused);
		}
#pragma endregion

#pragma region 등장 이펙트
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																	// AppearEffect
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			mAppearEffect = object::Instantiate<GameObject>(Vector3(8.1f, 0.0f, 30.f)
				, Vector3::One * 3
				, eLayerType::Enemy);
			MeshRenderer* mr = mAppearEffect->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_AppearEffect"));
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BOSS01_APPEAR_EFFECT", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\APPEAR\\BOSS01_APPEAR_EFFECT.png");
			mAppearEffect->GetComponent<Transform>()->SetScale((Vector3(texture.get()->GetImageRatioOfWidth() * 2.0f,
				texture.get()->GetImageRatioOfHeight() * 2.0f, 0.0f))
				* 8.0f);
			mAppearEffect->SetState(GameObject::eState::Paused);

		}
#pragma endregion

#pragma region 그림자
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																	// 그림자
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
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
		}
#pragma endregion

#pragma region 애니메이션
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 애니메이션
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"BOSS01_APPEAR", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\APPEAR\\BOSS01_APPEAR.png");
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->Create(L"R_APPEAR", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(3744.0f / 26.0f, 144.0f), 26);//, Vector2::Zero, 0.05f);
		at->Create(L"L_APPEAR", atlas, enums::eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(3744.0f / 26.0f, 144.0f), 26);// duration 커지면 느려짐, duration 작으면 빨라짐

		atlas
			= Resources::Load<Texture>(L"BOSS01_APPEAR_WAIT", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\APPEAR\\BOSS01_APPEAR_WAIT.png");
		at->Create(L"R_APPEAR_WAIT", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(432.0f / 3.0f, 144.0f), 3);
		at->Create(L"L_APPEAR_WAIT", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(432.0f / 3.0f, 144.0f), 3);

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
		at->Create(L"R_DOWNED", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4, Vector2::Zero, 0.8f);
		at->Create(L"L_DOWNED", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4, Vector2::Zero, 0.8f);

		atlas
			= Resources::Load<Texture>(L"BOSS01_GETUP", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\BASIC\\BOSS01_GETUP.png");
		at->Create(L"R_GETUP", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1584.0f / 11.0f, 144.0f), 11);

		atlas
			= Resources::Load<Texture>(L"BOSS01_GETUP_L", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\BASIC\\BOSS01_GETUP_L.png");
		at->Create(L"L_GETUP", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1584.0f / 11.0f, 144.0f), 11);

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
		at->Create(L"R_ATTACK_FIRE", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(3024.0f / 14.0f, 216.0f), 14, Vector2::Zero, 0.08f);
		at->Create(L"L_ATTACK_FIRE", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(3024.0f / 14.0f, 216.0f), 14, Vector2::Zero, 0.08f);

		atlas
			= Resources::Load<Texture>(L"BOSS01_ATTACK_DOWNKICK", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\ATTACK\\BOSS01_ATTACK_DOWNKICK.png");
		at->Create(L"R_ATTACK_DOWNKICK", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);
		at->Create(L"L_ATTACK_DOWNKICK", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);

		atlas
			= Resources::Load<Texture>(L"BOSS01_ATTACK_SUPER_STR", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\ATTACK\\BOSS01_ATTACK_SUPER_STR.png");
		at->Create(L"R_ATTACK_SUPER_STR", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1008.0f / 7.0f, 432.0f), 7);
		at->Create(L"L_ATTACK_SUPER_STR", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1008.0f / 7.0f, 432.0f), 7);

		//atlas
		//	= Resources::Load<Texture>(L"BOSS01_ATTACK_SUPER_ING", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\ATTACK\\BOSS01_ATTACK_SUPER_ING.png");
		//at->Create(L"R_ATTACK_SUPER_ING", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(864.0f / 6.0f, 432.0f), 6);
		//at->Create(L"L_ATTACK_SUPER_ING", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(864.0f / 6.0f, 432.0f), 6);

		atlas
			= Resources::Load<Texture>(L"BOSS01_ATTACK_SUPER_ING", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\ATTACK\\BOSS01_ATTACK_SUPER_ING_s.png");
		at->Create(L"R_ATTACK_SUPER_ING", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(864.0f / 6.0f, 144.0f), 6);
		at->Create(L"L_ATTACK_SUPER_ING", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(864.0f / 6.0f, 144.0f), 6);

		atlas
			= Resources::Load<Texture>(L"BOSS01_ATTACK_SUPER_END", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\ATTACK\\BOSS01_ATTACK_SUPER_END.png");
		at->Create(L"R_ATTACK_SUPER_END", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(720.0f / 5.0f, 432.0f), 5, Vector2::Zero, 0.14f);
		at->Create(L"L_ATTACK_SUPER_END", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(720.0f / 5.0f, 432.0f), 5, Vector2::Zero, 0.14f);

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

#pragma region 이벤트
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 이벤트 
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		at = GetOwner()->GetComponent<Animator>();

		at->CompleteEvent(L"L_APPEAR") = std::bind(&Boss01Script::AppearComplete, this);
		at->CompleteEvent(L"R_APPEAR") = std::bind(&Boss01Script::AppearComplete, this);

		at->StartEvent(L"L_DAMAGE_STUN") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"R_DAMAGE_STUN") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"L_DAMAGE_KNOCKBACK") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"R_DAMAGE_KNOCKBACK") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"L_DAMAGE_KNOCKDOWN") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"R_DAMAGE_KNOCKDOWN") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"L_DAMAGE_DOWN") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"R_DAMAGE_DOWN") = std::bind(&Boss01Script::DamageStart, this);
		at->CompleteEvent(L"L_DAMAGE_STUN") = std::bind(&Boss01Script::DamageStunComplete, this);
		at->CompleteEvent(L"R_DAMAGE_STUN") = std::bind(&Boss01Script::DamageStunComplete, this);
		at->CompleteEvent(L"L_DAMAGE_KNOCKBACK") = std::bind(&Boss01Script::DamageStunComplete, this);
		at->CompleteEvent(L"R_DAMAGE_KNOCKBACK") = std::bind(&Boss01Script::DamageStunComplete, this);
		//at->CompleteEvent(L"L_DAMAGE_KNOCKDOWN") = std::bind(&Boss01Script::DamageStunComplete, this);
		//at->CompleteEvent(L"R_DAMAGE_KNOCKDOWN") = std::bind(&Boss01Script::DamageStunComplete, this);
		at->CompleteEvent(L"L_DAMAGE_DOWN") = std::bind(&Boss01Script::DamageStunComplete, this);
		at->CompleteEvent(L"R_DAMAGE_DOWN") = std::bind(&Boss01Script::DamageStunComplete, this);

		at->StartEvent(L"L_ATTACK_PUNCH") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"R_ATTACK_PUNCH") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"L_ATTACK_JUMPPUNCH_ING") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"L_ATTACK_JUMPPUNCH_ING") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"L_ATTACK_KICK") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"R_ATTACK_KICK") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"L_ATTACK_FIRE") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"R_ATTACK_FIRE") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"L_ATTACK_DOWNKICK") = std::bind(&Boss01Script::DamageStart, this);
		at->StartEvent(L"R_ATTACK_DOWNKICK") = std::bind(&Boss01Script::DamageStart, this);
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

		at->CompleteEvent(L"L_ATTACK_SUPER_STR") = std::bind(&Boss01Script::SuperStrComplete, this);
		at->CompleteEvent(L"R_ATTACK_SUPER_STR") = std::bind(&Boss01Script::SuperStrComplete, this);
		//at->CompleteEvent(L"L_ATTACK_SUPER_ING") = std::bind(&Boss01Script::CombatComplete, this);
		//at->CompleteEvent(L"R_ATTACK_SUPER_ING") = std::bind(&Boss01Script::CombatComplete, this);
		at->CompleteEvent(L"L_ATTACK_SUPER_END") = std::bind(&Boss01Script::SuperEndComplete, this);
		at->CompleteEvent(L"R_ATTACK_SUPER_END") = std::bind(&Boss01Script::SuperEndComplete, this);

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

		at->CompleteEvent(L"L_DISAPPEAR") = std::bind(&Boss01Script::DisAppearComplete, this);
		at->CompleteEvent(L"R_DISAPPEAR") = std::bind(&Boss01Script::DisAppearComplete, this);

#pragma endregion

#pragma region 콜라이더
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 콜라이더
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		mBodyCd = this->GetOwner()->AddComponent<Collider2D>();
		mBodyCd->SetSize(Vector2(0.2f, 0.2f));
		mBodyCd->SetIsBody(true);

		mSkillCd = this->GetOwner()->AddComponent<Collider2D>();
		mSkillCd->SetSize(Vector2(0.2f, 0.3f));
		mSkillCd->SetCenter(Vector2(0.3f, 0.0f));
		mSkillCd->SetActivation(eColliderActivation::InActive);

#pragma endregion

#pragma region 초기화 (ex. 초기 방향)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 초기화 
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 처음 시작하는 방향 랜덤
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

		// 사운드
		{
			mPunch01Sound = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 50.f)
				, Vector3::One
				, eLayerType::UI);
			AudioSource* as = mPunch01Sound->AddComponent<AudioSource>();

			mPunch02Sound = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 50.f)
				, Vector3::One
				, eLayerType::UI);
			as = mPunch02Sound->AddComponent<AudioSource>();

			mSwing01Sound = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 50.f)
				, Vector3::One
				, eLayerType::UI);
			as = mSwing01Sound->AddComponent<AudioSource>();
		}

	}

	void Boss01Script::Update()
	{
#pragma region 디버그

		//std::wstring str = std::to_wstring(mPhase);
		//ya::DebugLog::PrintDebugLog(L"mPhase: " + str);

		//std::wstring str1 = std::to_wstring(mMinion01->GetComponent<MinionScript>()->GetHp());
		//std::wstring str2 = std::to_wstring(mMinion02->GetComponent<MinionScript>()->GetHp());
		//std::wstring str3 = std::to_wstring(mMinion03->GetComponent<MinionScript>()->GetHp());
		//ya::DebugLog::PrintDebugLog(L"mHp: " + str1 + L" mHp: " + str2 + L" mHp: " + str3);

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
			case eBoss01State::L_AppearWait:
				L_appearWait();
				break;
			case eBoss01State::R_AppearWait:
				R_appearWait();
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

#pragma region 속성
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 속성 업데이트
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 본인 위치 업데이트
		Transform* tr = this->GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		mPos = pos;

		// 플레이어 위치, 방향 업데이트
		//if (PlayScene::IsPlayerExist())
		//{
		//	mIsPlayerDead = PlayScene::IsPlayerDead();
		//	mPlayerPos = PlayScene::GetPlayerPosition();
		//	mPlayerDir = PlayScene::GetPlayerDirection();
		//}
		if (Boss01Scene::IsPlayerExist())
		{
			mIsPlayerDead = Boss01Scene::IsPlayerDead();
			mPlayerPos = Boss01Scene::GetPlayerPosition();
			mPlayerDir = Boss01Scene::GetPlayerDirection();
		}

		// 죽는 경우 사라지기 전까지 타임
		if (mIsDead == true)
		{
			mDeadTime -= Time::DeltaTime();
			if (mDeadTime <= 0.0f)
			{
				this->GetOwner()->SetState(ya::GameObject::eState::Dead);
			}
		}

#pragma endregion

#pragma region 그림자
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 그림자 업데이트
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

#pragma region 이펙트
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 이펙트 업데이트
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

#pragma region 콜라이더
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 콜라이더 업데이트
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
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
													// 페이즈 0 (등장)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (mPhase == 0)
		{
			if (mLevelofPhase0 == 0)
			{
				// 등장 애니메
				ChangeState(eBoss01State::L_Appear);
			}
			else if (mLevelofPhase0 == 1)
			{
				// 등장 배경 띄우기
				mAppearEffect->SetState(GameObject::eState::Active);

				// 대기 애니메
				ChangeState(eBoss01State::L_AppearWait);

				if (mAppearEffect->GetState() == GameObject::eState::Active)
				{
					mLevelofPhase0 = 2;
				}
			}
			else if (mLevelofPhase0 == 2)
			{
				// 등장 배경 이동
				Transform* appearEffecttr = mAppearEffect->GetComponent<Transform>();
				Vector3 appearEffectpos = appearEffecttr->GetPosition();

				appearEffectpos.x -= 4.0f * Time::DeltaTime();

				appearEffecttr->SetPosition(appearEffectpos);

				if (appearEffectpos.x < -8.0f)
				{
					// Idle 애니메
					ChangeState(eBoss01State::L_Idle);

					mAppearEffect->SetState(GameObject::eState::Dead);

					mLevelofPhase0 = 3;
				}
			}
			else if (mLevelofPhase0 == 3)
			{
				mPhase = 1;
			}

		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// 페이즈 1 (보스 탐지)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (mPhase == 1)
		{
			if (mLevelofPhase1 == 0)
			{
				float hpPercent = static_cast<float>(mHp) / static_cast<float>(mMaxHp) * 100;
				if (hpPercent <= mToPhase02HpPercent)// 70퍼
				{
					mPhase = 2;
				}

				// 페이즈 1 AI

				// 공격을 당하고 있을 때는 아래의 상태 변화가 있으면 안됨
				// 추후 공격을 당하는 변수들 합쳐서 함수로 대체 예정
				if (mIsDamageStun == false && mIsDamageKnockBack == false && mIsDamageKnockDown == false && mIsDamageDown == false
					//&& mBodyCd->GetState() == eColliderState::NotColliding
					&& mIsDowned == false
					&& mIsGetup == false)
				{
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																	// 탐지거리 내 플레이어 O
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if (IsPlayerInDetectionRange())// 탐지거리 내 플레이어 O
					{
						if (mDetected == false)// 처음 감지했을 때만 들어오는 조건문
						{
							// 플레이어 쪽 방향으로 설정 해줘야 함
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

							// 달려갈지 대기할지 랜덤 설정
							if (mRandWaitOrRun == -100)
							{
								std::mt19937 mt(rd());
								std::uniform_int_distribution<int> dist(0, 2);
								mRandWaitOrRun = dist(mt);

								// 디버깅용
								//mRandWaitOrRun = 1;// Wait
								//mRandWaitOrRun = 0;// Run
							}
						}

						/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 탐지거리 내 플레이어 O 전투거리 내 플레이어 O
						/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						if (IsPlayerInCombatRange())
						{
							if (mIsDamageStun == false && mIsDamageKnockBack == false && mIsDamageKnockDown == false && mIsDamageDown == false
								&& mIsDowned == false && mIsGetup == false
								&& mIsAttackPunch == false && mIsAttackJumpPunchStr == false && mIsAttackJumpPunchIng == false
								&& mIsAttackKick == false && mIsAttackFire == false
								&& mIsAttackDownKick == false
								&& mIsGuard == false)
								// Combat 조건
							{
								// 처음 감지했을 때만 들어오는 조건문
								// 플레이어 쪽 방향 쳐다보기
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

									// Combat 관련 변수 초기화 ex. 2.0f
									// 사실상 mCombatTimer 사용하지 않고
									// Combat에서 랜덤 행동
									mCombatTimer = 0.0f;
								}

								Combat();
							}
						}

						/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 탐지거리 내 플레이어 O 전투거리 내 플레이어 X
						/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						else
						{
							mDetected = true;// 플레이어 쪽 방향으로 설정 해주기 위해 처음 Detect 되는 상태로 전환
							mIsCombat = false;

							//mCombatTimer = 0.0f;

							// 달려오는 경우
							if (mRandWaitOrRun == 0 || mRandWaitOrRun == 1)
							{
								// 몬스터와 플레이어 사이의 거리 계산
								Vector3 direction = mPlayerPos - mPos;
								direction.Normalize();

								// 플레이어와 몬스터 사이의 거리가 너무 작으면 멈추기
								if (fabs(direction.x) < 0.05f)
								{
									if (mDirection == eDirection::L)
										ChangeState(eBoss01State::L_Idle);
									else
										ChangeState(eBoss01State::R_Idle);
								}
								else
								{
									// 몬스터가 플레이어를 향해 이동하도록 설정
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

							// 대기하는 경우
							else// (mRandWaitOrRun == +1)
							{
								if (mPlayerPos.x + 0.05f < mPos.x && (mCurState == eBoss01State::L_Idle || mCurState == eBoss01State::R_Idle || mCurState == eBoss01State::L_Run || mCurState == eBoss01State::R_Run))
								{
									mDirection = eDirection::L;
									ChangeState(eBoss01State::L_Idle);
								}
								else if (mPos.x < mPlayerPos.x - 0.05f && (mCurState == eBoss01State::L_Idle || mCurState == eBoss01State::R_Idle || mCurState == eBoss01State::L_Run || mCurState == eBoss01State::R_Run))
								{
									mDirection = eDirection::R;
									ChangeState(eBoss01State::R_Idle);
								}
							}

						}
					}

					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 탐지거리 내 플레이어 X && 전투거리 내 플레이어 X
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					else
					{
						// 초기화
						mDetected = false;
						mRandWaitOrRun = -100;


						// 이동 타이머 감소
						mMoveTimer -= Time::DeltaTime();

						if (mMoveTimer <= 0.0f)
						{
							std::mt19937 mt(rd());
							std::uniform_int_distribution<int> dist(0, 1);

							// 랜덤하게 이동 방향 변경
							if (dist(mt) == 0)
							{
								mDirection = eDirection::L;
								mDirectionInt = -1;
							}
							else
							{
								mDirection = eDirection::R;
								mDirectionInt = +1;
							} // -1 또는 +1로 랜덤하게 설정

							// 타이머 초기화
							mMoveTimer = mMoveInterval;
						}

						// 랜덤 이동 로직
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

			else if (mLevelofPhase1 == 1)
			{

			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// 페이즈 2 (부하 빙빙)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (mPhase == 2)
		{
			if (mLevelofPhase2 == 0)
			{
				// 바꾸기 전 상태 준비
				// 콜라이더 끄기
				if(mBodyCd->GetActivation() == enums::eColliderActivation::Active)
				{
					mBodyCd->SetActivation(enums::eColliderActivation::InActive);
				}

				// 위치 이동
				Transform* tr = this->GetOwner()->GetComponent<Transform>();
				Vector3 currentPosition = tr->GetPosition();

				const Vector3 targetPosition = Vector3{ 2.2f, 0.0f, 0.0f };// 목표 지점
				const float moveDistance = 0.8f;// 간접 속도
				const float minDistanceToStop = 0.01f;// 목표지점 근접

				Vector3 direction = targetPosition - currentPosition;// 이동 방향
				direction.z = 0.0f;
				if (direction.Length() > minDistanceToStop)// 이동 진행
				{
					direction.Normalize();

					Vector3 movement = direction * moveDistance * Time::DeltaTime();// 이동량

					Vector3 newPosition = currentPosition + movement;
					newPosition.z = currentPosition.z;
					tr->SetPosition(newPosition);

					// 애니메
					Vector3 directionToTarget = targetPosition - currentPosition;
					if (0.0f < directionToTarget.x)// cur - target
					{
						mDirection = eDirection::R;
						ChangeState(eBoss01State::R_Run);
					}
					else
					{
						mDirection = eDirection::L;
						ChangeState(eBoss01State::L_Run);
					}
				}
				else// 이동 중단
				{
					// 이동을 중단하는 로직
					mLevelofPhase2 = 1;
				}
			}

			else if (mLevelofPhase2 == 1)
			{
				ChangeState(eBoss01State::L_AttackSuperStr);
			}

			else if (mLevelofPhase2 == 2)
			{
				// 기존 Scale 333에서 1.5배 확장
				Transform* tr = this->GetOwner()->GetComponent<Transform>();
				Vector3 size = tr->GetScale();
				if (size.x <= 3.0f * 1.5f || size.y <= 3.0f * 1.5f)
				{
					size.x *= 1.5f;
					size.y *= 1.5f;
					tr->SetScale(size);
				}

				ChangeState(eBoss01State::L_AttackSuperIng);

				if (mMinion01->GetState() == GameObject::eState::Paused && mMinion01->GetComponent<MinionScript>()->GetPhase() == (unsigned int)0
					&& mMinion02->GetState() == GameObject::eState::Paused && mMinion02->GetComponent<MinionScript>()->GetPhase() == (unsigned int)0
					&& mMinion03->GetState() == GameObject::eState::Paused && mMinion03->GetComponent<MinionScript>()->GetPhase() == (unsigned int)0)
				{
					mMinion01->SetState(GameObject::eState::Active);
					mMinion02->SetState(GameObject::eState::Active);
					mMinion03->SetState(GameObject::eState::Active);

					mMinion01->GetComponent<MinionScript>()->SetPhase((unsigned int)1);
					mMinion02->GetComponent<MinionScript>()->SetPhase((unsigned int)1);
					mMinion03->GetComponent<MinionScript>()->SetPhase((unsigned int)1);
				}

				if (mMinion01->GetComponent<MinionScript>()->GetHp() <= 0
					&& mMinion02->GetComponent<MinionScript>()->GetHp() <= 0
					&& mMinion03->GetComponent<MinionScript>()->GetHp() <= 0)
				{
					if (mMinion01->GetState() == GameObject::eState::Paused
						&& mMinion02->GetState() == GameObject::eState::Paused
						&& mMinion03->GetState() == GameObject::eState::Paused)
					{
						// 기존 Scale 333에서 1.5배 축소
						Transform* tr = this->GetOwner()->GetComponent<Transform>();
						Vector3 size = tr->GetScale();
						if (size.x != 3.0f || size.y != 3.0f)
						{
							size.x = 3.0f;
							size.y = 3.0f;
							tr->SetScale(size);
						}

						ChangeState(eBoss01State::L_AttackSuperEnd);

						// 콜라이더 켜기
						if (mBodyCd->GetActivation() == enums::eColliderActivation::InActive)
						{
							mBodyCd->SetActivation(enums::eColliderActivation::Active);
						}
					}
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
										// 페이즈 3 (보스 탐지) + 4 (부하 던지기로 안에 조건문 내부에 포함)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		else if (mPhase == 3 || mPhase == 4)
		{
			if (mLevelofPhase3 == 0)
			{
				float hpPercent = static_cast<float>(mHp) / static_cast<float>(mMaxHp) * 100;
				if (hpPercent <= mToPhase04HpPercent)// 50퍼
				{
					mPhase = 4;
				}

				// 페이즈 3 AI

				// 공격을 당하고 있을 때는 아래의 상태 변화가 있으면 안됨
				// 추후 공격을 당하는 변수들 합쳐서 함수로 대체 예정
				if (mIsDamageStun == false && mIsDamageKnockBack == false && mIsDamageKnockDown == false && mIsDamageDown == false
					//&& mBodyCd->GetState() == eColliderState::NotColliding
					&& mIsDowned == false
					&& mIsGetup == false)
				{
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																	// 탐지거리 내 플레이어 O
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if (IsPlayerInDetectionRange())// 탐지거리 내 플레이어 O
					{
						if (mDetected == false)// 처음 감지했을 때만 들어오는 조건문
						{
							// 플레이어 쪽 방향으로 설정 해줘야 함
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

							// 달려갈지 대기할지 랜덤 설정
							if (mRandWaitOrRun == -100)
							{
								//std::mt19937 mt(rd());
								//std::uniform_int_distribution<int> dist(0, 1);
								//mRandWaitOrRun = dist(mt);

								// 디버깅용
								//mRandWaitOrRun = 1;// Wait
								mRandWaitOrRun = 0;// Run
							}
						}

						/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 탐지거리 내 플레이어 O 전투거리 내 플레이어 O
						/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						if (IsPlayerInCombatRange())
						{
							if (mIsDamageStun == false && mIsDamageKnockBack == false && mIsDamageKnockDown == false && mIsDamageDown == false
								&& mIsDowned == false && mIsGetup == false
								&& mIsAttackPunch == false && mIsAttackJumpPunchStr == false && mIsAttackJumpPunchIng == false
								&& mIsAttackKick == false && mIsAttackFire == false
								&& mIsAttackDownKick == false
								&& mIsGuard == false)
								// Combat 조건
							{
								// 처음 감지했을 때만 들어오는 조건문
								// 플레이어 쪽 방향 쳐다보기
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

									// Combat 관련 변수 초기화 ex. 2.0f
									// 사실상 mCombatTimer 사용하지 않고
									// Combat에서 랜덤 행동
									mCombatTimer = 0.0f;
								}

								Combat();
							}
						}

						/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 탐지거리 내 플레이어 O 전투거리 내 플레이어 X
						/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						else
						{
							mDetected = true;// 플레이어 쪽 방향으로 설정 해주기 위해 처음 Detect 되는 상태로 전환
							mIsCombat = false;

							//mCombatTimer = 0.0f;

							// 달려오는 경우
							if (mRandWaitOrRun == 0 || mRandWaitOrRun == 1)
							{
								// 몬스터와 플레이어 사이의 거리 계산
								Vector3 direction = mPlayerPos - mPos;
								direction.Normalize();

								// 플레이어와 몬스터 사이의 거리가 너무 작으면 멈추기
								if (fabs(direction.x) < 0.05f)
								{
									if (mDirection == eDirection::L)
										ChangeState(eBoss01State::L_Idle);
									else
										ChangeState(eBoss01State::R_Idle);
								}
								else
								{
									// 몬스터가 플레이어를 향해 이동하도록 설정
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

							// 대기하는 경우
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
															// 탐지거리 내 플레이어 X && 전투거리 내 플레이어 X
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					else
					{
						// 초기화
						mDetected = false;
						mRandWaitOrRun = -100;


						// 이동 타이머 감소
						mMoveTimer -= Time::DeltaTime();

						if (mMoveTimer <= 0.0f)
						{
							std::mt19937 mt(rd());
							std::uniform_int_distribution<int> dist(0, 1);

							// 랜덤하게 이동 방향 변경
							if (dist(mt) == 0)
							{
								mDirection = eDirection::L;
								mDirectionInt = -1;
							}
							else
							{
								mDirection = eDirection::R;
								mDirectionInt = +1;
							} // -1 또는 +1로 랜덤하게 설정

							// 타이머 초기화
							mMoveTimer = mMoveInterval;
						}

						// 랜덤 이동 로직
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

			else if (mLevelofPhase3 == 1)
			{

			}

			else if (mLevelofPhase3 == 2)
			{

			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
											// 페이즈 4 (부하 던지기) + 페이즈 3 내부에 있으며, 보스 탐지
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (mPhase == 4)
			{
				if (mMinion01->GetState() == GameObject::eState::Paused && mMinion01->GetComponent<MinionScript>()->GetPhase() == (unsigned int)2
					&& mMinion02->GetState() == GameObject::eState::Paused && mMinion02->GetComponent<MinionScript>()->GetPhase() == (unsigned int)2)
				{
					mMinion01->SetState(GameObject::eState::Active);
					mMinion02->SetState(GameObject::eState::Active);

					Transform* minion01tr = mMinion01->GetComponent<Transform>();
					minion01tr->SetPosition(Vector3(2.0f, 1.0f, minion01tr->GetPosition().z));

					Transform* minion02tr = mMinion02->GetComponent<Transform>();
					minion02tr->SetPosition(Vector3(-2.0f, 1.0f, minion02tr->GetPosition().z));

					mMinion01->GetComponent<MinionScript>()->SetPhase((unsigned int)3);
					mMinion01->GetComponent<MinionScript>()->SetLevelPhase3((unsigned int)0);
					mMinion02->GetComponent<MinionScript>()->SetPhase((unsigned int)3);
					mMinion02->GetComponent<MinionScript>()->SetLevelPhase3((unsigned int)3);
				}

				float hpPercent = static_cast<float>(mHp) / static_cast<float>(mMaxHp) * 100;
				if (hpPercent <= mToPhase05HpPercent)// 0퍼
				{
					mPhase = 5;
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// 페이즈 5 (종료)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (mPhase == 5)// 보스 체력 0되면 5페이즈 전환 해줘야 함
		{
			// 부하 지워주는 부하의 4페이즈 호출
			mMinion01->GetComponent<MinionScript>()->SetPhase((unsigned int)4);
			mMinion02->GetComponent<MinionScript>()->SetPhase((unsigned int)4);
			//mMinion03->GetComponent<MinionScript>()->SetPhase((unsigned int)4);// 이미 Paused된 상태

			// 부하 지워지면, 본인도 지우기
			if (mMinion01->GetState() == GameObject::eState::Paused
				&& mMinion02->GetState() == GameObject::eState::Paused)
			{
				// 본인 애니메
				if (mDirection == eDirection::L)// 혹은 플레이어 위치와 비교
				{
					ChangeState(eBoss01State::L_DisAppear);
				}
				else
				{
					ChangeState(eBoss01State::R_DisAppear);
				}
			}

		}

		// 디버깅 용
		if (Input::GetKey(eKeyCode::I))
		{
			mPhase = 5;
		}

#pragma endregion

#pragma region 충돌관련 동기화
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 충돌
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 충돌하지 않는 상태일 때
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

		// mSkillCd 활성화 비활성화 조건
		if (mIsAttackPunch || mIsAttackJumpPunchIng || mIsAttackKick || mIsAttackFire || mIsAttackDownKick 
			|| mLevelofPhase2 == 1)
		{
			mSkillCd->SetActivation(eColliderActivation::Active);
		}
		else
		{
			mSkillCd->SetActivation(eColliderActivation::InActive);
		}

#pragma endregion

#pragma region 상태변수 동기화
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// 상태 bool 변수 동기화
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 가드 상태 변수 동기화
		if (mCurState == eBoss01State::L_Guard || mCurState == eBoss01State::R_Guard)
		{
			mIsGuard = true;
		}
		else
		{
			mIsGuard = false;
		}

		// Attacked 상태 변수 동기화
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
				rb->AddForce(Vector2(-100.4f, 0.0f));
			}
			else
			{
				Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();
				rb->SetGround(true);
				rb->AddForce(Vector2(100.4f, 0.0f));
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

		// Downed 상태 변수 동기화
		if (mCurState == eBoss01State::L_Downed || mCurState == eBoss01State::R_Downed)
		{
			mIsDowned = true;
		}
		else
		{
			mIsDowned = false;
		}

		// GetUp 상태 변수 동기화
		if (mCurState == eBoss01State::L_GetUp || mCurState == eBoss01State::R_GetUp)
		{
			mIsGetup = true;
		}
		else
		{
			mIsGetup = false;
		}

		// 공격 상태 변수 동기화
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

#pragma region AttackState 동기화
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// 스킬 상태 Update
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		mAttackState[0] = mIsAttackPunch;
		mAttackState[1] = mIsAttackJumpPunchIng;
		mAttackState[2] = mIsAttackKick;
		mAttackState[3] = mIsAttackFire;
		mAttackState[4] = mIsAttackDownKick;
		mAttackState[5] = mIsAttackSuperIng;
		
		mAttackState[9] = 1;// 보스와 전투중이란 것을 전달



#pragma endregion

	}

#pragma region OnCollision
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 충돌
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void Boss01Script::OnCollisionEnter(Collider2D* other)
	{

	}

	void Boss01Script::OnCollisionStay(Collider2D* other)
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 페이즈 0
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (mPhase == 0)
		{

		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 페이즈 2 
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (mPhase == 2)
		{
			if (dynamic_cast<PlayerScript*>(other->GetOwner()->GetComponent<PlayerScript>()))
			{
				if (other->GetOwner()->GetComponent<RamonaScript>()->IsDead() == true)
					return;

			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// 페이즈 1  3  4
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (mPhase == 1 || mPhase == 3 || mPhase == 4)
		{
			if (dynamic_cast<PlayerScript*>(other->GetOwner()->GetComponent<PlayerScript>()))
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
						// 처음 충돌
						// + 충돌 조건(다운되어있는데 갑자기 공격을 받았다고 해서 Guard나 Idle로 바뀌지 않기 위한 조건)
						// 추후 충돌 조건은 따로 정리할 예정
					{
						// 방어 스킬 사용할지 안할지 랜덤으로 실행
						std::mt19937 mt(rd());
						std::uniform_int_distribution<int> dist(0, 4);
						int randGuard = dist(mt);

						if (randGuard == 0)// 가드 사용
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
						else// 가드 미사용 == Attacked
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
					else if (mIsCollidingFirst == 0 && mIsDowned == true// Downed 공격을 당하는 조건문
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
	}

	void Boss01Script::OnCollisionExit(Collider2D* other)
	{

	}

#pragma endregion

#pragma region 이벤트 함수
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// 이벤트
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	void Boss01Script::AppearComplete()
	{
		mLevelofPhase0 = 1;
	}

	void Boss01Script::SuperStrComplete()
	{
		mLevelofPhase2 = 2;
	}

	void Boss01Script::SuperEndComplete()
	{
		mPhase = 3;
	}

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
		//막으려 하는 해당 스킬의 duration이 다르기 때문에 duration 까지 가드를 유지하기 위한 부분
		ePlayerState playerState = Boss01Scene::GetPlayerState();
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

		if (mPlayerPos.x < mPos.x)
		{
			ChangeState(eBoss01State::L_Downed);
			mDirection = eDirection::L;
		}
		else
		{
			ChangeState(eBoss01State::R_Downed);
			mDirection = eDirection::R;
		}
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

	void Boss01Script::DisAppearComplete()
	{
		// 끝
		// 종료
		// 마무리
		// 삭제
		// 죽음
		mIsDead = true;
		mShadow->SetState(GameObject::eState::Paused);
		this->GetOwner()->SetState(GameObject::eState::Paused);
	}

	void Boss01Script::AttackStart()
	{
		if(mCurState == eBoss01State::L_AttackPunch || mCurState == eBoss01State::R_AttackPunch)
		{
			AudioSource* as = mSwing01Sound->GetComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"swing03", L"..\\Resources\\Sound\\BATTLE\\swing03.mp3"));
			as->Play();
		}
		else
		{
			AudioSource* as = mSwing01Sound->GetComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"swing01", L"..\\Resources\\Sound\\BATTLE\\swing01.mp3"));
			as->Play();
		}
	}

	void Boss01Script::DamageStart()
	{
		if (mIsDamageKnockDown == true)
		{
			AudioSource* as = mPunch02Sound->GetComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"punch02", L"..\\Resources\\Sound\\BATTLE\\punch02.mp3"));
			as->Play();
		}
		else
		{
			AudioSource* as = mPunch01Sound->GetComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"punch01", L"..\\Resources\\Sound\\BATTLE\\punch01.mp3"));
			as->Play();
		}
	}

#pragma endregion

#pragma region 애니메이션 함수
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
													// 상태 애니메이션 함수
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
	void Boss01Script::L_appearWait()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_APPEAR_WAIT", true);
	}
	void Boss01Script::R_appearWait()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_APPEAR_WAIT", true);
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
														// 동작 내부 함수
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void Boss01Script::Combat()
	{
		mIsCombat = true;

		mCombatTimer -= Time::DeltaTime();

		if (mCombatTimer <= 0.0f)
		{
			// 공격 or 방어 or 대기 중 하나를 랜덤으로 실행
			const int wait = 3;// wait가 높을 수록 공격 및 방어가 아닌 대기할 확률이 높아짐

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
		// 플레이어 공격 스킬 확인
		// 해당 함수 직전에 OnCollisionStay에서 업데이트

		// 플레이어 공격 스킬에 맞는 Attacked 상태 설정
		// Stun (Attacked1) : mIsNormalAttack1 mIsNormalAttack2 mIsNormalAttack3 mIsRoundKickAttack
		// KnockBack (Attacked2) : mIsKickAttack mIsWeaponNormalAttack mIsWeaponSideAttack mIsWeaponStabAttack mIsRunJumpAttack mIsRunWeaponAttack
		// KnockDown (Attacked3) : mIsJumpDownAttack mIsJumpSlideAttack mIsRunSlideAttack mIsFireBall mIsSuper
		// Down (Attacked4) : mIsWeaponDownAttack (다운 상태에서만 공격 가능, 다운 상태는 KnockDown되어 GetUp 전의 상태를 의미)

#pragma region bool 변수 참고
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

			if (mPos.x < mPlayerPos.x)// 적 - 플레이어
			{
				if (mIsDamageKnockDown == false)
				{
					ChangeState(eBoss01State::R_DamageKnockDown);
					mIsDamageKnockDown = true;
				}
			}
			else// 플레이어 - 적
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
					if (mPos.x < mPlayerPos.x)// 적 - 플레이어
					{
						if (mIsDamageStun == false)
						{
							ChangeState(eBoss01State::R_DamageStun);
							mIsDamageStun = true;
						}
					}
					else// 플레이어 - 적
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
					if (mPos.x < mPlayerPos.x)// 적 - 플레이어
					{
						if (mIsDamageKnockBack == false)
						{
							ChangeState(eBoss01State::L_DamageKnockBack);
							mIsDamageKnockBack = true;
						}
					}
					else// 플레이어 - 적
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
					if (mPos.x < mPlayerPos.x)// 적 - 플레이어
					{
						if (mIsDamageKnockDown == false)
						{
							ChangeState(eBoss01State::R_DamageKnockDown);
							mIsDamageKnockDown = true;
						}
					}
					else// 플레이어 - 적
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
				if (mPos.x < mPlayerPos.x)// 적 - 플레이어
				{
					if (mIsDamageDown == false)
					{
						ChangeState(eBoss01State::R_DamageDown);
						mIsDamageDown = true;
					}
				}
				else// 플레이어 - 적
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
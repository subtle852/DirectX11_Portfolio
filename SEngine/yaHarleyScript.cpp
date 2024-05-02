#include "yaHarleyScript.h"
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

#include "yaAudioListener.h"
#include "yaAudioClip.h"
#include "yaAudioSource.h"

namespace ya
{
	HarleyScript::HarleyScript()
	{
		mAttackState.resize(10, false);
		mPlayerAttackState.resize(20, false);
	}

	HarleyScript::~HarleyScript()
	{
	}

	void HarleyScript::Initialize()
	{
#pragma region 그림자
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 그림자
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

#pragma region 애니메이션
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 애니메이션
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"Harley_Idle", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_IDLE.png");
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->Create(L"R_Idle", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4);
		at->Create(L"L_Idle", atlas, enums::eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4);

		atlas
			= Resources::Load<Texture>(L"Harley_Walk", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_WALK.png");
		at->Create(L"R_Walk", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 8);
		at->Create(L"L_Walk", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 8);

		atlas
			= Resources::Load<Texture>(L"Harley_Run", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_RUN.png");
		at->Create(L"R_Run", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 8);
		at->Create(L"L_Run", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 8);

		atlas
			= Resources::Load<Texture>(L"Harley_ArmAttack", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_ARM.png");
		at->Create(L"R_ArmAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 9);
		at->Create(L"L_ArmAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 9);

		atlas
			= Resources::Load<Texture>(L"Harley_KickAttack", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_KICK.png");
		at->Create(L"R_KickAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 0.15f);
		at->Create(L"L_KickAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 0.15f);

		atlas
			= Resources::Load<Texture>(L"Harley_SideKickAttack", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_SIDEKICK.png");
		at->Create(L"R_SideKickAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 7);
		at->Create(L"L_SideKickAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 7);

		atlas
			= Resources::Load<Texture>(L"Harley_UpperAttack", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_UPPER.png");
		at->Create(L"R_UpperAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 9);
		at->Create(L"L_UpperAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 9);

		atlas
			= Resources::Load<Texture>(L"Harley_Guard", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_GUARD.png");
		at->Create(L"R_Guard", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4);
		at->Create(L"L_Guard", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4);

		atlas
			= Resources::Load<Texture>(L"Harley_Attacked1", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_ATTACKED1.png");
		at->Create(L"R_Attacked1", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 0.15f);
		at->Create(L"L_Attacked1", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 0.15f);

		atlas
			= Resources::Load<Texture>(L"Harley_Attacked2", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_ATTACKED2.png");
		at->Create(L"R_Attacked2", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 0.15f);
		at->Create(L"L_Attacked2", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 0.15f);

		atlas
			= Resources::Load<Texture>(L"Harley_Attacked3", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_ATTACKED3.png");
		at->Create(L"R_Attacked3", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 14);
		at->Create(L"L_Attacked3", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 14);

		atlas
			= Resources::Load<Texture>(L"Harley_Attacked4", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_ATTACKED4.png");
		at->Create(L"R_Attacked4", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4);
		at->Create(L"L_Attacked4", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4);

		atlas
			= Resources::Load<Texture>(L"Harley_GetUp", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_GETUP.png");
		at->Create(L"R_GetUp", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 11, Vector2::Zero, 0.08f);
		at->Create(L"L_GetUp", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 11, Vector2::Zero, 0.08f);

		atlas
			= Resources::Load<Texture>(L"Harley_Downed", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_DEAD.png");
		at->Create(L"R_Downed", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 1.0f);
		at->Create(L"L_Downed", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 1.0f);

		atlas
			= Resources::Load<Texture>(L"Harley_Dead", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\HARLEY\\HARLEY_DEAD.png");
		at->Create(L"R_Dead", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 1.0f);
		at->Create(L"L_Dead", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 1.0f);

#pragma endregion

#pragma region 이벤트
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 이벤트 
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		at = GetOwner()->GetComponent<Animator>();

		at->StartEvent(L"L_Attacked1") = std::bind(&HarleyScript::AttackedStart, this);
		at->StartEvent(L"R_Attacked1") = std::bind(&HarleyScript::AttackedStart, this);
		at->StartEvent(L"L_Attacked2") = std::bind(&HarleyScript::AttackedStart, this);
		at->StartEvent(L"R_Attacked2") = std::bind(&HarleyScript::AttackedStart, this);
		at->StartEvent(L"L_Attacked3") = std::bind(&HarleyScript::AttackedStart, this);
		at->StartEvent(L"R_Attacked3") = std::bind(&HarleyScript::AttackedStart, this);
		at->StartEvent(L"L_Attacked4") = std::bind(&HarleyScript::AttackedStart, this);
		at->StartEvent(L"R_Attacked4") = std::bind(&HarleyScript::AttackedStart, this);
		at->CompleteEvent(L"L_Attacked1") = std::bind(&HarleyScript::Attacked1Complete, this);
		at->CompleteEvent(L"R_Attacked1") = std::bind(&HarleyScript::Attacked1Complete, this);
		at->CompleteEvent(L"L_Attacked2") = std::bind(&HarleyScript::Attacked1Complete, this);
		at->CompleteEvent(L"R_Attacked2") = std::bind(&HarleyScript::Attacked1Complete, this);
		//at->CompleteEvent(L"L_Attacked3") = std::bind(&HarleyScript::Attacked1Complete, this);
		//at->CompleteEvent(L"R_Attacked3") = std::bind(&HarleyScript::Attacked1Complete, this);
		at->CompleteEvent(L"L_Attacked4") = std::bind(&HarleyScript::Attacked1Complete, this);
		at->CompleteEvent(L"R_Attacked4") = std::bind(&HarleyScript::Attacked1Complete, this);

		at->CompleteEvent(L"L_Attacked3") = std::bind(&HarleyScript::Attacked3Complete, this);
		at->CompleteEvent(L"R_Attacked3") = std::bind(&HarleyScript::Attacked3Complete, this);
		at->CompleteEvent(L"L_Attacked4") = std::bind(&HarleyScript::Attacked4Complete, this);
		at->CompleteEvent(L"R_Attacked4") = std::bind(&HarleyScript::Attacked4Complete, this);

		at->StartEvent(L"L_ArmAttack") = std::bind(&HarleyScript::AttackStart, this);
		at->StartEvent(L"R_ArmAttack") = std::bind(&HarleyScript::AttackStart, this);
		at->StartEvent(L"L_KickAttack") = std::bind(&HarleyScript::AttackStart, this);
		at->StartEvent(L"R_KickAttack") = std::bind(&HarleyScript::AttackStart, this);
		at->StartEvent(L"L_SideKickAttack") = std::bind(&HarleyScript::AttackStart, this);
		at->StartEvent(L"R_SideKickAttack") = std::bind(&HarleyScript::AttackStart, this);
		at->StartEvent(L"L_UpperAttack") = std::bind(&HarleyScript::AttackStart, this);
		at->StartEvent(L"R_UpperAttack") = std::bind(&HarleyScript::AttackStart, this);
		at->CompleteEvent(L"L_ArmAttack") = std::bind(&HarleyScript::CombatComplete, this);
		at->CompleteEvent(L"R_ArmAttack") = std::bind(&HarleyScript::CombatComplete, this);
		at->CompleteEvent(L"L_KickAttack") = std::bind(&HarleyScript::CombatComplete, this);
		at->CompleteEvent(L"R_KickAttack") = std::bind(&HarleyScript::CombatComplete, this);
		at->CompleteEvent(L"L_SideKickAttack") = std::bind(&HarleyScript::CombatComplete, this);
		at->CompleteEvent(L"R_SideKickAttack") = std::bind(&HarleyScript::CombatComplete, this);
		at->CompleteEvent(L"L_UpperAttack") = std::bind(&HarleyScript::CombatComplete, this);
		at->CompleteEvent(L"R_UpperAttack") = std::bind(&HarleyScript::CombatComplete, this);

		at->CompleteEvent(L"L_Guard") = std::bind(&HarleyScript::GuardComplete, this);
		at->CompleteEvent(L"R_Guard") = std::bind(&HarleyScript::GuardComplete, this);

		at->CompleteEvent(L"L_Downed") = std::bind(&HarleyScript::DownedComplete, this);
		at->CompleteEvent(L"R_Downed") = std::bind(&HarleyScript::DownedComplete, this);

		at->CompleteEvent(L"L_GetUp") = std::bind(&HarleyScript::GetUpComplete, this);
		at->CompleteEvent(L"R_GetUp") = std::bind(&HarleyScript::GetUpComplete, this);

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

#pragma region 초기화
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

	void HarleyScript::Update()
	{
#pragma region 디버그
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
			case eLukeState::L_Idle:
				L_idle();
				break;
			case eLukeState::R_Idle:
				R_idle();
				break;

				//case eLukeState::L_Angry:
				//	L_angry();
				//	break;
				//case eLukeState::R_Angry:
				//	R_angry();
				//	break;

			case eLukeState::L_Walk:
				L_walk();
				break;
			case eLukeState::R_Walk:
				R_walk();
				break;

			case eLukeState::L_Run:
				L_run();
				break;
			case eLukeState::R_Run:
				R_run();
				break;

			case eLukeState::L_ArmAttack:
				L_armattack();
				break;
			case eLukeState::R_ArmAttack:
				R_armattack();
				break;
			case eLukeState::L_KickAttack:
				L_kickattack();
				break;
			case eLukeState::R_KickAttack:
				R_kickattack();
				break;
			case eLukeState::L_SideKickAttack:
				L_sidekickattack();
				break;
			case eLukeState::R_SideKickAttack:
				R_sidekickattack();
				break;
			case eLukeState::L_UpperAttack:
				L_upperattack();
				break;
			case eLukeState::R_UpperAttack:
				R_upperattack();
				break;

			case eLukeState::L_Guard:
				L_guard();
				break;
			case eLukeState::R_Guard:
				R_guard();
				break;

			case eLukeState::L_Attacked1:
				L_attacked1();
				break;
			case eLukeState::R_Attacked1:
				R_attacked1();
				break;
			case eLukeState::L_Attacked2:
				L_attacked2();
				break;
			case eLukeState::R_Attacked2:
				R_attacked2();
				break;
			case eLukeState::L_Attacked3:
				L_attacked3();
				break;
			case eLukeState::R_Attacked3:
				R_attacked3();
				break;
			case eLukeState::L_Attacked4:
				L_attacked4();
				break;
			case eLukeState::R_Attacked4:
				R_attacked4();
				break;

			case eLukeState::L_GetUp:
				L_getup();
				break;
			case eLukeState::R_GetUp:
				R_getup();
				break;

			case eLukeState::L_Downed:
				L_downed();
				break;
			case eLukeState::R_Downed:
				R_downed();
				break;

			case eLukeState::L_Dead:
				L_dead();
				break;
			case eLukeState::R_Dead:
				R_dead();
				break;

				//case eLukeState::L_Flying:
				//	L_flying();
				//	break;
				//case eLukeState::R_Flying:
				//	R_flying();
				//	break;
				//case eLukeState::L_Raiding:
				//	L_raiding();
				//	break;
				//case eLukeState::R_Raiding:
				//	R_raiding();
				//	break;

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
		// 본인 위치 y값에 따른 z값 보간 수정
		{
			Transform* tr = this->GetOwner()->GetComponent<Transform>();
			float y = tr->GetPosition().y;

			float t = (y + 1.4f) / 1.8f; // -1.4부터 0.4까지의 범위
			float z = ZValueLerp(40.0f, 45.0f, t);

			// 현재 위치의 x와 y는 그대로 유지하고 z 값만 변경
			tr->SetPosition(Vector3(tr->GetPosition().x, tr->GetPosition().y, z));
		}
		
		// 본인 위치 업데이트
		Transform* tr = this->GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		mPos = pos;

		// 플레이어 위치, 방향 업데이트
		if (PlayScene::IsPlayerExist())
		{
			mIsPlayerDead = PlayScene::IsPlayerDead();
			mPlayerPos = PlayScene::GetPlayerPosition();
			mPlayerDir = PlayScene::GetPlayerDirection();
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

		// 공격을 당하고 있을 때는 아래의 상태 변화가 있으면 안됨
		// 추후 공격을 당하는 변수들 합쳐서 함수로 대체 예정
		if (mIsAttacked1 == false && mIsAttacked2 == false && mIsAttacked3 == false && mIsAttacked4 == false
			//&& mBodyCd->GetState() == eColliderState::NotColliding
			&& mIsDowned == false
			&& mIsGetUp == false
			&& abs(mPlayerPos.x - mPos.x) <= 5.0f)
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
						ChangeState(eLukeState::L_Idle);
					}
					else
					{
						mDetected = true;

						mDirection = eDirection::R;
						ChangeState(eLukeState::R_Idle);
					}

					// 달려갈지 대기할지 랜덤 설정
					if (mRandWaitOrRun == -100)
					{
						std::mt19937 mt(rd());
						std::uniform_int_distribution<int> dist(0, 1);
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
					if (mIsAttacked1 == false && mIsAttacked2 == false && mIsAttacked3 == false && mIsAttacked4 == false
						&& mIsDowned == false && mIsGetUp == false
						&& mIsArm == false && mIsKick == false && mIsSideKick == false && mIsUpper == false && mIsGuard == false)
						// Combat 조건
					{
						// 처음 감지했을 때만 들어오는 조건문
						// 플레이어 쪽 방향 쳐다보기
						if (mIsCombat == false)
						{
							if (mPlayerPos.x < mPos.x)
							{
								mDirection = eDirection::L;
								ChangeState(eLukeState::L_Idle);
							}
							else
							{
								mDirection = eDirection::R;
								ChangeState(eLukeState::R_Idle);
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
					if (mRandWaitOrRun == 0)
					{
						// 추후, 해당 조건문 CanRun or CanChase(Chase로 한다면, Run 변수들 네이밍 Chase로 바꿔줘야 함)로 묶을 예정
						// Combat에서 공격 스킬이 나가는 도중에
						// 플레이어가 전투거리에서 나갈 때,
						// 해당 스킬은 마저 실행하고 달려가야 하기 때문에 아래와 같은 조건문이 필요

						 // 몬스터와 플레이어 사이의 거리 계산
						Vector3 direction = mPlayerPos - mPos;
						direction.z = 0.0f;
						direction.Normalize();

						// 플레이어와 몬스터 사이의 거리가 너무 작으면 멈추기
						if (fabs(direction.x) < 0.05f)
						{
							if (mDirection == eDirection::L)
								ChangeState(eLukeState::L_Idle);
							else
								ChangeState(eLukeState::R_Idle);
						}
						else
						{
							// 몬스터가 플레이어를 향해 이동하도록 설정
							if (direction.x < 0 && (mCurState == eLukeState::L_Idle || mCurState == eLukeState::R_Idle || mCurState == eLukeState::L_Run || mCurState == eLukeState::R_Run))
							{
								mDirection = eDirection::L;
								ChangeState(eLukeState::L_Run);

								mDirectionInt = -1;
								Transform* tr = this->GetOwner()->GetComponent<Transform>();
								Vector3 pos = tr->GetPosition();
								pos += direction * mRunSpeed * Time::DeltaTime();
								tr->SetPosition(pos);
							}
							else if (direction.x > 0 && (mCurState == eLukeState::L_Idle || mCurState == eLukeState::R_Idle || mCurState == eLukeState::L_Run || mCurState == eLukeState::R_Run))
							{
								mDirection = eDirection::R;
								ChangeState(eLukeState::R_Run);

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
						if (mPlayerPos.x + 0.05f < mPos.x && (mCurState == eLukeState::L_Idle || mCurState == eLukeState::R_Idle || mCurState == eLukeState::L_Run || mCurState == eLukeState::R_Run))
						{
							mDirection = eDirection::L;
							ChangeState(eLukeState::L_Idle);
						}
						else if (mPos.x < mPlayerPos.x - 0.05f && (mCurState == eLukeState::L_Idle || mCurState == eLukeState::R_Idle || mCurState == eLukeState::L_Run || mCurState == eLukeState::R_Run))
						{
							mDirection = eDirection::R;
							ChangeState(eLukeState::R_Idle);
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
					//if (rand() % 2 == 0)
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
					ChangeState(eLukeState::L_Walk);
				}
				else
				{
					mDirection = eDirection::R;
					ChangeState(eLukeState::R_Walk);
				}
			}
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

		//// mBodyCd 활성화 비활성화 조건
		//if (mCurState == eLukeState::L_Guard || mCurState == eLukeState::R_Guard
		//	|| mIsArm || mIsKick || mIsSideKick || mIsUpper)
		//	//|| mIsAttacked1 || mIsAttacked2 || mIsAttacked3 || mIsAttacked4)
		//	// 가드가 붙은 스킬아냐 아니냐로 구분을 해서 적용을 할지 고민중
		//	// 가드를 하고 있다가 바로 스킬을 쓴다면, 계속 무적이고 플레이어의 공격상태와 겹치게 되면 상황이 애매해짐 
		//{
		//	mBodyCd->SetActivation(eColliderActivation::InActive);
		//}
		//else
		//{
		//	mBodyCd->SetActivation(eColliderActivation::Active);
		//}

		// mSkillCd 활성화 비활성화 조건
		if (mIsArm || mIsKick || mIsSideKick || mIsUpper)
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
		if (mCurState == eLukeState::L_Guard || mCurState == eLukeState::R_Guard)
		{
			mIsGuard = true;
		}
		else
		{
			mIsGuard = false;
		}

		// Attacked 상태 변수 동기화
		if (mCurState == eLukeState::L_Attacked1 || mCurState == eLukeState::R_Attacked1)
		{
			if (mCurState == eLukeState::L_Attacked1)
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

			mIsAttacked1 = true;
		}
		else
		{
			mIsAttacked1 = false;
		}

		if (mCurState == eLukeState::L_Attacked2 || mCurState == eLukeState::R_Attacked2)
		{
			if (mCurState == eLukeState::L_Attacked2)
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

			mIsAttacked2 = true;
		}
		else
		{
			mIsAttacked2 = false;
		}

		if (mCurState == eLukeState::L_Attacked3 || mCurState == eLukeState::R_Attacked3)
		{
			if (mCurState == eLukeState::L_Attacked3)
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

			mIsAttacked3 = true;
		}
		else
		{
			mIsAttacked3 = false;
		}

		if (mCurState == eLukeState::L_Attacked4 || mCurState == eLukeState::R_Attacked4)
		{
			mIsAttacked4 = true;
		}
		else
		{
			mIsAttacked4 = false;
		}

		// Downed 상태 변수 동기화
		if (mCurState == eLukeState::L_Downed || mCurState == eLukeState::R_Downed)
		{
			mIsDowned = true;
		}
		else
		{
			mIsDowned = false;
		}

		// GetUp 상태 변수 동기화
		if (mCurState == eLukeState::L_GetUp || mCurState == eLukeState::R_GetUp)
		{
			mIsGetUp = true;
		}
		else
		{
			mIsGetUp = false;
		}

		// 공격 상태 변수 동기화
		if (mCurState == eLukeState::L_ArmAttack || mCurState == eLukeState::R_ArmAttack)
		{
			mIsArm = true;
		}
		else
		{
			mIsArm = false;
		}
		if (mCurState == eLukeState::L_KickAttack || mCurState == eLukeState::R_KickAttack)
		{
			mIsKick = true;
		}
		else
		{
			mIsKick = false;
		}
		if (mCurState == eLukeState::L_SideKickAttack || mCurState == eLukeState::R_SideKickAttack)
		{
			mIsSideKick = true;
		}
		else
		{
			mIsSideKick = false;
		}
		if (mCurState == eLukeState::L_UpperAttack || mCurState == eLukeState::R_UpperAttack)
		{
			mIsUpper = true;
		}
		else
		{
			mIsUpper = false;
		}

#pragma endregion

#pragma region AttackState 동기화
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// 스킬 상태 Update
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		mAttackState[0] = mIsArm;
		mAttackState[1] = mIsKick;
		mAttackState[2] = mIsSideKick;
		mAttackState[3] = mIsUpper;

#pragma endregion

	}

#pragma region OnCollision
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 충돌
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void HarleyScript::OnCollisionEnter(Collider2D* other)
	{

	}

	void HarleyScript::OnCollisionStay(Collider2D* other)
	{
		if (dynamic_cast<PlayerScript*>(other->GetOwner()->GetComponent<PlayerScript>()))
			//if (other->GetOwner()->GetName() == L"Ramona")
		{
			if (other->GetOwner()->GetComponent<RamonaScript>()->IsDead() == true)
				return;

			if (this->GetOwner()->GetComponent<Collider2D>()->IsBody() == true && other->IsBody() == true)
				return;

			if (mCurState == eLukeState::L_Guard || mCurState == eLukeState::R_Guard
				|| mIsArm || mIsKick || mIsSideKick || mIsUpper)
				return;

			if (mBodyCd->GetState() == eColliderState::IsColliding)
			{
				mRandWaitOrRun = 0;

				std::copy(other->GetOwner()->GetComponent<RamonaScript>()->GetAttackState().begin()
					, other->GetOwner()->GetComponent<RamonaScript>()->GetAttackState().end()
					, mPlayerAttackState.begin());

				if (mIsCollidingFirst == 0
					&& mIsAttacked1 == false && mIsAttacked2 == false && mIsAttacked3 == false && mIsAttacked4 == false
					&& mIsDowned == false
					&& mIsGetUp == false
					&& mIsArm == false && mIsKick == false && mIsSideKick == false && mIsUpper == false && mIsGuard == false
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
							ChangeState(eLukeState::L_Guard);

							mIsCollidingFirst = 1;
						}
						else
						{
							mDirection = eDirection::R;
							ChangeState(eLukeState::R_Guard);

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
					&& mIsAttacked1 == false && mIsAttacked2 == false && mIsAttacked3 == false && mIsAttacked4 == false
					&& mIsGetUp == false
					&& mIsArm == false && mIsKick == false && mIsSideKick == false && mIsUpper == false && mIsGuard == false
					&& mPlayerAttackState[17] == false)
				{
					if (mCanAttacked4 == true)
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
					if (mIsDowned || mIsGetUp || mIsWalk || mIsRun)
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

	void HarleyScript::OnCollisionExit(Collider2D* other)
	{

	}

#pragma endregion

#pragma region 이벤트 함수
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// 이벤트
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void HarleyScript::CombatComplete()
	{
		mIsArm = false;
		mIsKick = false;
		mIsSideKick = false;
		mIsUpper = false;


		if (mPlayerPos.x < mPos.x)
			ChangeState(eLukeState::L_Idle);
		else
			ChangeState(eLukeState::R_Idle);

		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(0, 3);
		mCombatInterval = (float)(dist(mt) + 1.0f);
	}

	void HarleyScript::GuardComplete()
	{
		// 막으려 하는 해당 스킬의 duration이 다르기 때문에 duration 까지 가드를 유지하기 위한 부분 
		ePlayerState playerState = PlayScene::GetPlayerState();
		if (playerState == ePlayerState::L_Idle || playerState == ePlayerState::R_Idle
			|| playerState == ePlayerState::L_Walk || playerState == ePlayerState::R_Walk
			|| playerState == ePlayerState::L_Jump || playerState == ePlayerState::R_Jump
			|| playerState == ePlayerState::L_Run || playerState == ePlayerState::R_Run)
		{
			if (mPlayerPos.x < mPos.x)
				ChangeState(eLukeState::L_Idle);
			else
				ChangeState(eLukeState::R_Idle);
		}
		else
		{
			if (mPlayerPos.x < mPos.x)
				ChangeState(eLukeState::L_Guard);
			else
				ChangeState(eLukeState::R_Guard);
		}
	}

	void HarleyScript::Attacked1Complete()
	{
		mIsAttacked1 = false;
		mIsAttacked2 = false;
		//mIsAttacked3 = false;
		mIsAttacked4 = false;

		//mIsCollidingFirst = 0;

		if (mPlayerPos.x < mPos.x)
			ChangeState(eLukeState::L_Idle);
		else
			ChangeState(eLukeState::R_Idle);
	}

	void HarleyScript::Attacked3Complete()
	{
		mIsAttacked3 = false;
		mIsDowned = true;

		mCanAttacked4 = true;

		if (mHp <= 0.0f)
		{
			SetEffectFlickering(0.05f, mDeadTime);
		}

		if (mPlayerPos.x < mPos.x)
		{
			ChangeState(eLukeState::L_Downed);
			mDirection = eDirection::L;
		}
		else
		{
			ChangeState(eLukeState::R_Downed);
			mDirection = eDirection::R;
		}
	}

	void HarleyScript::Attacked4Complete()
	{
		mIsAttacked4 = false;
		mIsDowned = true;

		mCanAttacked4 = false;

		if (mHp <= 0.0f)
		{
			SetEffectFlickering(0.05f, mDeadTime);
			mIsDead = true;
		}

		if (mDirection == eDirection::L)
			ChangeState(eLukeState::L_Downed);
		else
			ChangeState(eLukeState::R_Downed);
	}

	void HarleyScript::DownedComplete()
	{
		if (mHp <= 0.0f)
		{
			mIsDead = true;
			return;
		}
		else
		{
			mIsDowned = false;
			mIsGetUp = true;

			if (mDirection == eDirection::L)
				ChangeState(eLukeState::L_GetUp);
			else
				ChangeState(eLukeState::R_GetUp);
		}
	}

	void HarleyScript::GetUpComplete()
	{
		mIsGetUp = false;

		if (mDirection == eDirection::L)
			ChangeState(eLukeState::L_Idle);
		else
			ChangeState(eLukeState::R_Idle);
	}
	void HarleyScript::AttackedStart()
	{
		if (mIsDowned == true)
		{
			AudioSource* as = mPunch01Sound->GetComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"punch01", L"..\\Resources\\Sound\\BATTLE\\punch01.mp3"));
			as->Play();
		}
		else if (mPlayerAttackState[0] || mPlayerAttackState[1] || mPlayerAttackState[2] || mPlayerAttackState[4] || mPlayerAttackState[5])
		{
			AudioSource* as = mPunch01Sound->GetComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"punch01", L"..\\Resources\\Sound\\BATTLE\\punch01.mp3"));
			as->Play();
		}

		else if (mPlayerAttackState[3] || mPlayerAttackState[6] || mPlayerAttackState[8] || mPlayerAttackState[9] || mPlayerAttackState[12] || mPlayerAttackState[13])
		{
			AudioSource* as = mPunch01Sound->GetComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"punch01", L"..\\Resources\\Sound\\BATTLE\\punch01.mp3"));
			as->Play();
		}

		else if (mPlayerAttackState[10] || mPlayerAttackState[11] || mPlayerAttackState[14] || mPlayerAttackState[15] || mPlayerAttackState[16] || mPlayerAttackState[17])
		{
			AudioSource* as = mPunch02Sound->GetComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"punch02", L"..\\Resources\\Sound\\BATTLE\\punch02.mp3"));
			as->Play();
		}

	}
	void HarleyScript::AttackStart()
	{
		{
			AudioSource* as = mSwing01Sound->GetComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"swing01", L"..\\Resources\\Sound\\BATTLE\\swing01.mp3"));
			as->Play();
		}
	}
#pragma endregion

#pragma region 애니메이션 함수
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
													// 상태 애니메이션 함수
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void HarleyScript::L_idle()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Idle", true);
	}
	void HarleyScript::R_idle()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Idle", true);
	}
	//void LukeScript::L_angry()
	//{
	//	Animator* at = this->GetOwner()->GetComponent<Animator>();
	//	at->PlayAnimation(L"L_Angry", true);
	//}
	//void LukeScript::R_angry()
	//{
	//	Animator* at = this->GetOwner()->GetComponent<Animator>();
	//	at->PlayAnimation(L"R_Angry", true);
	//}
	void HarleyScript::L_walk()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Walk", true);
	}
	void HarleyScript::R_walk()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Walk", true);
	}
	void HarleyScript::L_run()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Run", true);
	}
	void HarleyScript::R_run()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Run", true);
	}
	void HarleyScript::L_armattack()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_ArmAttack", true);
	}
	void HarleyScript::R_armattack()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_ArmAttack", true);
	}
	void HarleyScript::L_kickattack()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_KickAttack", true);
	}
	void HarleyScript::R_kickattack()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_KickAttack", true);
	}
	void HarleyScript::L_sidekickattack()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_SideKickAttack", true);
	}
	void HarleyScript::R_sidekickattack()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_SideKickAttack", true);
	}
	void HarleyScript::L_upperattack()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_UpperAttack", true);
	}
	void HarleyScript::R_upperattack()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_UpperAttack", true);
	}
	void HarleyScript::L_guard()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Guard", true);
	}
	void HarleyScript::R_guard()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Guard", true);
	}
	void HarleyScript::L_attacked1()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Attacked1", true);
	}
	void HarleyScript::R_attacked1()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Attacked1", true);
	}
	void HarleyScript::L_attacked2()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Attacked2", true);
	}
	void HarleyScript::R_attacked2()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Attacked2", true);
	}
	void HarleyScript::L_attacked3()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Attacked3", true);
	}
	void HarleyScript::R_attacked3()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Attacked3", true);
	}
	void HarleyScript::L_attacked4()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Attacked4", true);
	}
	void HarleyScript::R_attacked4()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Attacked4", true);
	}
	void HarleyScript::L_getup()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_GetUp", true);
	}
	void HarleyScript::R_getup()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_GetUp", true);
	}
	void HarleyScript::L_downed()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Downed", true);
	}
	void HarleyScript::R_downed()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Downed", true);
	}
	void HarleyScript::L_dead()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Dead", true);
	}
	void HarleyScript::R_dead()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Dead", true);
	}
	//void LukeScript::L_flying()
	//{
	//	Animator* at = this->GetOwner()->GetComponent<Animator>();
	//	at->PlayAnimation(L"L_Flying", true);
	//}
	//void LukeScript::R_flying()
	//{
	//	Animator* at = this->GetOwner()->GetComponent<Animator>();
	//	at->PlayAnimation(L"R_Flying", true);
	//}
	//void LukeScript::L_raiding()
	//{
	//	Animator* at = this->GetOwner()->GetComponent<Animator>();
	//	at->PlayAnimation(L"L_Raiding", true);
	//}
	//void LukeScript::R_raiding()
	//{
	//	Animator* at = this->GetOwner()->GetComponent<Animator>();
	//	at->PlayAnimation(L"R_Raiding", true);
	//}

#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
													// 동작 내부 함수
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void HarleyScript::Combat()
	{
		mIsCombat = true;

		mCombatTimer -= Time::DeltaTime();

		if (mCombatTimer <= 0.0f)
		{
			// 공격 or 방어 or 대기 중 하나를 랜덤으로 실행
			const int wait = 3;// wait가 높을 수록 공격 및 방어가 아닌 대기할 확률이 높아짐

			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> dist(0, (int)eLukeCombatState::End + wait);
			int randStateNum = dist(mt);

			switch (static_cast<eLukeCombatState>(randStateNum))
			{
			case eLukeCombatState::ArmAttack:
				mIsArm = true;

				if (mPlayerPos.x < mPos.x)
					ChangeState(eLukeState::L_ArmAttack);
				else
					ChangeState(eLukeState::R_ArmAttack);
				break;

			case eLukeCombatState::KickAttack:
				mIsKick = true;

				if (mPlayerPos.x < mPos.x)
					ChangeState(eLukeState::L_KickAttack);
				else
					ChangeState(eLukeState::R_KickAttack);
				break;

			case eLukeCombatState::SideKickAttack:
				mIsSideKick = true;

				if (mPlayerPos.x < mPos.x)
					ChangeState(eLukeState::L_SideKickAttack);
				else
					ChangeState(eLukeState::R_SideKickAttack);
				break;

			case eLukeCombatState::UpperAttack:
				mIsUpper = true;

				if (mPlayerPos.x < mPos.x)
					ChangeState(eLukeState::L_UpperAttack);
				else
					ChangeState(eLukeState::R_UpperAttack);
				break;

			case eLukeCombatState::Guard:
				mIsGuard = true;

				if (mPlayerPos.x < mPos.x)
					ChangeState(eLukeState::L_Guard);
				else
					ChangeState(eLukeState::R_Guard);
				break;

			default:
				break;
			}

			mCombatTimer = mCombatInterval;
		}
	}

	void HarleyScript::SetAttackedState()
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
				if (mIsAttacked3 == false)
				{
					ChangeState(eLukeState::R_Attacked3);
					mIsAttacked3 = true;
				}
			}
			else// 플레이어 - 적
			{
				if (mIsAttacked3 == false)
				{
					ChangeState(eLukeState::L_Attacked3);
					mIsAttacked3 = true;
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
						if (mIsAttacked1 == false)
						{
							ChangeState(eLukeState::R_Attacked1);
							mIsAttacked1 = true;
						}
					}
					else// 플레이어 - 적
					{
						if (mIsAttacked1 == false)
						{
							ChangeState(eLukeState::L_Attacked1);
							mIsAttacked1 = true;
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
						if (mIsAttacked2 == false)
						{
							ChangeState(eLukeState::R_Attacked2);
							mIsAttacked2 = true;
						}
					}
					else// 플레이어 - 적
					{
						if (mIsAttacked2 == false)
						{
							ChangeState(eLukeState::L_Attacked2);
							mIsAttacked2 = true;
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
						if (mIsAttacked3 == false)
						{
							ChangeState(eLukeState::R_Attacked3);
							mIsAttacked3 = true;
						}
					}
					else// 플레이어 - 적
					{
						if (mIsAttacked3 == false)
						{
							ChangeState(eLukeState::L_Attacked3);
							mIsAttacked3 = true;
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
					if (mIsAttacked4 == false)
					{
						ChangeState(eLukeState::R_Attacked4);
						mIsAttacked4 = true;
					}
				}
				else// 플레이어 - 적
				{
					if (mIsAttacked4 == false)
					{
						ChangeState(eLukeState::L_Attacked4);
						mIsAttacked4 = true;
					}
				}
			}
		}
	}

	void HarleyScript::SetEffectFlickering(float tick, float duration)
	{
		GetOwner()->mIsEffectFlickering = true;
		mOnFlickering = true;
		mFlickeringCurTime = 0.0f;
		mFlickeringMaxTime = duration;
		mFlickeringTickTime = tick;
	}

	void HarleyScript::SetEffectFlashing(float tick, float duration, Vector4 color)
	{
		GetOwner()->mIsEffectFlashing = true;
		GetOwner()->mEffectColor = color;

		mOnFlashing = true;
		mFlashingCurTime = 0.0f;
		mFlashingMaxTime = duration;
		mFlashingTickTime = tick;
	}
}
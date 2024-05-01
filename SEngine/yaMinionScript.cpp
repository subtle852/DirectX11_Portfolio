#include "yaMinionScript.h"
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
#include "yaBoss01Script.h"
#include "yaRigidbody.h"
#include "yaObject.h"
#include "yaMeshRenderer.h"
#include "..\\Editor_Window\\yaDebugLog.h"

namespace ya
{
	MinionScript::MinionScript()
	{
		mAttackState.resize(10, false);
		mPlayerAttackState.resize(20, false);
	}
	MinionScript::~MinionScript()
	{
	}
	void MinionScript::Initialize()
	{
#pragma region 애니메이션
		// 애니메이션
		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"MINION_APPEAR", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\MINION\\MINION_APPEAR.png");
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->Create(L"R_APPEAR", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1440.0f / 10.0f, 144.0f), 10);//, Vector2::Zero, 0.05f);
		at->Create(L"L_APPEAR", atlas, enums::eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1440.0f / 10.0f, 144.0f), 10);

		atlas
			= Resources::Load<Texture>(L"MINION_DISAPPEAR", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\MINION\\MINION_DISAPPEAR.png");
		at->Create(L"R_DISAPPEAR", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(2304.0f / 16.0f, 144.0f), 16);
		at->Create(L"L_DISAPPEAR", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(2304.0f / 16.0f, 144.0f), 16);

		atlas
			= Resources::Load<Texture>(L"MINION_IDLE", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\MINION\\MINION_IDLE.png");
		at->Create(L"R_IDLE", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(720.0f / 5.0f, 144.0f), 5);
		at->Create(L"L_IDLE", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(720.0f / 5.0f, 144.0f), 5);

		atlas
			= Resources::Load<Texture>(L"MINION_ATTACK_APPEAR", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\MINION\\MINION_ATTACK_APPEAR.png");
		at->Create(L"R_ATTACK_APPEAR", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1008.0f / 7.0f, 144.0f), 7);
		at->Create(L"L_ATTACK_APPEAR", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1008.0f / 7.0f, 144.0f), 7);

		atlas
			= Resources::Load<Texture>(L"MINION_ATTACK", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\MINION\\MINION_ATTACK.png");
		at->Create(L"R_ATTACK", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1296.0f / 9.0f, 144.0f), 9);
		at->Create(L"L_ATTACK", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1296.0f / 9.0f, 144.0f), 9);

		atlas
			= Resources::Load<Texture>(L"MINION_ATTACK_DISAPPEAR", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\MINION\\MINION_ATTACK_DISAPPEAR.png");
		at->Create(L"R_ATTACK_DISAPPEAR", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1008.0f / 7.0f, 144.0f), 7);
		at->Create(L"L_ATTACK_DISAPPEAR", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1008.0f / 7.0f, 144.0f), 7);

		atlas
			= Resources::Load<Texture>(L"MINION_ATTACK_NO", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\MINION\\MINION_ATTACK_NO.png");
		at->Create(L"R_ATTACK_NO", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1008.0f / 7.0f, 144.0f), 7);
		at->Create(L"L_ATTACK_NO", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1008.0f / 7.0f, 144.0f), 7);

		atlas
			= Resources::Load<Texture>(L"MINION_DAMAGE", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\MINION\\MINION_DAMAGE.png");
		at->Create(L"R_DAMAGE", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(720.0f / 5.0f, 144.0f), 5);
		at->Create(L"L_DAMAGE", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(720.0f / 5.0f, 144.0f), 5);
#pragma endregion

#pragma region 이벤트
		// 이벤트
		at = GetOwner()->GetComponent<Animator>();

		at->CompleteEvent(L"L_APPEAR") = std::bind(&MinionScript::AppearComplete, this);
		at->CompleteEvent(L"R_APPEAR") = std::bind(&MinionScript::AppearComplete, this);

		at->CompleteEvent(L"L_DISAPPEAR") = std::bind(&MinionScript::DisAppearComplete, this);
		at->CompleteEvent(L"R_DISAPPEAR") = std::bind(&MinionScript::DisAppearComplete, this);

		at->CompleteEvent(L"L_DAMAGE") = std::bind(&MinionScript::DamageComplete, this);
		at->CompleteEvent(L"R_DAMAGE") = std::bind(&MinionScript::DamageComplete, this);

		at->CompleteEvent(L"L_ATTACK_APPEAR") = std::bind(&MinionScript::AttackAppearComplete, this);
		at->CompleteEvent(L"R_ATTACK_APPEAR") = std::bind(&MinionScript::AttackAppearComplete, this);
		at->CompleteEvent(L"L_ATTACK") = std::bind(&MinionScript::AttackComplete, this);
		at->CompleteEvent(L"R_ATTACK") = std::bind(&MinionScript::AttackComplete, this);
		at->CompleteEvent(L"L_ATTACK_DISAPPEAR") = std::bind(&MinionScript::AttackDisAppearComplete, this);
		at->CompleteEvent(L"R_ATTACK_DISAPPEAR") = std::bind(&MinionScript::AttackDisAppearComplete, this);
#pragma endregion

#pragma region 콜라이더
		// 콜라이더
		mBodyCd = this->GetOwner()->AddComponent<Collider2D>();
		mBodyCd->SetSize(Vector2(0.2f, 0.2f));
		mBodyCd->SetIsBody(true);

		mSkillCd = this->GetOwner()->AddComponent<Collider2D>();
		mSkillCd->SetSize(Vector2(0.1f, 0.1f));
		mSkillCd->SetCenter(Vector2(0.0f, 0.0f));
		//mSkillCd->SetActivation(eColliderActivation::InActive);
#pragma endregion

#pragma region 총알
		// 총알
		{
			mBullet01 = object::Instantiate<GameObject>(Vector3(2.0f, 1.0f, 40.f)
				, Vector3::One * 3
				, eLayerType::Enemy);
			mBullet01->SetName(L"Bullet01");

			MeshRenderer* mrb = mBullet01->AddComponent<MeshRenderer>();
			mrb->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mrb->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			Animator* atb = mBullet01->AddComponent<Animator>();
			atb = mBullet01->GetComponent<Animator>();
			std::shared_ptr<Texture> atlasb
				= Resources::Load<Texture>(L"BASIC_BULLET01_IDLE", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\MINION\\MINION_FIREBALL.png");
			atb->Create(L"R_BULLET01_IDLE", atlasb, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1152.0f / 8.0f, 144.0f), 8);
			atb->Create(L"L_BULLET01_IDLE", atlasb, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1152.0f / 8.0f, 144.0f), 8);
			atb->PlayAnimation(L"L_BULLET01_IDLE", true);

			mBullet01->SetState(GameObject::eState::Paused);
		}
		{
			mBullet02 = object::Instantiate<GameObject>(Vector3(-2.0f, 1.0f, 40.f)
				, Vector3::One * 3
				, eLayerType::Enemy);
			mBullet02->SetName(L"Bullet02");

			MeshRenderer* mrb = mBullet02->AddComponent<MeshRenderer>();
			mrb->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mrb->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			Animator* atb = mBullet02->AddComponent<Animator>();
			atb = mBullet02->GetComponent<Animator>();
			std::shared_ptr<Texture> atlasb
				= Resources::Load<Texture>(L"BASIC_BULLET02_IDLE", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\MINION\\MINION_FIREBALL.png");
			atb->Create(L"R_BULLET02_IDLE", atlasb, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1152.0f / 8.0f, 144.0f), 8);
			atb->Create(L"L_BULLET02_IDLE", atlasb, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1152.0f / 8.0f, 144.0f), 8);
			atb->PlayAnimation(L"R_BULLET02_IDLE", true);

			mBullet02->SetState(GameObject::eState::Paused);
		}
#pragma endregion

#pragma region 그림자
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
				* 0.8f);

			mShadow->SetState(ya::GameObject::eState::Paused);
		}
#pragma endregion

	}
	void MinionScript::Update()
	{
#pragma region 디버그
		//std::wstring str = std::to_wstring(mLevelPhase3);
		//ya::DebugLog::PrintDebugLog(L"mLevelPhase3: " + str);

#pragma endregion

#pragma region FSM
		// FSM
		if (mPrevState != mCurState)
		{
			switch (mCurState)
			{
			case eMinionState::L_Appear:
				L_appear();
				break;
			case eMinionState::R_Appear:
				R_appear();
				break;

			case eMinionState::L_DisAppear:
				L_disAppear();
				break;
			case eMinionState::R_DisAppear:
				R_disAppear();
				break;

			case eMinionState::L_Idle:
				L_idle();
				break;
			case eMinionState::R_Idle:
				R_idle();
				break;

			case eMinionState::L_AttackAppear:
				L_attackAppear();
				break;
			case eMinionState::R_AttackAppear:
				R_attackAppear();
				break;
			case eMinionState::L_Attack:
				L_attack();
				break;
			case eMinionState::R_Attack:
				R_attack();
				break;
			case eMinionState::L_AttackDisAppear:
				L_attackDisAppear();
				break;
			case eMinionState::R_AttackDisAppear:
				R_attackDisAppear();
				break;
			case eMinionState::L_AttackNo:
				L_attackNo();
				break;
			case eMinionState::R_AttackNo:
				R_attackNo();
				break;

			case eMinionState::L_Damage:
				L_damage();
				break;
			case eMinionState::R_Damage:
				R_damage();
				break;

			default:
				break;
			}
		}

		mPrevState = mCurState;

#pragma endregion

#pragma 속성 업데이트
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
			mIsPlayerDead = PlayScene::IsPlayerDead();
			mPlayerPos = PlayScene::GetPlayerPosition();
			mPlayerDir = PlayScene::GetPlayerDirection();
		}
#pragma endregion

#pragma region 그림자
		// 그림자
		if(mShadow->GetState() == ya::GameObject::eState::Active)
		{
			Transform* myTr = GetOwner()->GetComponent<Transform>();
			Vector3 myPos = myTr->GetPosition();
			myPos.y -= 0.7f;

			Transform* shadowTr = mShadow->GetComponent<Transform>();
			shadowTr->SetPosition(myPos);
		}
#pragma endregion

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// 페이즈 0 (대기)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (mPhase == 0)
		{

		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// 페이즈 1 (등장)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (mPhase == 1)
		{
			mShadow->SetState(ya::GameObject::eState::Active);

			// 등장
			ChangeState(eMinionState::L_Appear);

			//Transform* tr = this->GetOwner()->GetComponent<Transform>();
			//tr->SetPosition(Vector3(3.2f, 0.0f, tr->GetPosition().z));

		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// 페이즈 2 (빙빙)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (mPhase == 2)
		{
			// Idle 애니메
			if (mIsDamage == false)
			{
				ChangeState(eMinionState::L_Idle);
			}
			if (mIsCollidingFirst == 2)// 충돌 시, Damage 애니메이션을 단 한번만 호출되도록 하기위한 부분
			{
				mIsDamage = false;
				ChangeState(eMinionState::L_Idle);
			}

			// 충돌 시, Damage 애니메 (OnColiisionStay 내부에서 호출)

			// 충돌 중이지 않는 경우 충돌관련 초기화
			//if (mBodyCd->GetState() == enums::eColliderState::NotColliding)//
			if(mCurState == eMinionState::L_Idle || mCurState == eMinionState::R_Idle)
			{
				mIsDamage = false;
				mIsCollidingFirst = 0;
			}

			if (mHp <= 0)
			{
				mShadow->SetState(ya::GameObject::eState::Paused);

				ChangeState(eMinionState::L_DisAppear);
			}

			/*std::wstring str = std::to_wstring(mHp);
			ya::DebugLog::PrintDebugLog(L"mHp: " + str);*/

			//std::wstring str = std::to_wstring(mIsCollidingFirst);
			//ya::DebugLog::PrintDebugLog(L"mIsCollidingFirst: " + str);

			//std::wstring str = std::to_wstring(currentRadian);
			//std::wstring str1 = std::to_wstring(currentDegree);
			//ya::DebugLog::PrintDebugLog(L"Radian: " + str + L" Degree: " + str1);

			// 회전
			// currentRadian 지정을 통해 시작 위치 설정 가능
			Transform* tr = this->GetOwner()->GetComponent<Transform>();

			float centerX = 2.2f;
			float centerY = 0.0f;

			float radiusX = 1.0f;
			float radiusY = 0.5f;

			currentRadian += rotationSpeed * Time::DeltaTime();

			float newX = centerX + radiusX * cos(currentRadian);
			float newY = centerY + radiusY * sin(currentRadian);
			tr->SetPosition(Vector3(newX, newY, tr->GetPosition().z));

			// 라디안 최대치
			if (currentRadian >= 2 * XM_PI)
			{
				currentRadian -= 2 * XM_PI;
			}
			else if (currentRadian < 0)
			{
				currentRadian += 2 * XM_PI;
			}

			// 라디안 각도변환 (라디안 = 각도 * pi / 180)
			currentDegree = currentRadian * 180 / XM_PI;
			if (0.0f < currentDegree && currentDegree <= 180)
			{
				tr->SetPosition(Vector3(newX, newY, 41));
			}
			else
			{
				tr->SetPosition(Vector3(newX, newY, 39));
			}

		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 페이즈 3 (총알 던지기)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (mPhase == 3)
		{
			if (mLevelPhase3 == 0)
			{
				mPhase3AppearTime = 2.0f;

				mShadow->SetState(ya::GameObject::eState::Active);

				Transform* tr = this->GetOwner()->GetComponent<Transform>();
				if (tr->GetPosition().x > 0.0f)
				{
					ChangeState(eMinionState::L_AttackAppear);
				}
				else
				{
					ChangeState(eMinionState::R_AttackAppear);
				}
			}
			else if (mLevelPhase3 == 1)
			{
				Transform* tr = this->GetOwner()->GetComponent<Transform>();
				if (tr->GetPosition().x > 0.0f)
				{
					ChangeState(eMinionState::L_Attack);

					// Collider 이동
					{
						// 목표 지점
						const Vector2 targetCenter(-1.0f, -1.5f);

						Vector2 currentCenter = mSkillCd->GetCenter();
						Vector2 direction = targetCenter - currentCenter;
						float distance = direction.Length();

						// 이동 속도
						float moveSpeed = 2.5f;

						// 목표 지점에 도달 처리
						if (distance <= moveSpeed * Time::DeltaTime())
						{
							mSkillCd->SetCenter(targetCenter);
						}
						else
						{
							direction.Normalize();
							Vector2 movement = direction * moveSpeed * Time::DeltaTime();

							Vector2 newCenter = currentCenter + movement;
							mSkillCd->SetCenter(newCenter);
						}
					}

					if (mBullet01->GetState() == GameObject::eState::Paused)
					{
						mBullet01->SetState(GameObject::eState::Active);
						Animator* at = mBullet01->GetComponent<Animator>();
						at->PlayAnimation(L"L_BULLET01_IDLE", false);
					}

					// Bullet01 이동
					{
						// 목표 지점
						const Vector2 targetPosition(1.0f, -1.1f);

						Transform* bulletTransform = mBullet01->GetComponent<Transform>();
						Vector3 currentPosition = bulletTransform->GetPosition();
						Vector2 direction = targetPosition - currentPosition;
						float distance = direction.Length();

						// 이동 속도 설정
						float moveSpeed = 3.0f;

						// 목표 지점에 도달 처리
						if (distance <= moveSpeed * Time::DeltaTime())
						{
							bulletTransform->SetPosition(Vector3(targetPosition.x, targetPosition.y, currentPosition.z));
						}
						else
						{
							direction.Normalize();
							Vector2 movement = direction * moveSpeed * Time::DeltaTime();

							Vector2 newPosition = currentPosition + movement;
							bulletTransform->SetPosition(Vector3(newPosition.x, newPosition.y, currentPosition.z));
						}
					}
					
				}
				else
				{
					ChangeState(eMinionState::R_Attack);

					// Collider 이동
					{
						// 목표 지점
						const Vector2 targetCenter(1.0f, -1.5f);

						Vector2 currentCenter = mSkillCd->GetCenter();
						Vector2 direction = targetCenter - currentCenter;
						float distance = direction.Length();

						// 이동 속도
						float moveSpeed = 2.5f;

						// 목표 지점에 도달 처리
						if (distance <= moveSpeed * Time::DeltaTime())
						{
							mSkillCd->SetCenter(targetCenter);
						}
						else
						{
							direction.Normalize();
							Vector2 movement = direction * moveSpeed * Time::DeltaTime();

							Vector2 newCenter = currentCenter + movement;
							mSkillCd->SetCenter(newCenter);
						}
					}

					if (mBullet02->GetState() == GameObject::eState::Paused)
					{
						mBullet02->SetState(GameObject::eState::Active);
						Animator* at = mBullet02->GetComponent<Animator>();
						at->PlayAnimation(L"R_BULLET02_IDLE", false);
					}

					// Bullet02 이동
					{
						// 목표 지점
						const Vector2 targetPosition(-1.0f, -1.1f);

						Transform* bulletTransform = mBullet02->GetComponent<Transform>();
						Vector3 currentPosition = bulletTransform->GetPosition();
						Vector2 direction = targetPosition - currentPosition;
						float distance = direction.Length();

						// 이동 속도 설정
						float moveSpeed = 3.0f;

						// 목표 지점에 도달 처리
						if (distance <= moveSpeed * Time::DeltaTime())
						{
							bulletTransform->SetPosition(Vector3(targetPosition.x, targetPosition.y, currentPosition.z));
						}
						else
						{
							direction.Normalize();
							Vector2 movement = direction * moveSpeed * Time::DeltaTime();

							Vector2 newPosition = currentPosition + movement;
							bulletTransform->SetPosition(Vector3(newPosition.x, newPosition.y, currentPosition.z));
						}
					}
				}
			}
			else if (mLevelPhase3 == 2)
			{
				// 콜라이더 Center 초기화 및 Bullet01, Bullet02 위치 초기화 
				mSkillCd->SetCenter(Vector2(0.0f, 0.0f));

				Transform* bullet01Transform = mBullet01->GetComponent<Transform>();
				bullet01Transform->SetPosition(Vector3(2.0f, 1.0f, bullet01Transform->GetPosition().z));

				Transform* bullet02Transform = mBullet02->GetComponent<Transform>();
				bullet02Transform->SetPosition(Vector3(-2.0f, 1.0f, bullet02Transform->GetPosition().z));

				if (mBullet01->GetState() == GameObject::eState::Active)
				{
					mBullet01->SetState(GameObject::eState::Paused);
				}
				if (mBullet02->GetState() == GameObject::eState::Active)
				{
					mBullet02->SetState(GameObject::eState::Paused);
				}

				Transform* tr = this->GetOwner()->GetComponent<Transform>();
				if (tr->GetPosition().x > 0.0f)
				{
					ChangeState(eMinionState::L_AttackDisAppear);
				}
				else
				{
					ChangeState(eMinionState::R_AttackDisAppear);
				}
			}
			else if (mLevelPhase3 == 3)
			{
				mShadow->SetState(ya::GameObject::eState::Paused);

				ChangeState(eMinionState::L_AttackNo);

				mPhase3AppearTime -= Time::DeltaTime();
				if (mPhase3AppearTime <= 0.0f)
				{
					mLevelPhase3 = 0;
				}
			}
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 페이즈 4 (종료)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (mPhase == 4)
		{
			// 보스 체력 0이하 되면 (BossScript에서)
			// 부하 두마리 DisAppear (BossScript에서)
			// 보스 DisAppear (부하 소멸 호출 후, BossScript에서)
			// 승리 마크 및 이펙트 (BossScene or BossScript에서)

			Transform* tr = this->GetOwner()->GetComponent<Transform>();
			if (tr->GetPosition().x > 0.0f)
			{
				ChangeState(eMinionState::L_DisAppear);
			}
			else
			{
				ChangeState(eMinionState::R_DisAppear);
			}

		}
		else
		{

		}
	}

#pragma region OnCollision
	void MinionScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void MinionScript::OnCollisionStay(Collider2D* other)
	{ 
		// 페이즈 2 (빙빙도는 경우 DAMAGE)
		if (mPhase == 2)
		{
			if (dynamic_cast<PlayerScript*>(other->GetOwner()->GetComponent<PlayerScript>()))
			{
				if (other->GetOwner()->GetComponent<RamonaScript>()->IsDead() == true)
					return;

				//if (this->GetOwner()->GetComponent<Collider2D>()->IsBody() == true && other->IsBody() == true)
				//	return;

				//if (mCurState == eBoss01State::L_Guard || mCurState == eBoss01State::R_Guard
				//	|| mIsAttackPunch || mIsAttackJumpPunchIng || mIsAttackKick || mIsAttackFire || mIsAttackDownKick)
				//	return;

				if (this->GetOwner()->GetComponent<Collider2D>()->IsBody() == true && other->IsBody() == true)
				{

				}

				else if (this->GetOwner()->GetComponent<Collider2D>()->IsBody() == true && other->IsBody() == false)
				{
					if (mBodyCd->GetState() == eColliderState::IsColliding)
					{
						if (mIsCollidingFirst == 0 && mIsDamage == false)
						{
							other->GetOwner()->GetComponent<RamonaScript>()->AddSp(10);
							mHp -= mAttackedDamage;

							mIsDamage = true;
							ChangeState(eMinionState::L_Damage);

							mIsCollidingFirst = 1;
						}
					}
				}
			}
		}
	}
	void MinionScript::OnCollisionExit(Collider2D* other)
	{
	}
#pragma endregion

#pragma region 이벤트 함수
	void MinionScript::AppearComplete()
	{
		mPhase = 2;
	}
	void MinionScript::DisAppearComplete()
	{
		if (mPhase == 4)// 완전히 죽는 상황
		{
			mShadow->SetState(GameObject::eState::Paused);
			mIsDead = true;
			this->GetOwner()->SetState(GameObject::eState::Paused);
		}
		else// 빙빙돌고 사라지는 상황
		{
			mShadow->SetState(GameObject::eState::Paused);
			this->GetOwner()->SetState(GameObject::eState::Paused);
		}
	}
	void MinionScript::DamageComplete()
	{
		mIsCollidingFirst = 2;
	}
	void MinionScript::AttackAppearComplete()
	{
		mLevelPhase3 = 1;
	}
	void MinionScript::AttackComplete()
	{
		mLevelPhase3 = 2;
	}
	void MinionScript::AttackDisAppearComplete()
	{
		mLevelPhase3 = 3;
	}
#pragma endregion

#pragma region 애니메이션 함수
	void MinionScript::L_appear()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_APPEAR", true);
	}
	void MinionScript::R_appear()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_APPEAR", true);
	}
	void MinionScript::L_disAppear()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_DISAPPEAR", true);
	}
	void MinionScript::R_disAppear()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_DISAPPEAR", true);
	}
	void MinionScript::L_idle()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_IDLE", true);
	}
	void MinionScript::R_idle()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_IDLE", true);
	}
	void MinionScript::L_attackAppear()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_ATTACK_APPEAR", true);
	}
	void MinionScript::R_attackAppear()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_ATTACK_APPEAR", true);
	}
	void MinionScript::L_attack()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_ATTACK", true);
	}
	void MinionScript::R_attack()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_ATTACK", true);
	}
	void MinionScript::L_attackDisAppear()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_ATTACK_DISAPPEAR", true);
	}
	void MinionScript::R_attackDisAppear()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_ATTACK_DISAPPEAR", true);
	}
	void MinionScript::L_attackNo()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_ATTACK_NO", true);
	}
	void MinionScript::R_attackNo()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_ATTACK_NO", true);
	}
	void MinionScript::L_damage()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_DAMAGE", true);
	}
	void MinionScript::R_damage()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_DAMAGE", true);
	}
#pragma endregion

	void MinionScript::SetEffectFlickering(float tick, float duration)
	{
		GetOwner()->mIsEffectFlickering = true;
		mOnFlickering = true;
		mFlickeringCurTime = 0.0f;
		mFlickeringMaxTime = duration;
		mFlickeringTickTime = tick;
	}
	void MinionScript::SetEffectFlashing(float tick, float duration, Vector4 color)
	{
		GetOwner()->mIsEffectFlashing = true;
		GetOwner()->mEffectColor = color;

		mOnFlashing = true;
		mFlashingCurTime = 0.0f;
		mFlashingMaxTime = duration;
		mFlashingTickTime = tick;
	}
}
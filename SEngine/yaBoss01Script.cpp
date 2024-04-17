//#include "yaBoss01Script.h"
//#include "yaCameraScript.h"
//#include "yaTransform.h"
//#include "yaGameObject.h"
//#include "yaTime.h"
//#include "yaInput.h"
//#include "yaAnimator.h"
//#include "yaResources.h"
//#include "yaPlayScene.h"
//#include "yaCollider2D.h"
//#include "yaRamonaScript.h"
//
//namespace ya
//{
//	Boss01Script::Boss01Script()
//	{
//	}
//	Boss01Script::~Boss01Script()
//	{
//	}
//	void Boss01Script::Initialize()
//	{
//#pragma region 애니메이션
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//															// 애니메이션
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		std::shared_ptr<Texture> atlas
//			= Resources::Load<Texture>(L"Luke_Idle", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->Create(L"R_Idle", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);//, Vector2::Zero, 0.05f);
//		at->Create(L"L_Idle", atlas, enums::eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_Angry", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_ANGRY.png");
//		at->Create(L"R_Angry", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4);
//		at->Create(L"L_Angry", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_Walk", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_WALK.png");
//		at->Create(L"R_Walk", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1385.0f / 12.0f, 116.0f), 12);
//		at->Create(L"L_Walk", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1385.0f / 12.0f, 116.0f), 12);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_Run", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_RUN.png");
//		at->Create(L"R_Run", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
//		at->Create(L"L_Run", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
//
//		atlas
//			= Resources::Load<Texture>(L"ArmAttack", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_ARM.png");
//		at->Create(L"R_ArmAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
//		at->Create(L"L_ArmAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_KickAttack", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_KICK.png");
//		at->Create(L"R_KickAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(808.0f / 7.0f, 116.0f), 7);
//		at->Create(L"L_KickAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(808.0f / 7.0f, 116.0f), 7);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_SideKickAttack", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_SIDEKICK.png");
//		at->Create(L"R_SideKickAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(808.0f / 7.0f, 116.0f), 7);
//		at->Create(L"L_SideKickAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(808.0f / 7.0f, 116.0f), 7);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_UpperAttack", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_UPPER.png");
//		at->Create(L"R_UpperAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
//		at->Create(L"L_UpperAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_Guard", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_GUARD.png");
//		at->Create(L"R_Guard", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(693.0f / 6.0f, 116.0f), 6);
//		at->Create(L"L_Guard", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(693.0f / 6.0f, 116.0f), 6);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_Attacked1", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_ATTACKED1.png");
//		at->Create(L"R_Attacked1", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4, Vector2::Zero, 0.15f);
//		at->Create(L"L_Attacked1", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4, Vector2::Zero, 0.15f);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_Attacked2", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_ATTACKED2.png");
//		at->Create(L"R_Attacked2", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4, Vector2::Zero, 0.15f);
//		at->Create(L"L_Attacked2", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4, Vector2::Zero, 0.15f);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_Attacked3", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_ATTACKED3.png");
//		at->Create(L"R_Attacked3", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1616.0f / 14.0f, 116.0f), 14);
//		at->Create(L"L_Attacked3", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1616.0f / 14.0f, 116.0f), 14);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_Attacked4", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_ATTACKED4.png");
//		at->Create(L"R_Attacked4", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4);
//		at->Create(L"L_Attacked4", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_GetUp", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_GETUP.png");
//		at->Create(L"R_GetUp", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
//		at->Create(L"L_GetUp", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_Downed", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_DEAD.png");
//		at->Create(L"R_Downed", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4, Vector2::Zero, 1.0f);
//		at->Create(L"L_Downed", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4, Vector2::Zero, 1.0f);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_Dead", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_DEAD.png");
//		at->Create(L"R_Dead", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4, Vector2::Zero, 1.0f);
//		at->Create(L"L_Dead", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4, Vector2::Zero, 1.0f);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_Flying", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_FLYING.png");
//		at->Create(L"R_Flying", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4);
//		at->Create(L"L_Flying", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4);
//
//		atlas
//			= Resources::Load<Texture>(L"Luke_Raiding", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_RAIDING.png");
//		at->Create(L"R_Raiding", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4);
//		at->Create(L"L_Raiding", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4);
//
//#pragma endregion
//
//#pragma region 이벤트
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//															// 이벤트 
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		at = GetOwner()->GetComponent<Animator>();
//
//		//at->CompleteEvent(L"L_Attacked1") = std::bind(&LukeScript::Attacked1Complete, this);
//		//at->CompleteEvent(L"R_Attacked1") = std::bind(&LukeScript::Attacked1Complete, this);
//
//#pragma endregion
//
//#pragma region 콜라이더
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//															// 콜라이더
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		mBodyCd = this->GetOwner()->AddComponent<Collider2D>();
//		mBodyCd->SetSize(Vector2(0.15f, 0.15f));
//		mBodyCd->SetIsBody(true);
//
//		mSkillCd = this->GetOwner()->AddComponent<Collider2D>();
//		mSkillCd->SetSize(Vector2(0.2f, 0.3f));
//		mSkillCd->SetCenter(Vector2(0.3f, 0.0f));
//		mSkillCd->SetActivation(eColliderActivation::InActive);
//
//#pragma endregion
//
//#pragma region 초기화
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//															// 초기화 
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		// 랜덤 함수를 위한 함수 실행
//		rd();// 반환 값 무시된 상태
//
//#pragma endregion
//	}
//	void Boss01Script::Update()
//	{
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//															// FSM
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		if (mPrevState != mCurState)
//		{
//			switch (mCurState)
//			{
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			case Boss01Script::L_Idle:
//				L_idle();
//				break;
//			case Boss01Script::R_Idle:
//				R_idle();
//				break;
//
//			default:
//				break;
//			}
//		}
//
//		mPrevState = mCurState;
//
//		// 본인 위치 업데이트
//		Transform* tr = this->GetOwner()->GetComponent<Transform>();
//		Vector3 pos = tr->GetPosition();
//		mPos = pos;
//
//		// 플레이어 위치, 방향 업데이트
//		if (PlayScene::IsPlayerExist())
//		{
//			mPlayerPos = PlayScene::GetPlayerPosition();
//			mPlayerDir = PlayScene::GetPlayerDirection();
//		}
//
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//															// 콜라이더 업데이트
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		if (mDirection == eDirection::L)
//		{
//			mSkillCd->SetCenter(Vector2(-0.3f, 0.0f));
//		}
//		else
//		{
//			mSkillCd->SetCenter(Vector2(0.3f, 0.0f));
//		}
//
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//															// AI
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		// 공격을 당하고 있을 때는 아래의 상태 변화가 있으면 안됨
//		// 추후 공격을 당하는 변수들 합쳐서 함수로 대체 예정
//		if (mIsAttacked1 == false && mBodyCd->GetState() == eColliderState::NotColliding && mIsDowned == false)
//		{
//			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//															// 탐지거리 내 플레이어 O
//			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//			if (IsPlayerInDetectionRange())// 탐지거리 내 플레이어 O
//			{
//				if (mDetected == false)// 처음 감지했을 때만 들어오는 조건문
//				{
//					// 플레이어 쪽 방향으로 설정 해줘야 함
//					if (mPlayerPos.x < mPos.x)
//					{
//						mDetected = true;
//						mDirection = eDirection::L;
//						ChangeState(eLukeState::L_Idle);
//					}
//					else
//					{
//						mDetected = true;
//
//						mDirection = eDirection::R;
//						ChangeState(eLukeState::R_Idle);
//					}
//
//					// 달려갈지 대기할지 랜덤 설정
//					if (mRandWaitOrRun == -100)
//					{
//						std::mt19937 mt(rd());
//						std::uniform_int_distribution<int> dist(0, 1);
//						mRandWaitOrRun = dist(mt);
//					}
//				}
//
//				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													// 탐지거리 내 플레이어 O 전투거리 내 플레이어 O
//				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//				if (IsPlayerInCombatRange())
//				{
//					if (mIsAttacked1 == false && mIsAttacked2 == false && mIsAttacked3 == false && mIsAttacked4 == false && mIsDowned == false && mIsGetUp == false && mIsGuard == false)// Combat 조건
//					{
//						// 처음 감지했을 때만 들어오는 조건문
//						if (mIsCombat == false)
//						{
//							if (mPlayerPos.x < mPos.x)
//							{
//								ChangeState(eLukeState::L_Idle);
//							}
//							else
//							{
//								ChangeState(eLukeState::R_Idle);
//							}
//
//							// Combat 관련 변수 초기화 
//							mCombatTimer = 2.0f;
//						}
//
//						Combat();
//					}
//				}
//
//				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													// 탐지거리 내 플레이어 O 전투거리 내 플레이어 X
//				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//				else
//				{
//					mDetected = true;// 플레이어 쪽 방향으로 설정 해주기 위해 처음 Detect 되는 상태로 전환
//					mIsCombat = false;
//
//					//mCombatTimer = 0.0f;
//
//					// 달려오는 경우
//					if (mRandWaitOrRun == 0)
//					{
//						// 추후, 해당 조건문 CanRun or CanChase(Chase로 한다면, Run 변수들 네이밍 Chase로 바꿔줘야 함)로 묶을 예정
//						// Combat에서 공격 스킬이 나가는 도중에
//						// 플레이어가 전투거리에서 나갈 때,
//						// 해당 스킬은 마저 실행하고 달려가야 하기 때문에 아래와 같은 조건문이 필요
//
//						if (fabs(mPlayerPos.x - mPos.x) < 0.05f)
//						{
//							if (mDirection == eDirection::L)
//								ChangeState(eLukeState::L_Idle);
//							else
//								ChangeState(eLukeState::R_Idle);
//						}
//						else
//						{
//							if (mPlayerPos.x < mPos.x && (mCurState == eLukeState::L_Idle || mCurState == eLukeState::R_Idle || mCurState == eLukeState::L_Run || mCurState == eLukeState::R_Run))
//							{
//								mDirection = eDirection::L;
//								ChangeState(eLukeState::L_Run);
//
//								mDirectionInt = -1;
//								Transform* tr = this->GetOwner()->GetComponent<Transform>();
//								Vector3 pos = tr->GetPosition();
//								pos.x += mDirectionInt * mRunSpeed * Time::DeltaTime();
//								tr->SetPosition(pos);
//							}
//							else if (mPos.x < mPlayerPos.x && (mCurState == eLukeState::L_Idle || mCurState == eLukeState::R_Idle || mCurState == eLukeState::L_Run || mCurState == eLukeState::R_Run))
//							{
//								mDirection = eDirection::R;
//								ChangeState(eLukeState::R_Run);
//
//								mDirectionInt = +1;
//								Transform* tr = this->GetOwner()->GetComponent<Transform>();
//								Vector3 pos = tr->GetPosition();
//								pos.x += mDirectionInt * mRunSpeed * Time::DeltaTime();
//								tr->SetPosition(pos);
//							}
//						}
//
//					}
//
//					// 대기하는 경우
//					else// (mRandWaitOrRun == 1)
//					{
//						if (mPlayerPos.x < mPos.x && (mCurState == eLukeState::L_Idle || mCurState == eLukeState::R_Idle || mCurState == eLukeState::L_Run || mCurState == eLukeState::R_Run))
//						{
//							ChangeState(eLukeState::L_Idle);
//						}
//						else if (mPos.x < mPlayerPos.x && (mCurState == eLukeState::L_Idle || mCurState == eLukeState::R_Idle || mCurState == eLukeState::L_Run || mCurState == eLukeState::R_Run))
//						{
//							ChangeState(eLukeState::R_Idle);
//						}
//					}
//
//				}
//			}
//
//			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													// 탐지거리 내 플레이어 X && 전투거리 내 플레이어 X
//			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//			else
//			{
//				mDetected = false;
//				mRandWaitOrRun = -100;
//
//				// 이동 타이머 감소
//				mMoveTimer -= Time::DeltaTime();
//
//				if (mMoveTimer <= 0.0f)
//				{
//					// 랜덤하게 이동 방향 변경
//					if (rand() % 2 == 0)
//					{
//						mDirection = eDirection::L;
//						mDirectionInt = -1;
//					}
//					else
//					{
//						mDirection = eDirection::R;
//						mDirectionInt = +1;
//					} // -1 또는 1로 랜덤하게 설정
//
//					// 타이머 초기화
//					mMoveTimer = mMoveInterval;
//				}
//
//				// 랜덤 이동 로직
//				float moveDistance = GetRandomMoveDistance();
//				Transform* tr = this->GetOwner()->GetComponent<Transform>();
//				Vector3 pos = tr->GetPosition();
//				pos.x += mDirectionInt * moveDistance * Time::DeltaTime();
//				tr->SetPosition(pos);
//
//				if (mDirectionInt == -1)
//				{
//					mDirection = eDirection::L;
//					ChangeState(eLukeState::L_Walk);
//				}
//				else
//				{
//					mDirection = eDirection::R;
//					ChangeState(eLukeState::R_Walk);
//				}
//
//				// 화면 좌측 끝과 우측 끝을 벗어나지 않도록 처리
//				if (mPos.x < -2.8f)////////////////////////////////////////////////////////////////////////// 수정 예정 CameraPos로
//				{
//					//mPos.x = 0;
//					mDirectionInt = 1; // 우측으로 방향 전환
//					mDirection = eDirection::R;
//					ChangeState(eLukeState::R_Walk);
//				}
//				else if (mPos.x > 2.8f)
//				{
//					//mPos.x = screenWidth;
//					mDirectionInt = -1; // 좌측으로 방향 전환
//					mDirection = eDirection::L;
//					ChangeState(eLukeState::L_Walk);
//				}
//			}
//		}
//
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																// 충돌
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		if (mBodyCd->GetState() == eColliderState::IsColliding)
//		{
//			if (mIsCollidingFirst == 0
//				&& mIsAttacked1 == false && mIsAttacked2 == false && mIsAttacked3 == false && mIsAttacked4 == false && mIsDowned == false && mIsGetUp == false)// 처음 충돌
//				// + 충돌 조건(다운되어있는데 갑자기 공격을 받았다고 해서 Guard나 Idle로 바뀌지 않기 위한 조건)
//				// 추후 충돌 조건은 따로 정리할 예정
//			{
//				//// 플레이어 현재 스킬 저장
//				//mPlayerPreState = PlayScene::GetPlayerState();
//
//				// 방어 스킬 사용할지 안할지 랜덤으로 실행
//				std::mt19937 mt(rd());
//				std::uniform_int_distribution<int> dist(0, 1);
//				int randGuard = dist(mt);
//
//				if ((bool)randGuard == true)
//				{
//					if (mPlayerPos.x < mPos.x)
//					{
//						mDirection = eDirection::L;
//						ChangeState(eLukeState::L_Guard);
//
//						mIsCollidingFirst = 1;
//					}
//					else
//					{
//						mDirection = eDirection::R;
//						ChangeState(eLukeState::R_Guard);
//
//						mIsCollidingFirst = 1;
//					}
//				}
//				else
//				{
//					SetAttackedState();
//					mIsCollidingFirst = 1;
//				}
//			}
//
//			//// 콤보 공격을 하는 경우 충돌 처리를 처음으로 돌려놓는 부분 
//			//if (//mIsNormalAttackComboInit == false && 
//			//	(PlayScene::GetPlayerState() == ePlayerState::L_NormalAttack2 || PlayScene::GetPlayerState() == ePlayerState::R_NormalAttack2
//			//		|| PlayScene::GetPlayerState() == ePlayerState::R_NormalAttack3 || PlayScene::GetPlayerState() == ePlayerState::R_NormalAttack3))
//			//{
//			//	mIsCollidingFirst = 0;
//			//	mIsNormalAttackComboInit = true;
//			//}
//		}
//
//		// 충돌하지 않는 상태일 때
//		if (mBodyCd->GetState() == eColliderState::NotColliding)
//		{
//			mIsCollidingFirst = 0;
//			mPlayerPreState = ePlayerState::R_Idle;
//			mPlayerCurState = ePlayerState::R_Idle;
//			mIsNormalAttackComboInit = false;
//		}
//
//		if (mSkillCd->GetState() == eColliderState::NotColliding)
//		{
//			mIsCollidingFirst = 0;
//			mIsNormalAttackComboInit = false;
//		}
//
//		// mBodyCd 활성화 비활성화 조건
//		if (mCurState == eLukeState::L_Guard || mCurState == eLukeState::R_Guard
//			|| mIsArm || mIsKick || mIsSideKick || mIsUpper
//			|| mIsAttacked1 || mIsAttacked2 || mIsAttacked3 || mIsAttacked4)
//			// 가드가 붙은 스킬아냐 아니냐로 구분을 해서 적용을 할지 고민중
//			// 가드를 하고 있다가 바로 스킬을 쓴다면, 계속 무적이고 플레이어의 공격상태와 겹치게 되면 상황이 애매해짐 
//		{
//			mBodyCd->SetActivation(eColliderActivation::InActive);
//		}
//		else
//		{
//			mBodyCd->SetActivation(eColliderActivation::Active);
//		}
//
//		// 오류 임시 해결
//		if (Input::GetKey(eKeyCode::Q))
//		{
//			mBodyCd->SetState(eColliderState::NotColliding);
//		}
//
//		// mSkillCd 활성화 비활성화 조건
//		if (mIsArm || mIsKick || mIsSideKick || mIsUpper)
//		{
//			mSkillCd->SetActivation(eColliderActivation::Active);
//		}
//		else
//		{
//			mSkillCd->SetActivation(eColliderActivation::InActive);
//		}
//
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//														// 상태 bool 변수 동기화
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		// 가드 상태 변수 동기화
//		if (mCurState == eLukeState::L_Guard || mCurState == eLukeState::R_Guard)
//		{
//			mIsGuard = true;
//		}
//		else
//		{
//			mIsGuard = false;
//		}
//
//		// Attacked 상태 변수 동기화
//		if (mCurState == eLukeState::L_Attacked1 || mCurState == eLukeState::R_Attacked1)
//		{
//			mIsAttacked1 = true;
//		}
//		else
//		{
//			mIsAttacked1 = false;
//		}
//		if (mCurState == eLukeState::L_Attacked2 || mCurState == eLukeState::R_Attacked2)
//		{
//			mIsAttacked2 = true;
//		}
//		else
//		{
//			mIsAttacked2 = false;
//		}
//		if (mCurState == eLukeState::L_Attacked3 || mCurState == eLukeState::R_Attacked3)
//		{
//			mIsAttacked3 = true;
//		}
//		else
//		{
//			mIsAttacked3 = false;
//		}
//		if (mCurState == eLukeState::L_Attacked4 || mCurState == eLukeState::R_Attacked4)
//		{
//			mIsAttacked4 = true;
//		}
//		else
//		{
//			mIsAttacked4 = false;
//		}
//
//		if (mCurState == eLukeState::L_Downed || mCurState == eLukeState::R_Downed)
//		{
//			mIsDowned = true;
//		}
//		else
//		{
//			mIsDowned = false;
//		}
//
//		// GetUp 상태 변수 동기화
//		if (mCurState == eLukeState::L_GetUp || mCurState == eLukeState::R_GetUp)
//		{
//			mIsGetUp = true;
//		}
//		else
//		{
//			mIsGetUp = false;
//		}
//
//		// 공격 상태 변수 동기화
//		if (mCurState == eLukeState::L_ArmAttack || mCurState == eLukeState::R_ArmAttack)
//		{
//			mIsArm = true;
//		}
//		else
//		{
//			mIsArm = false;
//		}
//		if (mCurState == eLukeState::L_KickAttack || mCurState == eLukeState::R_KickAttack)
//		{
//			mIsKick = true;
//		}
//		else
//		{
//			mIsKick = false;
//		}
//		if (mCurState == eLukeState::L_SideKickAttack || mCurState == eLukeState::R_SideKickAttack)
//		{
//			mIsSideKick = true;
//		}
//		else
//		{
//			mIsSideKick = false;
//		}
//		if (mCurState == eLukeState::L_UpperAttack || mCurState == eLukeState::R_UpperAttack)
//		{
//			mIsUpper = true;
//		}
//		else
//		{
//			mIsUpper = false;
//		}
//
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//														// 스킬 상태 Update
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		mAttackState[0] = mIsArm;
//		mAttackState[1] = mIsKick;
//		mAttackState[2] = mIsSideKick;
//		mAttackState[3] = mIsUpper;
//	}
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//														// 이벤트
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	void LukeScript::JumpStart()
//	{
//	}
//
//	void LukeScript::Attacked1Complete()
//	{
//		mIsAttacked1 = false;
//		mIsAttacked2 = false;
//		//mIsAttacked3 = false;
//		mIsAttacked4 = false;
//
//		//mIsCollidingFirst = 0;
//
//		if (mPlayerPos.x < mPos.x)
//			ChangeState(eLukeState::L_Idle);
//		else
//			ChangeState(eLukeState::R_Idle);
//	}
//
//	void LukeScript::CombatComplete()
//	{
//		mIsArm = false;
//		mIsKick = false;
//		mIsSideKick = false;
//		mIsUpper = false;
//
//
//		if (mPlayerPos.x < mPos.x)
//			ChangeState(eLukeState::L_Idle);
//		else
//			ChangeState(eLukeState::R_Idle);
//
//		//mCombatInterval = float(rand() % 4 + 1.5f);// 0 ~ 3// 1.5f ~ 4.5f 
//		std::mt19937 mt(rd());
//		std::uniform_int_distribution<int> dist(0, 3);
//		mCombatInterval = (float)(dist(mt) + 1.0f);
//	}
//
//	void LukeScript::GuardComplete()
//	{
//		// 막으려 하는 해당 스킬의 duration이 다르기 때문에 duration 까지 가드를 유지하기 위한 부분 
//		ePlayerState playerState = PlayScene::GetPlayerState();
//		if (playerState == ePlayerState::L_Idle || playerState == ePlayerState::R_Idle || playerState == ePlayerState::L_Walk || playerState == ePlayerState::R_Walk ||
//			playerState == ePlayerState::L_Jump || playerState == ePlayerState::R_Jump || playerState == ePlayerState::L_Run || playerState == ePlayerState::R_Run)
//		{
//			if (mPlayerPos.x < mPos.x)
//				ChangeState(eLukeState::L_Idle);
//			else
//				ChangeState(eLukeState::R_Idle);
//		}
//		else
//		{
//			if (mPlayerPos.x < mPos.x)
//				ChangeState(eLukeState::L_Guard);
//			else
//				ChangeState(eLukeState::R_Guard);
//		}
//	}
//
//	void LukeScript::Attacked3Complete()
//	{
//		mIsAttacked3 = false;
//		mIsDowned = true;
//
//		if (mDirection == eDirection::L)
//			ChangeState(eLukeState::L_Downed);
//		else
//			ChangeState(eLukeState::R_Downed);
//	}
//
//	void LukeScript::DownedComplete()
//	{
//		mIsDowned = false;
//		mIsGetUp = true;
//
//		if (mDirection == eDirection::L)
//			ChangeState(eLukeState::L_GetUp);
//		else
//			ChangeState(eLukeState::R_GetUp);
//	}
//
//	void LukeScript::GetUpComplete()
//	{
//		mIsGetUp = false;
//
//		if (mDirection == eDirection::L)
//			ChangeState(eLukeState::L_Idle);
//		else
//			ChangeState(eLukeState::R_Idle);
//	}
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//															// 충돌
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	void LukeScript::OnCollisionEnter(Collider2D* other)
//	{
//
//	}
//
//	void LukeScript::OnCollisionStay(Collider2D* other)
//	{
//		if (other->GetOwner()->GetName() == L"Ramona")
//		{
//			for (int i = 0; i < 17; i++)
//			{
//				//mPlayerAttackState[i] = other->GetOwner()->GetComponent<RamonaScript>()->mAttackState[i];
//				mPlayerAttackState[i] = (other->GetOwner()->GetComponent<RamonaScript>()->GetAttackState())[i];;
//			}
//
//			if (mSkillCd->GetState() == eColliderState::IsColliding)
//			{
//				int a = 0;
//			}
//
//			if (mBodyCd->GetState() == eColliderState::IsColliding)
//			{
//				int b = 0;
//			}
//		}
//	}
//
//	void LukeScript::OnCollisionExit(Collider2D* other)
//	{
//		if (other->GetOwner()->GetName() == L"Ramona")
//		{
//			// OnCollsionExit 상태로 충돌이 끝나면 false로 변경
//			//this->GetOwner()->GetComponent<Collider2D>()->SetState(eColliderState::NotColliding);// 이것도 해줄 필요 없지않은가???
//			//mIsAttacked1 = false;
//		}
//	}
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//														// 동작 내부 함수
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	void LukeScript::Combat()
//	{
//		mIsCombat = true;
//
//		mCombatTimer -= Time::DeltaTime();
//
//		if (mCombatTimer <= 0.0f)
//		{
//			// 공격 방어 스킬들 중 하나를 랜덤으로 실행
//			std::mt19937 mt(rd());
//			std::uniform_int_distribution<int> dist(0, (int)eLukeCombatState::End - 1);
//			int randStateNum = dist(mt);
//			//int randStateNum = rand() % (int)eLukeCombatState::End;
//
//			switch (static_cast<eLukeCombatState>(randStateNum))
//			{
//			case eLukeCombatState::ArmAttack:
//				mIsArm = true;
//
//				if (mPlayerPos.x < mPos.x)
//					ChangeState(eLukeState::L_ArmAttack);
//				else
//					ChangeState(eLukeState::R_ArmAttack);
//				break;
//
//			case eLukeCombatState::KickAttack:
//				mIsKick = true;
//
//				if (mPlayerPos.x < mPos.x)
//					ChangeState(eLukeState::L_KickAttack);
//				else
//					ChangeState(eLukeState::R_KickAttack);
//				break;
//
//			case eLukeCombatState::SideKickAttack:
//				mIsSideKick = true;
//
//				if (mPlayerPos.x < mPos.x)
//					ChangeState(eLukeState::L_SideKickAttack);
//				else
//					ChangeState(eLukeState::R_SideKickAttack);
//				break;
//
//			case eLukeCombatState::UpperAttack:
//				mIsUpper = true;
//
//				if (mPlayerPos.x < mPos.x)
//					ChangeState(eLukeState::L_UpperAttack);
//				else
//					ChangeState(eLukeState::R_UpperAttack);
//				break;
//
//			default:
//				break;
//			}
//
//			mCombatTimer = mCombatInterval;
//		}
//	}
//
//	void LukeScript::SetAttackedState()
//	{
//		// 플레이어 공격 스킬 확인
//		// 해당 함수 직전에 OnCollisionStay에서 업데이트
//
//		// 플레이어 공격 스킬에 맞는 Attacked 상태 설정
//		// Stun (Attacked1) : mIsNormalAttack1 mIsNormalAttack2 mIsNormalAttack3 mIsRoundKickAttack
//		// Valley (Attacked2) : mIsKickAttack mIsWeaponNormalAttack mIsWeaponSideAttack mIsWeaponStabAttack mIsRunJumpAttack mIsRunWeaponAttack
//		// KnockDown (Attacked3) : mIsJumpDownAttack mIsJumpSlideAttack mIsRunSlideAttack mIsFireBall mIsSuper
//		// Down (Attacked4) : mIsWeaponDownAttack (다운 상태에서만 공격 가능, 다운 상태는 KnockDown되어 GetUp 전의 상태를 의미)
//
//#pragma region bool 변수 참고
//// mAttackState[0] = mIsNormalAttack1;
//// mAttackState[1] = mIsNormalAttack2;
//// mAttackState[2] = mIsNormalAttack3;
//// mAttackState[3] = mIsKickAttack;
//// mAttackState[4] = mIsRoundKickAttack;
//// mAttackState[5] = mIsBehindKickAttack;
//// mAttackState[6] = mIsWeaponNormalAttack;
//// mAttackState[7] = mIsWeaponDownAttack;
//// mAttackState[8] = mIsWeaponSideAttack;
//// mAttackState[9] = mIsWeaponStabAttack;
//// mAttackState[10] = mIsJumpDownAttack;
//// mAttackState[11] = mIsJumpSlideAttack;
//// mAttackState[12] = mIsRunJumpAttack;
//// mAttackState[13] = mIsRunWeaponAttack;
//// mAttackState[14] = mIsRunSlideAttack;
//// mAttackState[15] = mIsFireBall;
//// mAttackState[16] = mIsSuper;
//#pragma endregion
//
//		if (mPlayerAttackState[0] || mPlayerAttackState[1] || mPlayerAttackState[2] || mPlayerAttackState[4] || mPlayerAttackState[5])
//		{
//			if (mPos.x < mPlayerPos.x)// 적 - 플레이어
//			{
//				if (mIsAttacked1 == false)
//				{
//					ChangeState(eLukeState::R_Attacked1);
//					mIsAttacked1 = true;
//				}
//			}
//			else// 플레이어 - 적
//			{
//				if (mIsAttacked1 == false)
//				{
//					ChangeState(eLukeState::L_Attacked1);
//					mIsAttacked1 = true;
//				}
//			}
//		}
//
//		else if (mPlayerAttackState[3] || mPlayerAttackState[6] || mPlayerAttackState[8] || mPlayerAttackState[9] || mPlayerAttackState[12] || mPlayerAttackState[13])
//		{
//			if (mPos.x < mPlayerPos.x)// 적 - 플레이어
//			{
//				if (mIsAttacked2 == false)
//				{
//					ChangeState(eLukeState::R_Attacked2);
//					mIsAttacked2 = true;
//				}
//			}
//			else// 플레이어 - 적
//			{
//				if (mIsAttacked2 == false)
//				{
//					ChangeState(eLukeState::L_Attacked2);
//					mIsAttacked2 = true;
//				}
//			}
//		}
//
//		else if (mPlayerAttackState[10] || mPlayerAttackState[11] || mPlayerAttackState[14] || mPlayerAttackState[15] || mPlayerAttackState[16])
//		{
//			if (mPos.x < mPlayerPos.x)// 적 - 플레이어
//			{
//				if (mIsAttacked3 == false)
//				{
//					ChangeState(eLukeState::R_Attacked3);
//					mIsAttacked3 = true;
//				}
//			}
//			else// 플레이어 - 적
//			{
//				if (mIsAttacked3 == false)
//				{
//					ChangeState(eLukeState::L_Attacked3);
//					mIsAttacked3 = true;
//				}
//			}
//		}
//
//		else if (mPlayerAttackState[7])
//		{
//			if (mPos.x < mPlayerPos.x)// 적 - 플레이어
//			{
//				if (mIsAttacked4 == false)
//				{
//					ChangeState(eLukeState::R_Attacked4);
//					mIsAttacked4 = true;
//				}
//			}
//			else// 플레이어 - 적
//			{
//				if (mIsAttacked4 == false)
//				{
//					ChangeState(eLukeState::L_Attacked4);
//					mIsAttacked4 = true;
//				}
//			}
//		}
//	}
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													// 상태 애니메이션 함수
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	void LukeScript::L_idle()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_Idle", true);
//	}
//	void LukeScript::R_idle()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_Idle", true);
//	}
//	void LukeScript::L_angry()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_Angry", true);
//	}
//	void LukeScript::R_angry()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_Angry", true);
//	}
//	void LukeScript::L_walk()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_Walk", true);
//	}
//	void LukeScript::R_walk()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_Walk", true);
//	}
//	void LukeScript::L_run()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_Run", true);
//	}
//	void LukeScript::R_run()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_Run", true);
//	}
//	void LukeScript::L_armattack()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_ArmAttack", true);
//	}
//	void LukeScript::R_armattack()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_ArmAttack", true);
//	}
//	void LukeScript::L_kickattack()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_KickAttack", true);
//	}
//	void LukeScript::R_kickattack()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_KickAttack", true);
//	}
//	void LukeScript::L_sidekickattack()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_SideKickAttack", true);
//	}
//	void LukeScript::R_sidekickattack()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_SideKickAttack", true);
//	}
//	void LukeScript::L_upperattack()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_UpperAttack", true);
//	}
//	void LukeScript::R_upperattack()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_UpperAttack", true);
//	}
//	void LukeScript::L_guard()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_Guard", true);
//	}
//	void LukeScript::R_guard()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_Guard", true);
//	}
//	void LukeScript::L_attacked1()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_Attacked1", true);
//	}
//	void LukeScript::R_attacked1()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_Attacked1", true);
//	}
//	void LukeScript::L_attacked2()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_Attacked2", true);
//	}
//	void LukeScript::R_attacked2()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_Attacked2", true);
//	}
//	void LukeScript::L_attacked3()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_Attacked3", true);
//	}
//	void LukeScript::R_attacked3()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_Attacked3", true);
//	}
//	void LukeScript::L_attacked4()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_Attacked4", true);
//	}
//	void LukeScript::R_attacked4()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_Attacked4", true);
//	}
//	void LukeScript::L_getup()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_GetUp", true);
//	}
//	void LukeScript::R_getup()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_GetUp", true);
//	}
//	void LukeScript::L_downed()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_Downed", true);
//	}
//	void LukeScript::R_downed()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_Downed", true);
//	}
//	void LukeScript::L_dead()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_Dead", true);
//	}
//	void LukeScript::R_dead()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_Dead", true);
//	}
//	void LukeScript::L_flying()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_Flying", true);
//	}
//	void LukeScript::R_flying()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_Flying", true);
//	}
//	void LukeScript::L_raiding()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"L_Raiding", true);
//	}
//	void LukeScript::R_raiding()
//	{
//		Animator* at = this->GetOwner()->GetComponent<Animator>();
//		at->PlayAnimation(L"R_Raiding", true);
//	}
//}
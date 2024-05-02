#include "yaPlayScene.h"

#include "yaMesh.h"
#include "yaRenderer.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"

#include "yaTransform.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaObject.h"
#include "yaCollider2D.h"
#include "yaCollisionManager.h"
#include "yaRigidbody.h"
#include "yaAnimator.h"
#include "yaLight.h"
#include "yaSceneManager.h"

#include "yaAudioListener.h"
#include "yaAudioClip.h"
#include "yaAudioSource.h"

#include "yaGridScript.h"
#include "yaCamera.h"
#include "yaCameraScript.h"

#include "yaRamonaScript.h"
#include "yaLukeScript.h"
#include "yaBoss01Script.h"
#include "yaLeeScript.h"
#include "yaJesseScript.h"
#include "yaDogScript.h"
#include "yaLinusScript.h"
#include "yaHarleyScript.h"

#include "yaBoss01Scene.h"

#include "yaAudioListener.h"
#include "yaAudioClip.h"
#include "yaAudioSource.h"

#include "..\\Editor_Window\\yaDebugLog.h"

namespace ya
{
	GameObject* PlayScene::mRamona = nullptr;
	Vector3 PlayScene::mRamonaPos = Vector3::Zero;
	eDirection PlayScene::mRamonaDir = eDirection::R;
	ePlayerState PlayScene::mRamonaState = ePlayerState::R_Idle;
	bool PlayScene::mRamonaDead = false;

	int PlayScene::mHeart = 1000;
	int PlayScene::mHp = 1000;
	int PlayScene::mSp = 1000;

	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		// CollisionLayer
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Enemy, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Camera, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::Camera, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::Enemy, true);

		// STAGE 01 - BG 
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BG_STAGE01_01", L"..\\Resources\\SCENE\\STAGE01\\BG_STAGE01_01.png");

			mBG_STAGE01_01 = object::Instantiate<GameObject>(Vector3(-16.0f, -0.34f, 50.0f)
				, Vector3(texture.get()->GetImageRatioOfWidth(), texture.get()->GetImageRatioOfHeight(), 0.0f) * 272.0f
				, eLayerType::BG);// Player로 설정
			mBG_STAGE01_01->SetName(L"BG_STAGE01_01");

			MeshRenderer* mr = mBG_STAGE01_01->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_BG_STAGE01_01"));
			//player->AddComponent<CameraScript>();
		}

		// STAGE 01 - UI
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"UI_STAGE01_STATE", L"..\\Resources\\SCENE\\STAGE01\\UI_STAGE01_STATE.png");

			mUI_STAGE01_STATE = object::Instantiate<GameObject>(Vector3(-2.1f, 1.4f, 49.f)
				, Vector3(texture.get()->GetImageRatioOfWidth(), texture.get()->GetImageRatioOfHeight(), 0.0f) * 4.0f
				, eLayerType::UI);
			mUI_STAGE01_STATE->SetName(L"UI_STAGE01_STATE");

			MeshRenderer* mr = mUI_STAGE01_STATE->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_UI_STAGE01_STATE"));

			Collider2D* cd = mUI_STAGE01_STATE->AddComponent<Collider2D>();
			cd->SetCenter(Vector2(0.0f, 0.0f));

			//{// 콜라이더 추가하고 comps를 불러오는 GetComponents 활용법
			//	cd = mUI_STAGE01_STATE->AddComponent<Collider2D>();
			//	std::vector<Collider2D*> comps
			//		= mUI_STAGE01_STATE->GetComponents<Collider2D>();
			//}

			//// 부모 자식 Transform
			//{
			//	GameObject* mTemp = new GameObject();
			//	mTemp->SetName(L"Temp");
			//	AddGameObject(eLayerType::UI, mTemp);
			//	MeshRenderer* mr2 = mTemp->AddComponent<MeshRenderer>();
			//	mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			//	mr2->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_UI_STAGE01_STATE"));
			//	mTemp->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
			//	//player->AddComponent<CameraScript>();

			//	mTemp->GetComponent<Transform>()->SetParent(mUI_STAGE01_STATE->GetComponent<Transform>());

			//	mUI_STAGE01_STATE->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0001f));
			//	mUI_STAGE01_STATE->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, 45.f));

			//	Vector3 pos = mUI_STAGE01_STATE->GetComponent<Transform>()->GetRotation();
			//}
		}

		// 플레이어
		{
			mRamona
				= object::Instantiate<GameObject>(Vector3(-2.0f, 0.0f, 40.f)
					, Vector3::One * 3
					, eLayerType::Player);
			mRamona->SetName(L"Ramona");

			MeshRenderer* mr = mRamona->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Ramona_Idle", L"..\\Resources\\TEXTURE\\RAMONA\\Idle.png");
			Animator* at = mRamona->AddComponent<Animator>();
			at->Create(L"Ramona_temp", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 6);
			at->PlayAnimation(L"Ramona_temp", true);

			Rigidbody* rb = mRamona->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);
				
			mRamona->AddComponent<RamonaScript>();

			//AudioSource* as = mRamona->AddComponent<AudioSource>();
			//as->SetClip(Resources::Load<AudioClip>(L"TestSound", L"..\\Resources\\Sound\\0.mp3"));
			//as->Play();
		}

		// 몬스터
		InitializeEnemy();

		// Light
		{
			mDirectionalLight = new GameObject();
			mDirectionalLight->SetName(L"Light1");
			AddGameObject(eLayerType::Light, mDirectionalLight);
			Light* lightComp = mDirectionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			//lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			lightComp->SetColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
		}
		{
			mPointLight = new GameObject();
			mPointLight->SetName(L"Light2");
			AddGameObject(eLayerType::Light, mPointLight);
			Light* lightComp = mPointLight->AddComponent<Light>();
			Transform* tr = mPointLight->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, tr->GetPosition().z));
			lightComp->SetType(eLightType::Point);
			lightComp->SetColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
			lightComp->SetRadius(0.0f);
		}

		// Main Camera
		Camera* cameraComp = nullptr;

		{
			mMainCamera = new GameObject();
			mMainCamera->SetName(L"MainCamera");
			AddGameObject(eLayerType::Camera, mMainCamera);
			mMainCamera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = mMainCamera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			mMainCamera->AddComponent<CameraScript>();
			CameraScript* cameraScript = mMainCamera->GetComponent<CameraScript>();
			//cameraScript->SetCameraSetting(eCameraSetting::Static);
			//cameraScript->SetCameraSetting(eCameraSetting::Tracking, GetPlayerPosition());
			//cameraScript->SetCameraSetting(eCameraSetting::SmoothingTransition, Vector3(2.0f, -1.2f, 40.f), 1.0f);
			//cameraScript->SetCameraSetting(eCameraSetting::ShakeVertical, 5.0f, 20.0f, 0.1f);
			//cameraScript->SetCameraSetting(eCameraSetting::ShakeHorizontal, 5.0f, 20.0f, 0.1f);
			//cameraScript->SetCameraSetting(eCameraSetting::ShakeZoom, 5.0f, 0.1f, 5.0f);
			//cameraScript->SetCameraSetting(eCameraSetting::ShakeCircle, 5.0f, 15.0f, 0.3f);

			renderer::cameras.push_back(cameraComp);// Main Camera 렌더러에 추가
			renderer::mainCamera = cameraComp;

			mMainCamera->AddComponent<AudioListener>();
		}

		// UI Camera
		{
			GameObject* camera = new GameObject();
			camera->SetName(L"UICamera");
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::BG, false);
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::Enemy, false);
			//camera->AddComponent<CameraScript>();
		}

		{
			mBgm = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 50.f)
				, Vector3::One
				, eLayerType::UI);
			AudioSource* as = mBgm->AddComponent<AudioSource>();
		}
		{
			mExitSound = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 50.f)
				, Vector3::One
				, eLayerType::UI);
			AudioSource* as = mExitSound->AddComponent<AudioSource>();
		}
	}

	void PlayScene::Update()
	{
		//Transform* tr = mBG_PLAY_01->GetComponent<Transform>();
		//Vector3 pos = tr->GetPosition();
		//pos.x -= 1.0f * Time::DeltaTime();
		//tr->SetPosition(pos);

		if (IsPlayerExist())
		{
			Transform* tr = mRamona->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			mRamonaPos = pos;
			mRamonaDir = mRamona->GetComponent<RamonaScript>()->GetDirection();
			mRamonaState = mRamona->GetComponent<RamonaScript>()->GetState();
			mRamonaDead = mRamona->GetComponent<RamonaScript>()->IsDead();

			if (mHeart != 1000)
			{
				mHeart = mRamona->GetComponent<RamonaScript>()->GetHeart();
				mHp = mRamona->GetComponent<RamonaScript>()->GetHp();
				mSp = mRamona->GetComponent<RamonaScript>()->GetSp();
			}

			{
				std::wstring str = std::to_wstring(mRamona->GetComponent<Transform>()->GetPosition().x);
				std::wstring str1 = std::to_wstring(mRamona->GetComponent<Transform>()->GetPosition().y);
				//if (mLuke01 != nullptr)
				//{
				//	if (mLuke01->GetState() == GameObject::eState::Active)
				//		str4 = std::to_wstring(mLuke01->GetComponent<LukeScript>()->GetHp());
				//}
				//if (mLuke02 != nullptr)
				//{
				//	if (mLuke02->GetState() == GameObject::eState::Active)
				//		str5 = std::to_wstring(mLuke02->GetComponent<LukeScript>()->GetHp());
				//}
				//if (mLuke03 != nullptr)
				//{
				//	if (mLuke03->GetState() == GameObject::eState::Active)
				//		str6 = std::to_wstring(mLuke03->GetComponent<LukeScript>()->GetHp());
				//}

				ya::DebugLog::PrintDebugLog(L"x: " + str + L" y: " + str1);
			}
			{
				if (mPhase == 0 && GetPlayerPosition().x >= 2.5f)
				{
					//cameraScript->SetCameraSetting(eCameraSetting::Static);
					//cameraScript->SetCameraSetting(eCameraSetting::Tracking, GetPlayerPosition());
					mMainCamera->GetComponent<CameraScript>()->SetCameraSetting(eCameraSetting::SmoothingTransition
						, Vector3(GetPlayerPosition().x, 0.0, 40.f), 7.0f);

					if (abs(mMainCamera->GetComponent<Transform>()->GetPosition().x
						- GetPlayerPosition().x) <= 0.01f)
					{
						mMainCamera->GetComponent<CameraScript>()->SetCameraSetting(eCameraSetting::Tracking, GetPlayerPosition());

						mPhase = 1;
					}
					//cameraScript->SetCameraSetting(eCameraSetting::ShakeVertical, 5.0f, 20.0f, 0.1f);
					//cameraScript->SetCameraSetting(eCameraSetting::ShakeHorizontal, 5.0f, 20.0f, 0.1f);
					//cameraScript->SetCameraSetting(eCameraSetting::ShakeZoom, 5.0f, 0.1f, 5.0f);
					//cameraScript->SetCameraSetting(eCameraSetting::ShakeCircle, 5.0f, 15.0f, 0.3f);
				}

				// 본인 등장하는 페이즈가 아닌 경우는 Paused 걸어두거나
				// Script에서 플레이어와 x축 거리가 일정 간격 이하가 되면 Update 돌기(?)

				if (mPhase == 1 && GetPlayerPosition().x >= 7.2f)
				{
					mMainCamera->GetComponent<CameraScript>()->SetCameraSetting(eCameraSetting::Static);
					mPhase = 2;
				}

				if (mPhase == 2 && GetPlayerPosition().x >= 9.69f)
				{
					mMainCamera->GetComponent<CameraScript>()->SetCameraSetting(eCameraSetting::SmoothingTransition
						, Vector3(14.0f, 0.0, 40.f), 7.0f);

					if (mMainCamera->GetComponent<Transform>()->GetPosition().x >= 12.0f)
					{
						mMainCamera->GetComponent<CameraScript>()->SetCameraSetting(eCameraSetting::Static);

						mPhase = 3;
					}
				}

				if (mPhase == 3 && GetPlayerPosition().x >= 14.5f)
				{
					mMainCamera->GetComponent<CameraScript>()->SetCameraSetting(eCameraSetting::SmoothingTransition
						, Vector3(GetPlayerPosition().x, 0.0, 40.f), 7.0f);

					if (abs(mMainCamera->GetComponent<Transform>()->GetPosition().x
						- GetPlayerPosition().x) <= 0.01f)
					{
						mPhase = 4;
					}
				}

				if (mPhase == 4) 
				{
					mMainCamera->GetComponent<CameraScript>()->SetCameraSetting(eCameraSetting::Tracking, GetPlayerPosition());

					if (GetPlayerPosition().x > 38.0f)
					{
						mMainCamera->GetComponent<CameraScript>()->SetCameraSetting(eCameraSetting::SmoothingTransition
							, Vector3(48.0f, 0.0, 40.f), 7.0f);

						if (mMainCamera->GetComponent<Transform>()->GetPosition().x >= 48.0f)
						{
							mPhase = 5;
						}
					}
				}

				if (mPhase == 5)
				{
					mPhase05Time -= Time::DeltaTime();
					if (mPhase05Time <= 0.0f)
					{
						mMainCamera->GetComponent<CameraScript>()->SetCameraSetting(eCameraSetting::SmoothingTransition
							, Vector3(GetPlayerPosition().x, 0.0, 40.f), 12.0f);

						if (abs(mMainCamera->GetComponent<Transform>()->GetPosition().x
							- GetPlayerPosition().x) <= 0.01f)
						{
							mPhase = 6;
						}
					}
				}

				if (mPhase == 6)
				{
					mMainCamera->GetComponent<CameraScript>()->SetCameraSetting(eCameraSetting::Tracking, GetPlayerPosition());

					if (GetPlayerPosition().x >= 48.0f)
					{
						mPhase = 7;
					}
				}

				if (mPhase == 7)
				{
					mMainCamera->GetComponent<CameraScript>()->SetCameraSetting(eCameraSetting::Static);
				}
			}
		}

		if (mEnterLight == true)// 들어올 때
		{
			Light* directionallightComp = mDirectionalLight->GetComponent<Light>();

			totalTimeEnter += Time::DeltaTime();
			float speed = std::log(totalTimeEnter + 1) * mMaxValue / std::log(duration + 1);
			mCurrentValue += speed * Time::DeltaTime();

			if (mCurrentValue > mMaxValue)
			{
				mCurrentValue = mMaxValue;

				directionallightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));
				
				{
					mHeart = mRamona->GetComponent<RamonaScript>()->GetHeart();
					mHp = mRamona->GetComponent<RamonaScript>()->GetHp();
					mSp = mRamona->GetComponent<RamonaScript>()->GetSp();
				}

				mEnterLight = false;
			}

			directionallightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));
		}
		if (mExitLight == true)// 나갈 때
		{
			// 플레이어 체력 전달
			if(mHeart != 1000)
			{
				Boss01Scene::mAttributeTmp[0] = mHeart;
				Boss01Scene::mAttributeTmp[1] = mHp;
				Boss01Scene::mAttributeTmp[2] = mSp;

				mHp = 1000;
				mSp = 1000;
				mHeart = 1000;
			}

			Light* directionallightComp = mDirectionalLight->GetComponent<Light>();

			totalTimeExit -= Time::DeltaTime();
			if (totalTimeExit <= 0.0f)
			{
				directionallightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));

				mExitLight = false;

				if (mRamonaDead == true)
					SceneManager::LoadScene(L"MainScene");

				else
					SceneManager::LoadScene(L"Boss01Scene");
			}

			directionallightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));
		}

		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			mExitLight = true;

			mBG_STAGE01_01->GetComponent<Transform>()->SetPosition(Vector3(-64.0f, 0.0f, 40.f));
			mRamona->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 40.f));
			mMainCamera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));

			if (mRamonaDead == true)
			{
				AudioSource* as = mBgm->GetComponent<AudioSource>();
				as->Stop();

				as = mExitSound->GetComponent<AudioSource>();
				as->SetClip(Resources::Load<AudioClip>(L"STAGE01_LOSE", L"..\\Resources\\Sound\\STAGE01\\STAGE01_LOSE.mp3"));
				as->Play();
				//as->SetVolume(50.0f);
			}
			else
			{
				// 씬 넘어갈 때 틀 사운드
				AudioSource* as = mExitSound->GetComponent<AudioSource>();
				as->SetClip(Resources::Load<AudioClip>(L"STAGE01_EXIT", L"..\\Resources\\Sound\\STAGE01\\STAGE01_EXIT.mp3"));
				as->Play();
				//as->SetVolume(50.0f);
			}
		}


		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Vector3 pos(640, 360, 0.0f);
		Vector3 pos2(640, 360, 1000.0f);
		Viewport viewport;
		viewport.width = 1280.0f;
		viewport.height = 720.0f;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		pos = viewport.Unproject(pos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		pos2 = viewport.Unproject(pos2, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{
		mEnterLight = true;

		AudioSource* as = mBgm->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"STAGE01_BGM", L"..\\Resources\\Sound\\STAGE01\\STAGE01_BGM.mp3"));
		as->SetLoop(true);
		as->Play();
		
		//as->SetVolume(30.0f);
	}

	void PlayScene::OnExit()
	{
		AudioSource* as = mBgm->GetComponent<AudioSource>();
		as->Stop();
	}
	void PlayScene::InitializeEnemy()
	{
	//mLuke02->AddComponent<LukeScript>();
	//mLuke02->AddComponent<JesseScript>();
	//mLuke02->AddComponent<LeeScript>();
	//mLuke02->AddComponent<DogScript>();
	//mLuke02->AddComponent<LinusScript>();
	//mLuke02->AddComponent<HarleyScript>();

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////		1구역		/////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			mEnemy01
				= object::Instantiate<GameObject>(Vector3(2.0f, -1.2f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mEnemy01->SetName(L"mEnemy01");

			MeshRenderer* mr = mEnemy01->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle01", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mEnemy01->AddComponent<Animator>();
			at->Create(L"Luke_temp01", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp01", true);

			Rigidbody* rb = mEnemy01->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mEnemy01->AddComponent<LukeScript>();
		}
		{
			mEnemy02
				= object::Instantiate<GameObject>(Vector3(1.5f, 0.5f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mEnemy02->SetName(L"mEnemy02");

			MeshRenderer* mr = mEnemy02->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle02", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mEnemy02->AddComponent<Animator>();
			at->Create(L"Luke_temp02", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp02", true);

			Rigidbody* rb = mEnemy02->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mEnemy02->AddComponent<JesseScript>();
		}
		{
			mEnemy03
				= object::Instantiate<GameObject>(Vector3(1.7f, -0.5f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mEnemy03->SetName(L"mEnemy03");

			MeshRenderer* mr = mEnemy03->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle03", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mEnemy03->AddComponent<Animator>();
			at->Create(L"Luke_temp03", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp03", true);

			Rigidbody* rb = mEnemy03->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mEnemy03->AddComponent<LukeScript>();
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////		2구역		/////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			mEnemy04
				= object::Instantiate<GameObject>(Vector3(8.2f, 0.39f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mEnemy04->SetName(L"mEnemy04");

			MeshRenderer* mr = mEnemy04->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle04", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mEnemy04->AddComponent<Animator>();
			at->Create(L"Luke_temp04", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp04", true);

			Rigidbody* rb = mEnemy04->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mEnemy04->AddComponent<LukeScript>();
		}
		{
			mEnemy05
				= object::Instantiate<GameObject>(Vector3(9.2f, -0.07f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mEnemy05->SetName(L"mEnemy05");

			MeshRenderer* mr = mEnemy05->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle05", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mEnemy05->AddComponent<Animator>();
			at->Create(L"Luke_temp05", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp05", true);

			Rigidbody* rb = mEnemy05->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mEnemy05->AddComponent<LinusScript>();
		}
		{
			mEnemy06
				= object::Instantiate<GameObject>(Vector3(9.0f, -1.225f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mEnemy06->SetName(L"mEnemy06");

			MeshRenderer* mr = mEnemy06->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle06", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mEnemy06->AddComponent<Animator>();
			at->Create(L"Luke_temp06", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp06", true);

			Rigidbody* rb = mEnemy06->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mEnemy06->AddComponent<JesseScript>();
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////		3구역		/////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			mEnemy07
				= object::Instantiate<GameObject>(Vector3(13.87f, -0.05f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mEnemy07->SetName(L"mEnemy07");

			MeshRenderer* mr = mEnemy07->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle07", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mEnemy07->AddComponent<Animator>();
			at->Create(L"Luke_temp07", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp07", true);

			Rigidbody* rb = mEnemy07->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mEnemy07->AddComponent<DogScript>();
		}
		{
			mEnemy08
				= object::Instantiate<GameObject>(Vector3(13.84f, -1.22f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mEnemy08->SetName(L"mEnemy08");

			MeshRenderer* mr = mEnemy08->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle08", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mEnemy08->AddComponent<Animator>();
			at->Create(L"Luke_temp08", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp08", true);

			Rigidbody* rb = mEnemy08->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mEnemy08->AddComponent<HarleyScript>();
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////// 4구역 가는 통로	/////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			mEnemy09
				= object::Instantiate<GameObject>(Vector3(19.0f, -1.12f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mEnemy09->SetName(L"mEnemy09");

			MeshRenderer* mr = mEnemy09->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle09", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mEnemy09->AddComponent<Animator>();
			at->Create(L"Luke_temp09", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp09", true);

			Rigidbody* rb = mEnemy09->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mEnemy09->AddComponent<DogScript>();
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////		4구역		/////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			mEnemy10
				= object::Instantiate<GameObject>(Vector3(27.85f, -1.02f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mEnemy10->SetName(L"mEnemy10");

			MeshRenderer* mr = mEnemy10->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle10", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mEnemy10->AddComponent<Animator>();
			at->Create(L"Luke_temp10", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp10", true);

			Rigidbody* rb = mEnemy10->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mEnemy10->AddComponent<DogScript>();
		}
		{
			mEnemy11
				= object::Instantiate<GameObject>(Vector3(30.00f, -1.02f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mEnemy11->SetName(L"mEnemy11");

			MeshRenderer* mr = mEnemy11->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle11", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mEnemy11->AddComponent<Animator>();
			at->Create(L"Luke_temp11", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp11", true);

			Rigidbody* rb = mEnemy11->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mEnemy11->AddComponent<LukeScript>();
		}
		{
			mEnemy12
				= object::Instantiate<GameObject>(Vector3(31.5f, -1.26f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mEnemy12->SetName(L"mEnemy12");

			MeshRenderer* mr = mEnemy12->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle12", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mEnemy12->AddComponent<Animator>();
			at->Create(L"Luke_temp12", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp12", true);

			Rigidbody* rb = mEnemy12->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mEnemy12->AddComponent<DogScript>();
		}
		{
			mEnemy13
				= object::Instantiate<GameObject>(Vector3(33.03f, -1.26f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mEnemy13->SetName(L"mEnemy13");

			MeshRenderer* mr = mEnemy13->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle13", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mEnemy13->AddComponent<Animator>();
			at->Create(L"Luke_temp13", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp13", true);

			Rigidbody* rb = mEnemy13->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mEnemy13->AddComponent<JesseScript>();
		}
	}
}
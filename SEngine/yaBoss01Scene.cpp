#include "yaBoss01Scene.h"

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

#include "yaGridScript.h"
#include "yaCamera.h"
#include "yaCameraScript.h"

#include "yaRamonaScript.h"
#include "yaLukeScript.h"
#include "yaBoss01Script.h"

#include "yaPlayScene.h"

#include "yaAudioListener.h"
#include "yaAudioClip.h"
#include "yaAudioSource.h"

#include "..\\Editor_Window\\yaDebugLog.h"

namespace ya
{
	GameObject* Boss01Scene::mRamona = nullptr;
	Vector3 Boss01Scene::mRamonaPos = Vector3::Zero;
	eDirection Boss01Scene::mRamonaDir = eDirection::R;
	ePlayerState Boss01Scene::mRamonaState = ePlayerState::R_Idle;
	bool Boss01Scene::mRamonaDead = false;

	int Boss01Scene::mHeart = 1000;
	int Boss01Scene::mHp = 1000;
	int Boss01Scene::mSp = 1000;

	int Boss01Scene::mAttributeTmp[3] = {0, };


	Boss01Scene::Boss01Scene()
	{
	}
	Boss01Scene::~Boss01Scene()
	{
	}
	void Boss01Scene::Initialize()
	{
		// CollisionLayer
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Enemy, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Camera, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::Camera, true);
		//CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::Enemy, true);

		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BG_STAGE01_BOSS01", L"..\\Resources\\SCENE\\STAGE01\\BG_STAGE01_BOSS01.png");

			mBG_STAGE01_BOSS01 = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 50.0f)
				, Vector3(texture.get()->GetImageRatioOfWidth(), texture.get()->GetImageRatioOfHeight(), 0.0f) * 14.0f
				, eLayerType::BG);
			mBG_STAGE01_BOSS01->SetName(L"BG_STAGE01_BOSS01");

			MeshRenderer* mr = mBG_STAGE01_BOSS01->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_BG_STAGE01_BOSS01"));
			//player->AddComponent<CameraScript>();
		}

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
		}

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
		}
		{
			mBoss01
				= object::Instantiate<GameObject>(Vector3(2.0f, -1.2f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mBoss01->SetName(L"Boss01");

			MeshRenderer* mr = mBoss01->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"BASIC_BOSS01_IDLE01", L"..\\Resources\\TEXTURE\\STAGE01\\BOSS\\BOSS01\\BASIC\\BOSS01_IDLE.png");
			Animator* at = mBoss01->AddComponent<Animator>();
			at->Create(L"Boss01_temp01", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(864.0f / 6.0f, 144.0f), 6);
			at->PlayAnimation(L"Boss01_temp01", true);

			Rigidbody* rb = mBoss01->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mBoss01->AddComponent<Boss01Script>();
		}

		// Light
		{
			mDirectionalLight = new GameObject();
			mDirectionalLight->SetName(L"Light1");
			AddGameObject(eLayerType::Light, mDirectionalLight);
			Light* lightComp = mDirectionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
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
			lightComp->SetRadius(1.0f);
		}

		// OnEnter에서 생성
		////Main Camera
		//GameObject* camera = new GameObject();
		//AddGameObject(eLayerType::Player, camera);
		//camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		//Camera* cameraComp = camera->AddComponent<Camera>();
		//cameraComp->TurnLayerMask(eLayerType::UI, false);
		//camera->AddComponent<CameraScript>();

		//camera->AddComponent<AudioListener>();

		//// UI Camera
		//{
		//	GameObject* camera = new GameObject();
		//	camera->SetName(L"UICamera");
		//	AddGameObject(eLayerType::Player, camera);
		//	camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		//	Camera* cameraComp = camera->AddComponent<Camera>();
		//	cameraComp->TurnLayerMask(eLayerType::BG, false);// Player를 안보이게 설정
		//	//camera->AddComponent<CameraScript>();
		//}

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

	void Boss01Scene::Update()
	{
		if (IsPlayerExist())
		{
			Transform* tr = mRamona->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			mRamonaPos = pos;

			mRamonaDir = mRamona->GetComponent<RamonaScript>()->GetDirection();

			mRamonaState = mRamona->GetComponent<RamonaScript>()->GetState();

			mRamonaDead = mRamona->GetComponent<RamonaScript>()->IsDead();

			if(Boss01Scene::mHeart != 1000)
			{
				// 서로 연동
				Boss01Scene::mHeart = mRamona->GetComponent<RamonaScript>()->GetHeart();
				Boss01Scene::mHp = mRamona->GetComponent<RamonaScript>()->GetHp();
				Boss01Scene::mSp = mRamona->GetComponent<RamonaScript>()->GetSp();

				PlayScene::mHeart = Boss01Scene::mHeart;
				PlayScene::mHp = Boss01Scene::mHp;
				PlayScene::mSp = Boss01Scene::mSp;
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
				// 플레이어 체력 전달 받음
				{
					Boss01Scene::mHeart = mAttributeTmp[0];
					Boss01Scene::mHp = mAttributeTmp[1];
					Boss01Scene::mSp = mAttributeTmp[2];

					mRamona->GetComponent<RamonaScript>()->SetHeart(Boss01Scene::mHeart);
					mRamona->GetComponent<RamonaScript>()->SetHp(Boss01Scene::mHp);
					mRamona->GetComponent<RamonaScript>()->SetSp(Boss01Scene::mSp);
				}

				mCurrentValue = mMaxValue;

				directionallightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));

				mEnterLight = false;
			}

			directionallightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));
		}
		if (mExitLight == true)// 나갈 때
		{

			Light* directionallightComp = mDirectionalLight->GetComponent<Light>();
			//Light* pointlightComp = mPointLight->GetComponent<Light>();

			totalTimeExit += Time::DeltaTime();
			float speed = std::log(totalTimeExit + 1) * mCurrentValue / std::log(duration + 1);
			mCurrentValue -= speed * Time::DeltaTime();

			if (mCurrentValue <= mMinValue)
			{
				mCurrentValue = mMinValue;

				directionallightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));
				//pointlightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));

				mExitLight = false;

				if (mRamonaDead == true)
					SceneManager::LoadScene(L"MainScene");

				else
					SceneManager::LoadScene(L"EndingScene");
			}

			directionallightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));
			//pointlightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));
		}

		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			mExitLight = true;

			Boss01Scene::mHeart = 1000;
			Boss01Scene::mHp = 1000;
			Boss01Scene::mSp = 1000;

			PlayScene::mHeart = 1000;
			PlayScene::mHp = 1000;
			PlayScene::mSp = 1000;

			if (mRamonaDead == true)
			{
				AudioSource* as = mBgm->GetComponent<AudioSource>();
				as->Stop();

				as = mExitSound->GetComponent<AudioSource>();
				as->SetClip(Resources::Load<AudioClip>(L"BOSS01_LOSE", L"..\\Resources\\Sound\\BOSS01\\BOSS01_LOSE.mp3"));
				as->Play();
				//as->SetVolume(50.0f);
			}
			else
			{
				AudioSource* as = mBgm->GetComponent<AudioSource>();
				as->Stop();

				// 씬 넘어갈 때 틀 사운드
				as = mExitSound->GetComponent<AudioSource>();
				as->SetClip(Resources::Load<AudioClip>(L"BOSS01_WIN", L"..\\Resources\\Sound\\BOSS01\\BOSS01_WIN.mp3"));
				as->Play();
				//as->SetVolume(50.0f);
			}
		}

		if (mBgmPhase == 0 && mBoss01->GetComponent<Boss01Script>()->GetPhase() == 2)
		{
			AudioSource* as = mBgm->GetComponent<AudioSource>();
			as->Stop();

			as->SetClip(Resources::Load<AudioClip>(L"BOSS01_BGM02", L"..\\Resources\\Sound\\BOSS01\\BOSS01_BGM02.mp3"));
			as->Play();

			mMainCamera->GetComponent<CameraScript>()->SetCameraSetting(eCameraSetting::ShakeHorizontal, 5.0f, 20.0f, 0.1f);

			mBgmPhase = 1;
		}
		if (mBgmPhase == 1 && mBoss01->GetComponent<Boss01Script>()->GetPhase() == 3)
		{
			AudioSource* as = mBgm->GetComponent<AudioSource>();
			as->Stop();

			as->SetClip(Resources::Load<AudioClip>(L"BOSS01_BGM01", L"..\\Resources\\Sound\\BOSS01\\BOSS01_BGM01.mp3"));
			as->Play();

			mBoss01->GetComponent<Boss01Script>()->SetEffectFlashing(0.2f, 10.0f, Vector4(1.2f, 0.0f, 0.0f, 0.0f));// 덜 RED

			mBgmPhase = 2;
		}
		if (mBgmPhase == 2 && mBoss01->GetComponent<Boss01Script>()->GetPhase() == 4)
		{
			AudioSource* as = mBgm->GetComponent<AudioSource>();
			as->Stop();

			as->SetClip(Resources::Load<AudioClip>(L"BOSS01_BGM03", L"..\\Resources\\Sound\\BOSS01\\BOSS01_BGM03.mp3"));
			as->Play();

			mMainCamera->GetComponent<CameraScript>()->SetCameraSetting(eCameraSetting::ShakeVertical, 5.0f, 20.0f, 0.1f);

			mBoss01->GetComponent<Boss01Script>()->SetEffectFlashing(0.1f, 10.0f, Vector4(4.0f, 0.0f, 0.0f, 0.0f));// 더 RED

			mBgmPhase = 3;
		}


		Scene::Update();
	}

	void Boss01Scene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Boss01Scene::Render()
	{
		Scene::Render();
	}

	void Boss01Scene::OnEnter()
	{
		mEnterLight = true;

		//Main Camera
		mMainCamera = new GameObject();
		AddGameObject(eLayerType::Player, mMainCamera);
		mMainCamera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = mMainCamera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		mMainCamera->AddComponent<CameraScript>();

		mMainCamera->AddComponent<AudioListener>();

		// UI Camera
		{
			GameObject* camera = new GameObject();
			camera->SetName(L"UICamera");
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::BG, false);// Player를 안보이게 설정
			//camera->AddComponent<CameraScript>();
		}

		AudioSource* as = mBgm->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"BOSS01_BGM01", L"..\\Resources\\Sound\\BOSS01\\BOSS01_BGM01.mp3"));
		as->Play();
		//as->SetVolume(30.0f);
	}

	void Boss01Scene::OnExit()
	{
		AudioSource* as = mBgm->GetComponent<AudioSource>();
		as->Stop();
	}
}
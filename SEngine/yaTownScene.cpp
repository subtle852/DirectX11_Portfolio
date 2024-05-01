#include "yaTownScene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaMesh.h"
#include "yaCameraScript.h"
#include "yaCamera.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaObject.h"
#include "yaAnimator.h"
#include "yaRenderer.h"
#include "yaMiniScript.h"
#include "yaLight.h"
#include "yaCollider2D.h"
#include "yaTexture.h"
#include "yaAudioListener.h"
#include "yaAudioClip.h"
#include "yaAudioSource.h"
#include "yaObject.h"
#include "yaAnimator.h"
#include "yaTime.h"

namespace ya
{
	TownScene::TownScene()
	{
	}
	TownScene::~TownScene()
	{
	}
	void TownScene::Initialize()
	{
		// BG 
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BG_TOWN_MAP", L"..\\Resources\\SCENE\\STAGE01\\BG_TOWN_MAP.png");

			mBG_TOWN_MAP = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 50.0f)
				, Vector3(texture.get()->GetImageRatioOfWidth(), texture.get()->GetImageRatioOfHeight(), 0.0f) * 15.0f
				, eLayerType::Player);
			mBG_TOWN_MAP->SetName(L"BG_TOWN_MAP");

			MeshRenderer* mr = mBG_TOWN_MAP->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_BG_TOWN_MAP"));
			//player->AddComponent<CameraScript>();
		}

		// 애니메이션
		{
			GameObject* mPlayer
				= object::Instantiate<GameObject>(Vector3(-2.25f, 1.65f, 49.f)
					, Vector3::One * 4.0f
					, eLayerType::Player);
			mPlayer->SetName(L"MINI");

			//Collider2D* cd = mPlayer->AddComponent<Collider2D>();
			//cd->SetSize(Vector2(5.0f, 5.0f));

			MeshRenderer* mr = mPlayer->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"MINI_CHAR", L"..\\Resources\\TEXTURE\\RAMONA\\MINI_CHAR.png");
			Animator* at = mPlayer->AddComponent<Animator>();
			at->Create(L"MINI_CHAR", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(56.0f / 4.0f, 16.0f), 4);
			at->PlayAnimation(L"MINI_CHAR", true);

			mPlayer->AddComponent<MiniScript>();
		}

		// Light
		{
			mDirectionalLight = new GameObject();
			mDirectionalLight->SetName(L"Light1");
			AddGameObject(eLayerType::Light, mDirectionalLight);
			Light* lightComp = mDirectionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
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
			lightComp->SetColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
			lightComp->SetRadius(1.0f);
		}

		// Main Camera
		{
			GameObject* camera = new GameObject();
			camera->SetName(L"MainCamera");
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		{
			mBgm = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 50.f)
				, Vector3::One
				, eLayerType::UI);
			AudioSource* as = mBgm->AddComponent<AudioSource>();
		}
		{
			mEffect = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 50.f)
				, Vector3::One
				, eLayerType::UI);
			AudioSource* as = mEffect->AddComponent<AudioSource>();
		}
		{
			mEnter = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 50.f)
				, Vector3::One
				, eLayerType::UI);
			AudioSource* as = mEnter->AddComponent<AudioSource>();
		}
	}

	void TownScene::Update()
	{
		if (mEnterLight == true)// 들어올 때
		{
			Light* directionallightComp = mDirectionalLight->GetComponent<Light>();

			totalTimeEnter += Time::DeltaTime();
			float speed = std::log(totalTimeEnter + 1) * mMaxValue / std::log(duration + 1);
			mCurrentValue += speed * Time::DeltaTime();

			if (mCurrentValue >= mMaxValue)
			{
				mCurrentValue = 1.0f;
				directionallightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));

				mEnterLight = false;
			}

			directionallightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));
		}
		if (mExitLight == true)// 나갈 때
		{

			Light* directionallightComp = mDirectionalLight->GetComponent<Light>();

			totalTimeExit += Time::DeltaTime();
			float speed = std::log(totalTimeExit + 1) * mCurrentValue / std::log(duration + 1);
			mCurrentValue -= speed * Time::DeltaTime();

			if (mCurrentValue <= mMinValue)
			{
				directionallightComp->SetColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));

				mCurrentValue = mMinValue;
				mExitLight = false;
				SceneManager::LoadScene(L"PlayScene");
			}

			directionallightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));
		}

		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			AudioSource* as = mEnter->GetComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"SELECT_MAP_ENTER", L"..\\Resources\\Sound\\SELECT_MAP\\SELECT_MAP_ENTER.mp3"));
			as->Play();
			as->SetVolume(10.0f);

			mExitLight = true;
		}

		{
			if (Input::GetKeyDown(eKeyCode::W) || Input::GetKeyDown(eKeyCode::LEFT)
				|| Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::RIGHT)
				|| Input::GetKeyDown(eKeyCode::S) || Input::GetKeyDown(eKeyCode::UP)
				|| Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::DOWN))
			{
				AudioSource* as = mEffect->GetComponent<AudioSource>();
				as->SetClip(Resources::Load<AudioClip>(L"SELECT_MAP_EFFECT", L"..\\Resources\\Sound\\SELECT_MAP\\SELECT_MAP_EFFECT.mp3"));
				as->Play();
				as->SetVolume(30.0f);
			}
		}

		Scene::Update();
	}

	void TownScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void TownScene::Render()
	{
		Scene::Render();
	}

	void TownScene::OnEnter()
	{
		mEnterLight = true;

		AudioSource* as = mBgm->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"SELECT_MAP_BGM", L"..\\Resources\\Sound\\SELECT_MAP\\SELECT_MAP_BGM.mp3"));
		as->Play();
	}

	void TownScene::OnExit()
	{
		AudioSource* as = mBgm->GetComponent<AudioSource>();
		as->Stop();

		as = mEffect->GetComponent<AudioSource>();
		as->Stop();

		as = mEnter->GetComponent<AudioSource>();
		as->Stop();
	}
}
#include "yaSelectScene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaMesh.h"
#include "yaCameraScript.h"
#include "yaCamera.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaLight.h"
#include "yaAudioListener.h"
#include "yaAudioClip.h"
#include "yaAudioSource.h"
#include "yaObject.h"
#include "yaAnimator.h"
#include "yaTime.h"

namespace ya
{
	SelectScene::SelectScene()
	{
	}
	SelectScene::~SelectScene()
	{
	}
	void SelectScene::Initialize()
	{
		{
			mBG_SELECT_CURTAIN = new GameObject();
			AddGameObject(eLayerType::BG, mBG_SELECT_CURTAIN);
			MeshRenderer* mr = mBG_SELECT_CURTAIN->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_BG_SELECT_CURTAIN"));
			mBG_SELECT_CURTAIN->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 50.0f));
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BG_SELECT_CURTAIN", L"..\\Resources\\SCENE\\01_TITLE\\BG_TITLE_01.png");
			mBG_SELECT_CURTAIN->GetComponent<Transform>()->SetScale((Vector3(texture.get()->GetImageRatioOfWidth(),
				texture.get()->GetImageRatioOfHeight(), 0.0f))
				* 13.0f);
			//player->AddComponent<CameraScript>();
		}
		{
			mArrow = new GameObject();
			AddGameObject(eLayerType::Player, mArrow);
			MeshRenderer* mr = mArrow->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_Arrow"));
			mArrow->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 50.0f));
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"SELECT_ARROW", L"..\\Resources\\TEXTURE\\SELECT\\ARROW.png");
			mArrow->GetComponent<Transform>()->SetScale((Vector3(texture.get()->GetImageRatioOfWidth(),
				texture.get()->GetImageRatioOfHeight(), 0.0f))
				* 3.4f);
		}
		{
			mChar01
				= object::Instantiate<GameObject>(Vector3(-1.7f, 0.0f, 40.f)
					, Vector3::One * 3
					, eLayerType::Player);
			mChar01->SetName(L"Char01");

			MeshRenderer* mr = mChar01->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Char01_Idle", L"..\\Resources\\TEXTURE\\SELECT\\01_IDLE.png");
			Animator* at = mChar01->AddComponent<Animator>();
			at->Create(L"Char01_temp", atlas, enums::eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);
			at->PlayAnimation(L"Char01_temp", true);
		} 
		{
			mChar02
				= object::Instantiate<GameObject>(Vector3(-0.6f, 0.0f, 40.f)
					, Vector3::One * 3
					, eLayerType::Player);
			mChar02->SetName(L"Char02");

			MeshRenderer* mr = mChar02->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Char02_Idle", L"..\\Resources\\TEXTURE\\SELECT\\02_IDLE.png");
			Animator* at = mChar02->AddComponent<Animator>();
			at->Create(L"Char02_temp", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);
			at->PlayAnimation(L"Char02_temp", true);
		} 
		{
			mChar03
				= object::Instantiate<GameObject>(Vector3(0.6f, 0.0f, 40.f)
					, Vector3::One * 3
					, eLayerType::Player);
			mChar03->SetName(L"Char03");

			MeshRenderer* mr = mChar03->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Char03_Idle", L"..\\Resources\\TEXTURE\\SELECT\\03_IDLE.png");
			Animator* at = mChar03->AddComponent<Animator>();
			at->Create(L"Char03_temp", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);
			at->PlayAnimation(L"Char03_temp", true);
		}
		{
			mChar04
				= object::Instantiate<GameObject>(Vector3(1.7f, 0.0f, 40.f)
					, Vector3::One * 3
					, eLayerType::Player);
			mChar04->SetName(L"Char04");

			MeshRenderer* mr = mChar04->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Char04_Idle", L"..\\Resources\\TEXTURE\\SELECT\\04_IDLE.png");
			Animator* at = mChar04->AddComponent<Animator>();
			at->Create(L"Char04_temp", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(576.0f / 4.0f, 144.0f), 4);
			at->PlayAnimation(L"Char04_temp", true);
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
			tr->SetPosition(Vector3(-1.7f, 0.0f, tr->GetPosition().z));
			lightComp->SetType(eLightType::Point);
			lightComp->SetColor(Vector4(0.7f, 0.7f, 0.7f, 1.0f));
			lightComp->SetRadius(1.0f);
		}

		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		//camera->AddComponent<CameraScript>();

		camera->AddComponent<AudioListener>();

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

	void SelectScene::Update()
	{
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

				mEnterLight = false;
			}

			directionallightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));
		}
		if (mExitLight == true)// 나갈 때
		{

			Light* directionallightComp = mDirectionalLight->GetComponent<Light>();
			Light* pointlightComp = mPointLight->GetComponent<Light>();

			totalTimeExit += Time::DeltaTime();
			float speed = std::log(totalTimeExit + 1) * mCurrentValue / std::log(duration + 1);
			mCurrentValue -= speed * Time::DeltaTime();

			if (mCurrentValue <= mMinValue)
			{
				mCurrentValue = mMinValue;

				directionallightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));
				pointlightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));

				mExitLight = false;
				SceneManager::LoadScene(L"TownScene");
			}

			directionallightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));
			pointlightComp->SetColor(Vector4(mCurrentValue, mCurrentValue, mCurrentValue, mCurrentValue));
		}

		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			mExitLight = true;

			AudioSource* as = mEnter->GetComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"SELECT_CHAR_ENTER", L"..\\Resources\\Sound\\SELECT_CHAR\\SELECT_CHAR_ENTER.mp3"));
			as->Play();
			as->SetVolume(10.0f);
		}

		{
			if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::LEFT))
			{
				AudioSource* as = mEffect->GetComponent<AudioSource>();
				as->SetClip(Resources::Load<AudioClip>(L"SELECT_CHAR_EFFECT", L"..\\Resources\\Sound\\SELECT_CHAR\\SELECT_CHAR_EFFECT.mp3"));
				as->Play();
				as->SetVolume(10.0f);

				if (mNumber != 0)
					--mNumber;
			}
			if (Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::RIGHT))
			{
				AudioSource* as = mEffect->GetComponent<AudioSource>();
				as->SetClip(Resources::Load<AudioClip>(L"SELECT_CHAR_EFFECT", L"..\\Resources\\Sound\\SELECT_CHAR\\SELECT_CHAR_EFFECT.mp3"));
				as->Play();
				as->SetVolume(10.0f);

				if (mNumber != 3)
					++mNumber;
			}

			if (mNumber == 0)
			{
				mArrow->GetComponent<Transform>()->SetPosition(Vector3(-1.7f, 0.0f, 40.f));

				Transform* tr = mPointLight->GetComponent<Transform>();
				tr->SetPosition(Vector3(-1.7f, 0.0f, tr->GetPosition().z));
			}
			else if (mNumber == 1)
			{
				mArrow->GetComponent<Transform>()->SetPosition(Vector3(-0.6f, 0.0f, 40.f));

				Transform* tr = mPointLight->GetComponent<Transform>();
				tr->SetPosition(Vector3(-0.6f, 0.0f, tr->GetPosition().z));
			}
			else if (mNumber == 2)
			{
				mArrow->GetComponent<Transform>()->SetPosition(Vector3(0.6f, 0.0f, 40.f));

				Transform* tr = mPointLight->GetComponent<Transform>();
				tr->SetPosition(Vector3(0.6f, 0.0f, tr->GetPosition().z));
			}
			else if (mNumber == 3)
			{
				mArrow->GetComponent<Transform>()->SetPosition(Vector3(1.7f, 0.0f, 40.f));

				Transform* tr = mPointLight->GetComponent<Transform>();
				tr->SetPosition(Vector3(1.7f, 0.0f, tr->GetPosition().z));
			}
		}

		Scene::Update();
	}

	void SelectScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void SelectScene::Render()
	{
		Scene::Render();
	}

	void SelectScene::OnEnter()
	{
		mEnterLight = true;

		AudioSource* as = mBgm->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"SELECT_CHAR_BGM", L"..\\Resources\\Sound\\SELECT_CHAR\\SELECT_CHAR_BGM.mp3"));
		as->Play();
		//as->SetVolume(30.0f);

	}

	void SelectScene::OnExit()
	{
		AudioSource* as = mBgm->GetComponent<AudioSource>();
		as->Stop();

		as = mEffect->GetComponent<AudioSource>();
		as->Stop();

		as = mEnter->GetComponent<AudioSource>();
		as->Stop();
	}
}
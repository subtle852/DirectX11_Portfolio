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

#include "..\\Editor_Window\\yaDebugLog.h"

namespace ya
{
	GameObject* Boss01Scene::mRamona = nullptr;
	Vector3 Boss01Scene::mRamonaPos = Vector3::Zero;
	eDirection Boss01Scene::mRamonaDir = eDirection::R;
	ePlayerState Boss01Scene::mRamonaState = ePlayerState::R_Idle;
	bool Boss01Scene::mRamonaDead = false;


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
			GameObject* light = new GameObject();
			light->SetName(L"Light1");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		camera->AddComponent<CameraScript>();

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
		}

		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(L"EndingScene");
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

	}

	void Boss01Scene::OnExit()
	{

	}
}
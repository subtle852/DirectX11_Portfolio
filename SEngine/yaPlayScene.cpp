#include "yaPlayScene.h"

#include "yaTransform.h"
#include "yaMesh.h"
#include "yaRenderer.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"

#include "yaGridScript.h"
#include "yaCamera.h"
#include "yaCameraScript.h"

#include "yaInput.h"
#include "yaTime.h"
#include "yaObject.h"

#include "yaSceneManager.h"
#include "yaCollider2D.h"
#include "yaCollisionManager.h"

#include "yaAnimator.h"
#include "yaLight.h"

#include "yaRamonaScript.h"
#include "yaLukeScript.h"
#include "yaRigidbody.h"

#include "..\\Editor_Window\\yaDebugLog.h"

namespace ya
{
	GameObject* PlayScene::mRamona = nullptr;
	Vector3 PlayScene::mRamonaPos = Vector3::Zero;
	eDirection PlayScene::mRamonaDir = eDirection::R;
	ePlayerState PlayScene::mRamonaState = ePlayerState::R_Idle;
	bool PlayScene::mRamonaDead = false;


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

			mBG_STAGE01_01 = object::Instantiate<GameObject>(Vector3(0.0f, -0.34f, 50.0f)
				, Vector3(texture.get()->GetImageRatioOfWidth(), texture.get()->GetImageRatioOfHeight(), 0.0f) * 272.0f
				, eLayerType::BG);// Player로 설정
			mBG_STAGE01_01->SetName(L"BG_STAGE01_01");

			MeshRenderer* mr = mBG_STAGE01_01->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_BG_STAGE01_01"));
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

		// 애니메이션
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
			mLuke01
				= object::Instantiate<GameObject>(Vector3(2.0f, -1.2f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mLuke01->SetName(L"Luke01");

			MeshRenderer* mr = mLuke01->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle01", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mLuke01->AddComponent<Animator>();
			at->Create(L"Luke_temp01", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp01", true);
			
			Rigidbody* rb = mLuke01->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mLuke01->AddComponent<LukeScript>();
		}
		{
			mLuke02
				= object::Instantiate<GameObject>(Vector3(1.5f, 0.5f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mLuke02->SetName(L"Luke02");

			MeshRenderer* mr = mLuke02->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle02", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mLuke02->AddComponent<Animator>();
			at->Create(L"Luke_temp02", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp02", true);

			Rigidbody* rb = mLuke02->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mLuke02->AddComponent<LukeScript>();
		}
		{
			mLuke03
				= object::Instantiate<GameObject>(Vector3(1.7f, -0.5f, 40.f)
					, Vector3::One * 3
					, eLayerType::Enemy);
			mLuke03->SetName(L"Luke03");

			MeshRenderer* mr = mLuke03->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"Basic_Luke_Idle03", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LUKE\\LUKE_IDLE.png");
			Animator* at = mLuke03->AddComponent<Animator>();
			at->Create(L"Luke_temp03", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(923.0f / 8.0f, 116.0f), 8);
			at->PlayAnimation(L"Luke_temp03", true);

			Rigidbody* rb = mLuke03->AddComponent<Rigidbody>();
			rb->SetGround(true);
			rb->SetMass(1.0f);

			mLuke03->AddComponent<LukeScript>();
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

		//{
		//	GameObject* light = new GameObject();
		//	light->SetName(L"Light2");
		//	AddGameObject(eLayerType::Light, light);
		//	Light* lightComp = light->AddComponent<Light>();
		//	lightComp->SetType(eLightType::Point);
		//	lightComp->SetColor(Vector4(0.5f, 0.5f, 1.0f, 1.0f));
		//	lightComp->SetRadius(3.0f);
		//}

		// Main Camera
		Camera* cameraComp = nullptr;

		{
			GameObject* camera = new GameObject();
			camera->SetName(L"MainCamera");
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			CameraScript* cameraScript = camera->GetComponent<CameraScript>();
			//cameraScript->SetCameraSetting(eCameraSetting::Static);
			//cameraScript->SetCameraSetting(eCameraSetting::Tracking, GetPlayerPosition());
			//cameraScript->SetCameraSetting(eCameraSetting::SmoothingTransition, Vector3(2.0f, -1.2f, 40.f), 1.0f);
			//cameraScript->SetCameraSetting(eCameraSetting::ShakeVertical, 5.0f, 20.0f, 0.1f);
			//cameraScript->SetCameraSetting(eCameraSetting::ShakeHorizontal, 5.0f, 20.0f, 0.1f);
			//cameraScript->SetCameraSetting(eCameraSetting::ShakeZoom, 5.0f, 0.1f, 5.0f);
			//cameraScript->SetCameraSetting(eCameraSetting::ShakeCircle, 5.0f, 15.0f, 0.3f);

			renderer::cameras.push_back(cameraComp);// Main Camera 렌더러에 추가
			renderer::mainCamera = cameraComp;
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


			{
				std::wstring str = std::to_wstring(mRamona->GetComponent<RamonaScript>()->GetHeart());
				std::wstring str1 = std::to_wstring(mRamona->GetComponent<RamonaScript>()->GetHp());
				std::wstring str2 = std::to_wstring(mRamona->GetComponent<RamonaScript>()->GetSp());
				std::wstring str3 = std::to_wstring(mRamona->GetComponent<RamonaScript>()->GetCoin());
				std::wstring str4;
				std::wstring str5;
				std::wstring str6;
				if (mLuke01 != nullptr)
				{
					if (mLuke01->GetState() == GameObject::eState::Active)
						str4 = std::to_wstring(mLuke01->GetComponent<LukeScript>()->GetHp());
				}
				if (mLuke02 != nullptr)
				{
					if (mLuke02->GetState() == GameObject::eState::Active)
						str5 = std::to_wstring(mLuke02->GetComponent<LukeScript>()->GetHp());
				}
				if (mLuke03 != nullptr)
				{
					if (mLuke03->GetState() == GameObject::eState::Active)
						str6 = std::to_wstring(mLuke03->GetComponent<LukeScript>()->GetHp());
				}

				ya::DebugLog::PrintDebugLog(L"Heart: " + str + L" Hp: " + str1 + L" Sp: " + str2 + L" Coin: " + str3
					+ L" || Enemy01Hp: " + str4 + L" || Enemy02Hp: " + str5 + L" || Enemy03Hp: " + str6);
			}
		}



		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(L"ShopScene");
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

	}

	void PlayScene::OnExit()
	{

	}
}
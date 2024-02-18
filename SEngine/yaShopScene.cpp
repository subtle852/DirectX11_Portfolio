#include "yaShopScene.h"
#include "yaObject.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaMesh.h"
#include "yaRenderer.h"
#include "yaCameraScript.h"
#include "yaCamera.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaLight.h"

namespace ya
{
	ShopScene::ShopScene()
	{
	}
	ShopScene::~ShopScene()
	{
	}
	void ShopScene::Initialize()
	{
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BG_STAGE01_SHOP", L"..\\Resources\\SCENE\\STAGE01\\BG_STAGE01_SHOP.png");

			mBG_STAGE01_SHOP = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 50.0f)
				, Vector3(texture.get()->GetImageRatioOfWidth(), texture.get()->GetImageRatioOfHeight(), 0.0f) * 13.f
				, eLayerType::BG);
			mBG_STAGE01_SHOP->SetName(L"BG_STAGE01_SHOP");

			MeshRenderer* mr = mBG_STAGE01_SHOP->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_BG_STAGE01_SHOP"));
			//player->AddComponent<CameraScript>();
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
		//camera->AddComponent<CameraScript>();

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

	void ShopScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(L"Subspace01Scene");
		}

		Scene::Update();
	}

	void ShopScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void ShopScene::Render()
	{
		Scene::Render();
	}

	void ShopScene::OnEnter()
	{

	}

	void ShopScene::OnExit()
	{

	}
}
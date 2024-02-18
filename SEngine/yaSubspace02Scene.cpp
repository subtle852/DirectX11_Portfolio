#include "yaSubspace02Scene.h"
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
	Subspace02Scene::Subspace02Scene()
	{
	}
	Subspace02Scene::~Subspace02Scene()
	{
	}
	void Subspace02Scene::Initialize()
	{
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BG_STAGE01_SUBSPACE02", L"..\\Resources\\SCENE\\STAGE01\\BG_STAGE01_SUBSPACE02.png");

			mBG_STAGE01_SUBSPACE02 = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 50.0f)
				, Vector3(texture.get()->GetImageRatioOfWidth(), texture.get()->GetImageRatioOfHeight(), 0.0f) * 39.0f
				, eLayerType::BG);
			mBG_STAGE01_SUBSPACE02->SetName(L"BG_STAGE01_SUBSPACE02");

			MeshRenderer* mr = mBG_STAGE01_SUBSPACE02->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_BG_STAGE01_SUBSPACE02"));
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

	void Subspace02Scene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(L"Boss01Scene");
		}

		Scene::Update();
	}

	void Subspace02Scene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Subspace02Scene::Render()
	{
		Scene::Render();
	}

	void Subspace02Scene::OnEnter()
	{

	}

	void Subspace02Scene::OnExit()
	{

	}
}
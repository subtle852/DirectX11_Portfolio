#include "yaEndingScene.h"
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
	EndingScene::EndingScene()
	{
	}
	EndingScene::~EndingScene()
	{
	}
	void EndingScene::Initialize()
	{
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BG_ENDING", L"..\\Resources\\SCENE\\ENDING\\BG_ENDING.png");

			mBG_ENDING = object::Instantiate<GameObject>(Vector3(0.0f, -3.8f, 50.0f)
				, Vector3(texture.get()->GetImageRatioOfWidth(), texture.get()->GetImageRatioOfHeight(), 0.0f) * 13.0f
				, eLayerType::BG);
			mBG_ENDING->SetName(L"BG_ENDING");

			MeshRenderer* mr = mBG_ENDING->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_BG_ENDING"));
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
		camera->AddComponent<CameraScript>();
	}

	void EndingScene::Update()
	{
		Scene::Update();
	}

	void EndingScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void EndingScene::Render()
	{
		Scene::Render();
	}

	void EndingScene::OnEnter()
	{

	}

	void EndingScene::OnExit()
	{

	}
}
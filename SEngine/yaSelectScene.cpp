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
		//camera->AddComponent<CameraScript>();
	}

	void SelectScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(L"TownScene");
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

	}

	void SelectScene::OnExit()
	{

	}
}
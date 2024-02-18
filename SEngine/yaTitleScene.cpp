#include "yaTitleScene.h"
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
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		// DepthStencil
		// 들어갈수록 z값이 증가

		// Layer의 타입에 따라 SetPosition의 z 값이 정해지도록
		// ex. BG 50 Player 40 Monster 30 Effect 20 UI 10

		// TITLE
		{
			mBG_TITLE_01 = new GameObject();
			AddGameObject(eLayerType::BG, mBG_TITLE_01);
			MeshRenderer* mr = mBG_TITLE_01->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_BG_TITLE_01"));
			mBG_TITLE_01->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 50.0f));
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BG_TITLE_01", L"..\\Resources\\SCENE\\01_TITLE\\BG_TITLE_01.png");
			mBG_TITLE_01->GetComponent<Transform>()->SetScale((Vector3(texture.get()->GetImageRatioOfWidth(),
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
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			//if (mTitleEnterCount > 0)
			{
				SceneManager::LoadScene(L"MainScene");
			}

			//else
			//{
			//	mBG_TITLE_02 = new GameObject();
			//	AddGameObject(eLayerType::BG, mBG_TITLE_02);
			//	MeshRenderer* mr = mBG_TITLE_02->AddComponent<MeshRenderer>();
			//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			//	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_BG_TITLE_02"));
			//	mBG_TITLE_02->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 49.0f));
			//	std::shared_ptr<Texture> texture
			//		= Resources::Load<Texture>(L"BG_TITLE_02", L"..\\Resources\\SCENE\\01_TITLE\\BG_TITLE_02.png");
			//	mBG_TITLE_02->GetComponent<Transform>()->SetScale((Vector3(texture.get()->GetImageRatioOfWidth(),
			//		texture.get()->GetImageRatioOfHeight(), 0.0f))
			//		* 13.0f);
			//	//player->AddComponent<CameraScript>();

			//	mTitleEnterCount = 1;
			//}
		}

		Scene::Update();
	}

	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void TitleScene::Render()
	{
		Scene::Render();
	}

	void TitleScene::OnEnter()
	{

	}

	void TitleScene::OnExit()
	{

	}
}
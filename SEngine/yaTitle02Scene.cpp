#include "yaTitle02Scene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaMesh.h"
#include "yaCameraScript.h"
#include "yaCamera.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaLight.h"
#include "yaTime.h"

namespace ya
{
	Title02Scene::Title02Scene()
	{
	}
	Title02Scene::~Title02Scene()
	{
	}
	void Title02Scene::Initialize()
	{
		// DepthStencil
		// 들어갈수록 z값이 증가

		// Layer의 타입에 따라 SetPosition의 z 값이 정해지도록
		// ex. BG 50 Player 40 Monster 30 Effect 20 UI 10

		// TITLE 02
		{
			mBG_TITLE02_01 = new GameObject();
			AddGameObject(eLayerType::BG, mBG_TITLE02_01);
			MeshRenderer* mr = mBG_TITLE02_01->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_BG_TITLE02_01"));
			mBG_TITLE02_01->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 50.0f));
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BG_TITLE02_01", L"..\\Resources\\SCENE\\01_TITLE\\BG_TITLE01_01.png");
			mBG_TITLE02_01->GetComponent<Transform>()->SetScale((Vector3(texture.get()->GetImageRatioOfWidth(),
				texture.get()->GetImageRatioOfHeight(), 0.0f))
				* 13.0f);
			//player->AddComponent<CameraScript>();
		}
		{
			mUI_TITLE02_ENTER = new GameObject();
			AddGameObject(eLayerType::UI, mUI_TITLE02_ENTER);
			MeshRenderer* mr2 = mUI_TITLE02_ENTER->AddComponent<MeshRenderer>();
			mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr2->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_UI_TITLE02_ENTER"));
			mUI_TITLE02_ENTER->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.05f, 49.0f));
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BG_TITLE02_01", L"..\\Resources\\SCENE\\01_TITLE\\BG_TITLE01_01.png");
			mUI_TITLE02_ENTER->GetComponent<Transform>()->SetScale((Vector3(texture.get()->GetImageRatioOfWidth(),
				texture.get()->GetImageRatioOfHeight(), 0.0f))
				* 13.0f);
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

	void Title02Scene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(L"MainScene");
		}


		Transform* mUI_TITLE02_ENTER_tr = mUI_TITLE02_ENTER->GetComponent<Transform>();
		Vector3 mUI_TITLE02_ENTER_scale = mUI_TITLE02_ENTER_tr->GetScale();

		if (mUI_TITLE02_ENTER_scale.x <= 6.4f)
		{
			mUI_TITLE02_ENTER_SizeState = true;
		}
		else if (mUI_TITLE02_ENTER_scale.x > 6.5f)
		{
			mUI_TITLE02_ENTER_SizeState = false;
		}

		if (mUI_TITLE02_ENTER_SizeState == true)
		{
			mUI_TITLE02_ENTER_scale.x += 0.2f * Time::DeltaTime();
			mUI_TITLE02_ENTER_scale.y += 0.2f * Time::DeltaTime();
			mUI_TITLE02_ENTER_scale.z += 0.2f * Time::DeltaTime();

			mUI_TITLE02_ENTER_tr->SetScale(mUI_TITLE02_ENTER_scale);
		}
		else//(mUI_TITLE02_ENTER_SizeState == false)
		{
			mUI_TITLE02_ENTER_scale.x -= 0.2f * Time::DeltaTime();
			mUI_TITLE02_ENTER_scale.y -= 0.2f * Time::DeltaTime();
			mUI_TITLE02_ENTER_scale.z -= 0.2f * Time::DeltaTime();

			mUI_TITLE02_ENTER_tr->SetScale(mUI_TITLE02_ENTER_scale);
		}

		Scene::Update();
	}

	void Title02Scene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Title02Scene::Render()
	{
		Scene::Render();
	}

	void Title02Scene::OnEnter()
	{

	}

	void Title02Scene::OnExit()
	{

	}
}
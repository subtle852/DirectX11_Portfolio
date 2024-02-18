#include "yaMainScene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaMesh.h"
#include "yaCameraScript.h"
#include "yaCamera.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaLight.h"

namespace ya
{
	MainScene::MainScene()
	{
	}
	MainScene::~MainScene()
	{
	}
	void MainScene::Initialize()
	{
		// BG
		{
			mBG_MAIN_01 = new GameObject();
			AddGameObject(eLayerType::BG, mBG_MAIN_01);
			MeshRenderer* mr = mBG_MAIN_01->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_BG_MAIN_01"));
			mBG_MAIN_01->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 50.0f));
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BG_MAIN_01", L"..\\Resources\\SCENE\\02_MAIN\\BG_MAIN_01.png");
			mBG_MAIN_01->GetComponent<Transform>()->SetScale((Vector3(texture.get()->GetImageRatioOfWidth(),
				texture.get()->GetImageRatioOfHeight(), 0.0f))
				* 13.0f);
			//player->AddComponent<CameraScript>();
		}

		// UI
		{
			mUI_MAIN_MENU = new GameObject();
			AddGameObject(eLayerType::BG, mUI_MAIN_MENU);
			MeshRenderer* mr = mUI_MAIN_MENU->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_UI_MAIN_MENU"));
			mUI_MAIN_MENU->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 48.0f));
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BG_TITLE01_01", L"..\\Resources\\SCENE\\01_TITLE\\BG_TITLE01_01.png");
			mUI_MAIN_MENU->GetComponent<Transform>()->SetScale((Vector3(texture.get()->GetImageRatioOfWidth(),
				texture.get()->GetImageRatioOfHeight(), 0.0f))
				* 13.0f);
		}

		{
			mUI_MAIN_MENU_BAR = new GameObject();
			AddGameObject(eLayerType::BG, mUI_MAIN_MENU_BAR);
			MeshRenderer* mr2 = mUI_MAIN_MENU_BAR->AddComponent<MeshRenderer>();
			mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr2->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_UI_MAIN_MENU_BAR"));
			mUI_MAIN_MENU_BAR->GetComponent<Transform>()->SetPosition(Vector3(0.01f, -0.12f, 49.0f));
			//mUI_SELECT_BAR->GetComponent<Transform>()->SetPosition(Vector3(0.01f, -0.29f, 47.0f));
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BG_TITLE01_01", L"..\\Resources\\SCENE\\01_TITLE\\BG_TITLE01_01.png");
			mUI_MAIN_MENU_BAR->GetComponent<Transform>()->SetScale((Vector3(texture.get()->GetImageRatioOfWidth(),
				texture.get()->GetImageRatioOfHeight(), 0.0f))
				* 13.0f);
		}
		
		{
			mUI_MAIN_CHAR = new GameObject();
			AddGameObject(eLayerType::BG, mUI_MAIN_CHAR);
			MeshRenderer* mr = mUI_MAIN_CHAR->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_UI_MAIN_CHAR"));
			mUI_MAIN_CHAR->GetComponent<Transform>()->SetPosition(Vector3(0.1f, 0.0f, 47.0f));
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"BG_TITLE01_01", L"..\\Resources\\SCENE\\01_TITLE\\BG_TITLE01_01.png");
			mUI_MAIN_CHAR->GetComponent<Transform>()->SetScale((Vector3(texture.get()->GetImageRatioOfWidth(),
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
		//camera->AddComponent<CameraScript>();
	}

	void MainScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(L"SelectScene");
		}
		if (Input::GetKeyDown(eKeyCode::ESC))
		{
			SceneManager::LoadScene(L"Title02Scene");
		}

		// UI 캐릭터 크기 조정
		if (mUI_MAIN_CHAR != nullptr)
		{
			Transform* mUI_MAIN_CHAR_tr = mUI_MAIN_CHAR->GetComponent<Transform>();
			Vector3 mUI_MAIN_CHAR_scale = mUI_MAIN_CHAR_tr->GetScale();

			if (mUI_MAIN_CHAR_scale.x <= 6.4f)
			{
				mUI_MAIN_CHAR_SizeState = true;
			}
			else if (mUI_MAIN_CHAR_scale.x > 6.7f)
			{
				mUI_MAIN_CHAR_SizeState = false;
			}

			if (mUI_MAIN_CHAR_SizeState == true)
			{
				mUI_MAIN_CHAR_scale.x += 0.4f * Time::DeltaTime();
				mUI_MAIN_CHAR_scale.y += 0.4f * Time::DeltaTime();
				mUI_MAIN_CHAR_scale.z += 0.4f * Time::DeltaTime();

				mUI_MAIN_CHAR_tr->SetScale(mUI_MAIN_CHAR_scale);
			}
			else//(mUI_CHAR_SizeState == false)
			{
				mUI_MAIN_CHAR_scale.x -= 0.4f * Time::DeltaTime();
				mUI_MAIN_CHAR_scale.y -= 0.4f * Time::DeltaTime();
				mUI_MAIN_CHAR_scale.z -= 0.4f * Time::DeltaTime();

				mUI_MAIN_CHAR_tr->SetScale(mUI_MAIN_CHAR_scale);
			}
		}

		// 메뉴 넘버 입력
		if (Input::GetKeyDown(eKeyCode::W) || Input::GetKeyDown(eKeyCode::UP))
		{
			if (mMenuNumber != static_cast<int>(MenuNumber::StoryMode))
				mMenuNumber--;
		}
		if (Input::GetKeyDown(eKeyCode::S) || Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mMenuNumber != static_cast<int>(MenuNumber::ExitGame))
				mMenuNumber++;
		}

		// 메뉴 넘버에 따른 메뉴 바 위치 수정
		if (mUI_MAIN_MENU_BAR != nullptr) 
		{
			Transform* mUI_MAIN_SELECT_BAR_tr = mUI_MAIN_MENU_BAR->GetComponent<Transform>();
			Vector3 mUI_MAIN_SELECT_BAR_pos = mUI_MAIN_SELECT_BAR_tr->GetPosition();

			switch (mMenuNumber)
			{
			case (int)(MenuNumber::StoryMode):
				mUI_MAIN_SELECT_BAR_pos.y = -0.12f;
				break;
			case (int)(MenuNumber::NetworkGame):
				mUI_MAIN_SELECT_BAR_pos.y = -0.29f - (0.17f * 0) - 0.01f;
				break;
			case (int)(MenuNumber::ExtraGameModex):
				mUI_MAIN_SELECT_BAR_pos.y = -0.29f - (0.17f * 1) - 0.03f;
				break;
			case (int)(MenuNumber::UbisoftConnect):
				mUI_MAIN_SELECT_BAR_pos.y = -0.29f - (0.17f * 2) - 0.04f;
				break;
			case (int)(MenuNumber::Achievements):
				mUI_MAIN_SELECT_BAR_pos.y = -0.29f - (0.17f * 3) - 0.06f;
				break;
			case (int)(MenuNumber::Leaderboards):
				mUI_MAIN_SELECT_BAR_pos.y = -0.29f - (0.17f * 4) - 0.08f;
				break;
			case (int)(MenuNumber::HelpNOptions):
				mUI_MAIN_SELECT_BAR_pos.y = -0.29f - (0.17f * 5) - 0.09f;
				break;
			case (int)(MenuNumber::ExitGame):
				mUI_MAIN_SELECT_BAR_pos.y = -0.29f - (0.17f * 6) - 0.1f;
				break;
			default:
				break;
			}
			mUI_MAIN_SELECT_BAR_tr->SetPosition(mUI_MAIN_SELECT_BAR_pos);
		}

		Scene::Update();
	}

	void MainScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void MainScene::Render()
	{
		Scene::Render();
	}

	void MainScene::OnEnter()
	{
		mMenuNumber = 0;
	}

	void MainScene::OnExit()
	{

	}
}
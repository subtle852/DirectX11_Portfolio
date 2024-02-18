#include "yaCameraScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaPlayScene.h"

namespace ya
{
	void CameraScript::Initialize()
	{
		
	}

	void CameraScript::Update()
	{
		if (mCameraPosSetting == 1)
		{
			MoveFree();
		}

		else
		{
			Vector3 targetPos = PlayScene::GetPlayerPosition();
			MoveFix(targetPos);
		}
	}

	void CameraScript::MoveFree()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();


		if (Input::GetKey(eKeyCode::NUM6))
		{
			pos.z += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::NUM4))
		{
			pos.z -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::NUM1))
		{
			pos.x -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::NUM3))
		{
			pos.x += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::NUM2))
		{
			pos.y -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::NUM5))
		{
			pos.y += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}
	void CameraScript::MoveFix(Vector3 targetPos)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x = targetPos.x;
		pos.y = targetPos.y;

		tr->SetPosition(pos);
	}
}

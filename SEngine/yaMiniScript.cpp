#include "yaMiniScript.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaInput.h"
#include "yaTime.h"

namespace ya
{
	MiniScript::MiniScript()
	{
	}
	MiniScript::~MiniScript()
	{
	}
	void MiniScript::Initialize()
	{
		//(Vector3(-2.25f, 1.65f, 40.f) 0,0 위치
		// 좌우간격 상하간격 0.8
	}
	void MiniScript::Update()
	{
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			Vector2 tempPos = mPosbyMatrix;
			tempPos.x -= 1;
			if (mRoute[(int)tempPos.y][(int)tempPos.x] != 0)
			{
				tempPos.x -= 1;
				mPosbyMatrix.x = tempPos.x;

				mPos.x -= 1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			Vector2 tempPos = mPosbyMatrix;
			tempPos.x += 1;
			if (mRoute[(int)tempPos.y][(int)tempPos.x] != 0)
			{
				tempPos.x += 1;
				mPosbyMatrix.x = tempPos.x;

				mPos.x += 1;
			}
		}
		if (Input::GetKeyDown(eKeyCode::UP))
		{
			Vector2 tempPos = mPosbyMatrix;
			tempPos.y -= 1;
			if (mRoute[(int)tempPos.y][(int)tempPos.x] != 0)
			{
				tempPos.y -= 1;
				mPosbyMatrix.y = tempPos.y;

				mPos.y -= 1;
			}
		}
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			Vector2 tempPos = mPosbyMatrix;
			tempPos.y += 1;
			if (mRoute[(int)tempPos.y][(int)tempPos.x] != 0)
			{
				tempPos.y += 1;
				mPosbyMatrix.y = tempPos.y;

				mPos.y += 1;
			}
		}

		Transform* tr = this->GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x = zeroPos.x + (0.8f * mPos.x);
		pos.y = zeroPos.y - (0.8f * mPos.y);
		tr->SetPosition(pos);
	}
	void MiniScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void MiniScript::OnCollisionStay(Collider2D* other)
	{
	}
	void MiniScript::OnCollisionExit(Collider2D* other)
	{
	}
}
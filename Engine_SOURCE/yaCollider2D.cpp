#include "yaCollider2D.h"
#include "yaGameObject.h"
#include "yaRenderer.h"

namespace ya
{
	UINT Collider2D::mColliderNumber = 0;

	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mTransform(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
	{
		mColliderNumber++;
		mColliderID = mColliderNumber;
	}

	Collider2D::~Collider2D()
	{

	}

	void Collider2D::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
	}

	void Collider2D::Update()
	{
		// Collider가 붙은 오브젝트의 eLayerType이 UI인 경우 같이 이동하도록 만드는 것에대하여

		// 충돌하지 않을 때, 충돌 대상의 OtherPosition 불가능한 값으로 초기화 
		if (this->GetState() == eColliderState::NotColliding)
		{
			mOtherPosition = Vector3(9999.0f, 9999.0f, 9999.0f);
		}
	}

	void Collider2D::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 scale = tr->GetScale();
		scale.x *= mSize.x;
		scale.y *= mSize.y;

		Vector3 pos = tr->GetPosition();
		pos.x += mCenter.x;
		pos.y += mCenter.y;

		mPosition = pos;

		graphics::DebugMesh mesh = {};
		mesh.position = pos;
		mesh.scale = scale;
		mesh.rotation = tr->GetRotation();
		mesh.type = eColliderType::Rect;
		mesh.activation = mActivation;
		mesh.state = mState;

		renderer::PushDebugMeshAttribute(mesh);
	}

	void Collider2D::Render()
	{

	}

	void Collider2D::OnCollisionEnter(Collider2D* other)
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionEnter(other);
		}
	}

	void Collider2D::OnCollisionStay(Collider2D* other)
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionStay(other);
		}
	}

	void Collider2D::OnCollisionExit(Collider2D* other)
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionExit(other);
		}
	}
}
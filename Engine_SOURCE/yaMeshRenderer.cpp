#include "yaMeshRenderer.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaRenderer.h"
#include "yaAnimator.h"
#include "yaCollider2D.h"

namespace ya
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
	{
	}
	MeshRenderer::~MeshRenderer()
	{
	}
	void MeshRenderer::Initialize()
	{
	}
	void MeshRenderer::Update()
	{
	}
	void MeshRenderer::LateUpdate()
	{
	}
	void MeshRenderer::Render()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->BindConstantBuffer();

		mMesh->BindBuffer();
		mMaterial->Binds();

		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (animator)
			animator->Binds();

		mMesh->Render();

		mMaterial->Clear();
	}
}

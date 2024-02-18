#pragma once
#include "SEngine.h"
#include "yaGraphicDevice_Dx11.h"
#include "yaMesh.h"
#include "yaShader.h"
#include "yaConstantBuffer.h"
#include "yaCamera.h"
#include "yaLight.h"

using namespace ya::math;
using namespace ya::graphics;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};

	CBUFFER(AnimatorCB, CBSLOT_ANIMATION2D)
	{
		Vector2 spriteLeftTop;
		Vector2 spriteSize;
		Vector2 spriteOffset;
		Vector2 atlasSize;
		UINT animationType;
	};

	CBUFFER(ColliderCB, CBSLOT_COLLIDER)
	{
		UINT colliderActivation;
		UINT colliderState;
	};

	extern ya::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<ya::Light*> lights;
	extern ya::Camera* mainCamera;
	extern std::vector<ya::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;

	void Initialize();
	void BindLights();
	void Render();
	void Release();

	void PushDebugMeshAttribute(DebugMesh mesh);
}
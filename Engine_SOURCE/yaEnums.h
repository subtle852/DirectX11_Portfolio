#pragma once


namespace ya::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Rigidbody,
		Mesh,
		Collider2D,
		Particle,
		MeshRenderer,
		Animator,
		Script,
		Light,
		Camera,
		End,
	};

	enum class eLayerType
	{
		Grid,
		BG,
		Camera,
		Enemy,
		Player,
		Light,
		UI,
		End = 16,
	};

	enum class eCameraSetting
	{
		Static,
		Tracking,
		SmoothingTransition,
		ShakeVertical,
		ShakeHorizontal,
		ShakeZoom,
		ShakeCircle,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
		End,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};

	enum class eColliderActivation
	{
		InActive,
		Active,
		End,
	};

	enum class eColliderState
	{
		NotColliding,
		IsColliding,
		End,
	};

	enum class eAnimationType : UINT
	{
		None,
		Front,
		Back,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};

	enum class eDirection
	{
		L,
		R,
	};

	enum class ePlayerState
	{
		L_Idle,
		R_Idle,

		L_Walk,
		R_Walk,

		L_Run,
		R_Run,

		L_Jump,
		R_Jump,

		L_DJump,
		R_DJump,

		L_Guard,
		R_Guard,

		L_Evade,
		R_Evade,

		L_NormalAttack1,
		R_NormalAttack1,
		L_NormalAttack2,
		R_NormalAttack2,
		L_NormalAttack3,
		R_NormalAttack3,

		L_Kick,
		R_Kick,
		L_RoundKick,
		R_RoundKick,
		L_BehindKick,
		R_BehindKick,

		L_WeaponNormalAttack,
		R_WeaponNormalAttack,
		L_WeaponDownAttack,
		R_WeaponDownAttack,
		L_WeaponSideAttack,
		R_WeaponSideAttack,
		L_WeaponStabAttack,
		R_WeaponStabAttack,

		L_JumpDownAttack,
		R_JumpDownAttack,
		L_JumpSlideAttack,
		R_JumpSlideAttack,
		L_RunJumpAttack,
		R_RunJumpAttack,
		//L_RunJumpDownAttack,
		//R_RunJumpDownAttack,

		L_RunWeaponAttack,
		R_RunWeaponAttack,
		L_RunSlideAttack,
		R_RunSlideAttack,

		L_FireBall,
		R_FireBall,
		L_Super,
		R_Super,

		L_Stun,
		R_Stun,
		L_BackStun,
		R_BackStun,
		L_KnockDown,
		R_KnockDown,

		L_Downed,
		R_Downed,

		L_GetUp,
		R_GetUp,

		L_Revived,
		R_Revived,
	};
}
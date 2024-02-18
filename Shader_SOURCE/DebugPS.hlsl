#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};


float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;
    
    //if (colliderState == 0)// NotColiding
    //{
    //    color = float4(1.0f, 1.0f, 1.0f, 1.0f); // 흰색
    //}
    //else if (colliderState == 1)// IsColliding
    //{
    //    color = float4(0.0f, 1.0f, 0.0f, 1.0f); // 초록색
    //}
    ////else if (colliderState == 2)// NoneActive
    ////{
    ////    color = float4(1.0f, 1.0f, 1.0f, 1.0f); // 흰색
    ////}
    
    // 총 3가지 상황
    // Activation 1(켜진거) && Colliding 0(충돌 X)
    if (colliderActivation == 1 && colliderState == 0)
    {
        color = float4(0.0f, 1.0f, 0.0f, 1.0f);// 초록색
    }
    
    // Activation 1(켜진거) && Colliding 1(충돌 O)
    else if (colliderActivation == 1 && colliderState == 1)
    {
        color = float4(1.0f, 0.0f, 0.0f, 1.0f); // 빨간색
    }
    
    // Activation 0(꺼진거) && Colliding 0(충돌 X)
    else if (colliderActivation == 0)
    {
        color = float4(1.0f, 1.0f, 1.0f, 1.0f);// 흰색
    }
    
    else// 오류
    {
        color = float4(0.0f, 0.0f, 1.0f, 1.0f); // 파란색
    }
        return color;
}
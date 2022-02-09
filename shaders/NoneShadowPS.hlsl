#include "Basic.hlsli"
Texture2D<float4> tex : register(t0); // 0 番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0 番スロットに設定されたサンプラー

float4 main(GSOutput input) :SV_TARGET{

	return float4(color.r,color.g,color.b,1);
}

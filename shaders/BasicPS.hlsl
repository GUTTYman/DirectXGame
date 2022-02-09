#include "Basic.hlsli"
Texture2D<float4> tex : register(t0); // 0 番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0 番スロットに設定されたサンプラー

float4 PSmain(GSOutput input) :SV_TARGET{

	float4 texcolor = tex.Sample(smp, input.uv) * input.color * color;	
	return texcolor;
}

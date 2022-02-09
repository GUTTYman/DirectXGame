#include "PostEffectTest.hlsli"
Texture2D<float4> tex0 : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);  // 1番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
	float d = distance(drawUV, pickUV);
	return exp(-(d * d)) / (2 * sigma * sigma);
}


struct PSOutput
{
	float4 target0 : SV_TARGET0;
	float4 target1 : SV_TARGET1;
};

PSOutput main(VSOutput input)
{
	PSOutput output;
	//湾曲
	float2 resultUv = input.uv;
	resultUv -= float2(0.5, 0.5);
	//湾曲の強さの計算
	float distPower = pow(length(resultUv), dist);
	resultUv *= float2(distPower,distPower);
	resultUv += float2(0.5 , 0.5);

	float4 color = tex0.Sample(smp, resultUv);
	//RGBずらし
	resultUv.x += rgbShiftWeight;

	color.r = tex0.Sample(smp, resultUv).r;

	color = float4(color.rgb * fade, 1);
	output.target0 = color;
	output.target1 = float4(1 - (color).rgb, 1);

	return output;

}
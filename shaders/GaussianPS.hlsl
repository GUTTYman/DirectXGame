#include "Gaussian.hlsli"
Texture2D<float4> tex0 : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);  // 1番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー


float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
	float d = distance(drawUV, pickUV);
	return exp(-(d * d)) / (2 * sigma * sigma);
}

PSOutput main(VSOutput input)
{
	PSOutput output;

	float shiftWidth = shift;
	float4 color = tex0.Sample(smp, input.uv);
	if (color.r < 0.8 && color.g < 0.2)
	{
		color = float4(0, 0, 0, 0);
		color += tex0.Sample(smp, input.uv + float2(-shiftWidth, -shiftWidth));
		color += tex0.Sample(smp, input.uv + float2(0, -shiftWidth));
		color += tex0.Sample(smp, input.uv + float2(shiftWidth, -shiftWidth));
		color += tex0.Sample(smp, input.uv + float2(-shiftWidth, 0));
		color += tex0.Sample(smp, input.uv + float2(0, 0));
		color += tex0.Sample(smp, input.uv + float2(shiftWidth, 0));
		color += tex0.Sample(smp, input.uv + float2(-shiftWidth, shiftWidth));
		color += tex0.Sample(smp, input.uv + float2(0, shiftWidth));
		color += tex0.Sample(smp, input.uv + float2(shiftWidth, shiftWidth));

		color.rgb = color.rgb / 9;
	}
	//float4 color = float4(0, 0, 0, 1);// tex0.Sample(smp, input.uv);
	//	
	//float totalWeight = 0, sigma = shift, step = 0.001;

	//if (color.r < 0.8 && color.g < 0.2)
	//{
	//	for (float py = -sigma * 2; py <= sigma * 2; py += step)
	//	{
	//		for (float px = -sigma * 2; px <= sigma * 2; px += step)
	//		{
	//			float2 pickUV = input.uv + float2(px, py);
	//			float w = Gaussian(input.uv, pickUV, sigma);
	//			color += tex0.Sample(smp, pickUV) * w;
	//			totalWeight += w;
	//		}
	//	}

	//	color.rgb = color.rgb / totalWeight;
	//}
	output.target0 = color;
	output.target1 = float4(0,0,0,0);

	return output;

}
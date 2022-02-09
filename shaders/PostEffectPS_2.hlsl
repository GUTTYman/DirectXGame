#include "PostEffectTest.hlsli"

float4 main(PSOutput input){

	/*float4 col = tex0.Sample(smp, input.uv);
	float4 color = float4(0, 0, 0, 1);

	float grayScale = color.r * 0.299 + color.g * 0.587 + color.b * 0.114;
	float extract = smoothstep(0.6, 0.9, grayScale);
	float4 pick = color * extract;

	float totalWeight = 0, sigma = 0.005, step = 0.001;

	for (float py = -sigma * 2; py <= sigma * 2; py += step)
	{
		for (float px = -sigma * 2; px <= sigma * 2; px += step)
		{
			float2 pickUV = input.uv + float2(px, py);
			float w = Gaussian(input.uv, pickUV, sigma);
			color += tex0.Sample(smp, pickUV) * w;
			totalWeight += w;
		}
	}

	color.rgb = color.rgb / totalWeight;*/

}
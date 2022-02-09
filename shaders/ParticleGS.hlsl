#include"Particle.hlsli"

static const uint vnum = 78;

float3 GetRandomVector(float x)
{
	float3 returnData = float3(0, 0, 0);
	returnData.x = frac(sin(dot(float2(0.016f * x, 0), float2(12.9898, 78.233))) * 43758.5453);
	returnData.y = frac(sin(dot(float2(0, 0.016f * x), float2(12.9898, 78.233))) * 43758.5453);
	returnData.z = frac(sin(dot(float2(0.016f * x, 0.016f * x), float2(12.9898, 78.233))) * 43758.5453);
	return returnData;
}

float3 GetRandomVector(float3 vec)
{
	float3 result = float3(0, 0, 0);
	result.x = frac(sin(dot(vec.zy + vec.x, float2(12.9898, 78.233))) * 43758.5453);
	result.y = frac(sin(dot(vec.yz + vec.x, float2(12.9898, 78.233))) * 43758.5453);
	result.z = frac(sin(dot(vec.xy + vec.z, float2(12.9898, 78.233))) * 43758.5453);
	return result;
}

float3 GetRandomVector(float3 vec, float3 minValue, float3 maxValue)
{
	float3 result = float3(0, 0, 0);
	result = GetRandomVector(vec);
	result = (result / 1.0f * maxValue) - (-minValue) / 2.0f;
	return result;
}

[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION,
	inout PointStream< GSOutput > output
)
{		GSOutput element;
		element.normal = input[0].normal;
		element.uv = input[0].uv;
		element.color = input[0].color;

		float min = -10.0;
		float max = 10.0;
		//重力
		float gravity = time * 0.00008f;
		for (int i = 0; i < vnum; i++)
		{
			float4 pos = input[0].svpos;

			//ポジションに加算
			for (int j = 1; j <= input[0].instNo; j++)
			{
				//パーティクルを飛ばす方向
				float3 random = GetRandomVector(GetRandomVector(j + i), float3(min, 0, min), float3(max, max/2.0 , max)) * 0.005;
				random.y -= gravity;
				pos += float4(random.x, random.y, 0, 0) * time;
			}
			//ビュープロジェクションに変換
			element.svpos = mul(mul(viewproj, world), pos);//座標に行列を乗算
			output.Append(element);
		}
}
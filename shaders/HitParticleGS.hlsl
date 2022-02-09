#include"Particle.hlsli"

static const uint vnum = 3;

float rand(float2 co)
{
	return frac(sin(dot(co.xy, float2(12.9898, 78.233))) * 43758.5453);
}

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

[maxvertexcount(3)]
void main(
	triangle VSOutput input[3] : SV_POSITION,
	inout TriangleStream< GSOutput > output
)
{		GSOutput element;
		element.normal = input[0].normal;
		element.uv = input[0].uv;
		element.color = input[0].color;
		//ランダムの範囲
		float min = -10.0;
		float max = 10.0;
		//重力
		float gravity = time * 0.2;
		float s = time * 0.05;
		for (int i = 0; i < vnum; i++)
		{
			float4 pos = input[i].svpos;
			//パーティクルを飛ばす方向
			for (int j = 1; j <= input[i].instNo; j++)
			{
				float3 random = GetRandomVector(GetRandomVector(j), float3(min, min, min), float3(max, max , max));

				random.y -= gravity;
				random.z += s;
				//スケールをランダム
				float4x4 scale =
				{
					random.z * 0.4f,0,0,0,
					0,random.z * 0.4f,0,0,
					0,0,random.z * 0.4f,0,
					0,0,0,1,
				};
				//飛ばす方向をランダム
				float4x4 velocity =
				{
					1,0,0,random.x * time * 0.05,
					0,1,0,random.y * time * 0.05,
					0,0,1,0,
					0,0,0,1,
				};

				float4x4 sum = mul(velocity,scale);
				element.svpos = mul(mul(viewproj, world), mul(sum,pos));
			}
			output.Append(element);
		}
}
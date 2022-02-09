#include "Particle.hlsli"
VSOutput VSmain(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD, uint instNo : SV_InstanceID)
{
	float4 wnormal = normalize(mul(world, float4(normal, 0)));
	float4 wpos = mul(world, pos);
	//拡散反射光
	float3 diffuse = dot(lightv, wnormal.xyz);
	//光沢度
	const float shininess = 4.0f;
	//頂点から視点への方向ベクトル
	float3 eyedir = normalize(cameraPos - wpos.xyz);
	//反射光ベクトル
	float3 reflect = normalize(-lightv + 2 * dot(lightv, wnormal.xyz) * wnormal.xyz);//(lightdir + 2 * dot(-lightdir, normal)*normal);
	//鏡面反射光
	float3 specular = pow(saturate(dot(reflect, eyedir)), shininess);

	VSOutput output; // ピクセルシェーダーに渡す値
	output.svpos = pos;
	output.normal = normal;
	output.color.rgb = (diffuse + specular) * lightcolor;
	output.color.a = 1;
	output.uv = uv;
	output.instNo = instNo;
	return output;
}
cbuffer cbuff0 : register(b0)
{
	float4 color; //色(RGBA)
	matrix viewproj;
	matrix world;
	float3 cameraPos;
	int time;
	int maxCount;
};
cbuffer cbuff1 : register(b1)
{
	float3 lightv;
	float3 lightcolor;
};

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos : SV_POSITION; //システム用頂点座標
	float3 normal :NORMAL;//法線ベクトル
	float4 color:COLOR;//色
	float2 uv :TEXCOORD; //uv
	uint instNo : SV_InstanceID;
};

struct GSOutput
{
	float4 svpos:SV_POSITION;	//システム用頂点座標
	float3 normal :NORMAL;		//法線ベクトル
	float4 color:COLOR;//色
	float2 uv :TEXCOORD;		//uv値
};
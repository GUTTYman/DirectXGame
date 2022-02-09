cbuffer cbuff0 : register(b0)
{
	float4 color; //色(RGBA)
	float3 normalLength;
	matrix viewproj;
	matrix world;
	float3 cameraPos;
	float3 randomVertex;
};
cbuffer cbuff1 : register(b1)
{
	float3 lightv;
	float3 lightcolor;
};

// 頂点シェーダーからハルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos : SV_POSITION; //システム用頂点座標
	float3 normal :NORMAL;//法線ベクトル
	float4 color:COLOR;//色
	float2 uv :TEXCOORD; //uv
};

struct GSOutput
{
	float4 svpos:SV_POSITION;	//システム用頂点座標
	float3 normal :NORMAL;		//法線ベクトル
	float4 color:COLOR;//色
	float2 uv :TEXCOORD;		//uv値
};

#define NUM_CONTROL_POINTS 3

struct HS_CONTROL_POINT_OUTPUT
{
	float4 svpos : SV_POSITION; //システム用頂点座標
	float3 normal :NORMAL;//法線ベクトル
	float4 color:COLOR;//色
	float2 uv :TEXCOORD; //uv
};

struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[3]			: SV_TessFactor;
	float InsideTessFactor : SV_InsideTessFactor;
};

struct DS_OUTPUT
{
	float4 svpos : SV_POSITION; //システム用頂点座標
	float3 normal :NORMAL;//法線ベクトル
	float4 color:COLOR;//色
	float2 uv :TEXCOORD; //uv
};

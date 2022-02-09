cbuffer cbuff0 : register(b0)
{
	float4 color; //�F(RGBA)
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

// ���_�V�F�[�_�[����n���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
	float4 svpos : SV_POSITION; //�V�X�e���p���_���W
	float3 normal :NORMAL;//�@���x�N�g��
	float4 color:COLOR;//�F
	float2 uv :TEXCOORD; //uv
};

struct GSOutput
{
	float4 svpos:SV_POSITION;	//�V�X�e���p���_���W
	float3 normal :NORMAL;		//�@���x�N�g��
	float4 color:COLOR;//�F
	float2 uv :TEXCOORD;		//uv�l
};

#define NUM_CONTROL_POINTS 3

struct HS_CONTROL_POINT_OUTPUT
{
	float4 svpos : SV_POSITION; //�V�X�e���p���_���W
	float3 normal :NORMAL;//�@���x�N�g��
	float4 color:COLOR;//�F
	float2 uv :TEXCOORD; //uv
};

struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[3]			: SV_TessFactor;
	float InsideTessFactor : SV_InsideTessFactor;
};

struct DS_OUTPUT
{
	float4 svpos : SV_POSITION; //�V�X�e���p���_���W
	float3 normal :NORMAL;//�@���x�N�g��
	float4 color:COLOR;//�F
	float2 uv :TEXCOORD; //uv
};

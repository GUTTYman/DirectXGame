cbuffer cbuff0 : register(b0)
{
	float4 color; //�F(RGBA)
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

// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
	float4 svpos : SV_POSITION; //�V�X�e���p���_���W
	float3 normal :NORMAL;//�@���x�N�g��
	float4 color:COLOR;//�F
	float2 uv :TEXCOORD; //uv
	uint instNo : SV_InstanceID;
};

struct GSOutput
{
	float4 svpos:SV_POSITION;	//�V�X�e���p���_���W
	float3 normal :NORMAL;		//�@���x�N�g��
	float4 color:COLOR;//�F
	float2 uv :TEXCOORD;		//uv�l
};
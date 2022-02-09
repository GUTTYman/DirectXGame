#include"Basic.hlsli"
float rand(float2 co)
{
	return frac(sin(dot(co.xy, float2(12.9898, 78.233))) * 43758.5453);
}

//�w�肵���x�N�g�������ɉ�]������
float3 rotate(float3 p, float angle, float3 axis)
{
	float3 a = normalize(axis);
	float s = sin(angle);
	float c = cos(angle);
	float r = 1.0 - c;
	float3x3 m = float3x3(
		a.x * a.x * r + c, a.y * a.x * r + a.z * s, a.z * a.x * r - a.y * s,
		a.x * a.y * r - a.z * s, a.y * a.y * r + c, a.z * a.y * r + a.x * s,
		a.x * a.z * r + a.y * s, a.y * a.z * r - a.x * s, a.z * a.z * r + c
		);

	return mul(m, p);
}

[maxvertexcount(3)]
void main(
	triangle DS_OUTPUT input[3] : SV_POSITION,
	inout TriangleStream< GSOutput > output
)
{
	float4 center =(input[0].svpos + input[1].svpos + input[2].svpos) / 3;

	for (uint i = 0; i < 3; i++)
	{
		GSOutput element;
		//�t�F�[�X�����̏�ŉ�]������

		element.normal = input[i].normal;
		element.uv = input[i].uv;
		//element.color = float4(input[i].normal,1);
		element.color = input[i].color;

		//�����_���Ȓl����
		float random = rand(input[i].svpos.xy);
		//���_�������_���ŐU��������
		float4 rndVert = float4(input[i].svpos.x + input[i].svpos.x * sin(randomVertex.x * random) * 0.25,
			input[i].svpos.y + input[i].svpos.y * sin(randomVertex.y * random) * 0.25,
			input[i].svpos.z + input[i].svpos.z * sin(randomVertex.z * random) * 0.25, input[i].svpos.w);
		//�t�F�[�X�̉�]
		float4 rotation = center + float4(rotate(input[i].svpos.xyz - center.xyz, normalLength.x * 10 / 57.3248, input[i].normal), 0);
		//�t�F�[�X��@�������ɔ�΂�;
		float4 face = float4(input[i].normal.x * normalLength.x, input[i].normal.y * normalLength.y, input[i].normal.z * normalLength.z, 0);
		
		//�R�̌v�Z�𑫂����킹��
		float4 svpos = face + rndVert;
		//���W�ɍs�����Z
		element.svpos = mul(mul(viewproj, world), svpos);

		output.Append(element);
	}
}
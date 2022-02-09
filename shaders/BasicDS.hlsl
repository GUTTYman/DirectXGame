#include "Basic.hlsli"

[domain("tri")]

DS_OUTPUT main(
	HS_CONSTANT_DATA_OUTPUT input,
	float3 domain : SV_DomainLocation,
	const OutputPatch<HS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> patch)
{
	DS_OUTPUT output;

    //�V�����o�͂���e���_�̍��W���v�Z
    float3 f3Position =
        domain.x * patch[0].svpos +
        domain.y * patch[1].svpos +
        domain.z * patch[2].svpos;

    float4 f3Color =
        domain.x * patch[0].color +
        domain.y * patch[1].color +
        domain.z * patch[2].color;

    //�V�����o�͂���e���_�̖@�����v�Z
    float3 f3Normal = normalize(
        domain.x * patch[0].normal +
        domain.y * patch[1].normal +
        domain.z * patch[2].normal);

    //�V�����o�͂���e���_��UV���W���v�Z
    output.uv =
        domain.x * patch[0].uv +
        domain.y * patch[1].uv +
        domain.z * patch[2].uv;
    
    output.svpos = mul(float4(f3Position, 1), world);

    return output;
}

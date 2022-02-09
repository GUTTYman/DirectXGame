#include "Basic.hlsli"
float4 main(GSOutput input) :SV_TARGET{

	float4 texcolor = float4(input.normal,input.color.a);
	return texcolor;
}

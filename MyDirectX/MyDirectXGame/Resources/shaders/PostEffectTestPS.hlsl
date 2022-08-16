#include "PostEffectTest.hlsli"

Texture2D<float4> tex0 : register(t0);
Texture2D<float4> tex1 : register(t1);
SamplerState smp : register(s0);

float4 main(VSOutput input) :SV_TARGET
{
	float4 texcolor0 = tex0.Sample(smp,input.uv);
	float4 texcolor1 = tex1.Sample(smp, input.uv);
	float4 color = texcolor0;
	float l = (color.r + color.g + color.b) / 3;
	if(flag)
	{
		if (input.uv.x < 0.044f)
		{
			return float4(l, l, l, 1);
		}
		else if (0.235f < input.uv.x)
		{
			return float4(l, l, l, 1);
		}

		if (input.uv.y < 0.498f)
		{
			return float4(l, l, l, 1);
		}
		else if (0.925f < input.uv.y)
		{
			return float4(l, l, l, 1);
		}
	}

	return float4(color.rgb,1);
}
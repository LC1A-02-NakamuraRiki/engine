#include "PostEffectTest.hlsli"

Texture2D<float4> tex0 : register(t0);
Texture2D<float4> tex1 : register(t1);
SamplerState smp : register(s0);

float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
	float d = distance(drawUV, pickUV);
	return exp(-(d * d) / (2 * sigma * sigma));
}

float4 main(VSOutput input) :SV_TARGET
{
	float4 texcolor0 = float4(0,0,0,0);
	float4 color;
	float totalWeight = 0, sigma = 0.005f, stepWidth = 0.001f;
	for (float py = -sigma * 2; py <= sigma * 2; py += stepWidth)
	{
		for (float px = -sigma * 2; px <= sigma * 2; px += stepWidth)
		{
			float2 pickUV = input.uv + float2(px, py);
			float weight = Gaussian(input.uv, pickUV, sigma);
			color += tex0.Sample(smp, pickUV) * weight;
			totalWeight += weight;
		}
	}
	color.rgb = color.rgb / totalWeight;

	float4 bloom = float4(0,0,0,0);
	float rgb = 0.6f;
	float gray = color.r * 0.299 + color.g * 0.587 + color.b * 0.114;
	float l = (color.r + color.g + color.b) / 3;

	float brightNess = 0.27 * color.r + 0.67 * color.g + 0.06 * color.b;
	float brightNess1 = exp((1 / 2073600) * (log(0.01f + brightNess)));
	float brightNess2 = 1.0f * brightNess / brightNess1;
	float brightNess3 = (brightNess2 * (1 + brightNess2 / 4.0f)) / (1 + brightNess2);
	float u = 0.01f;
	float v = 0.01f;
	if (gray < 0.85f)
	{
		color = tex0.Sample(smp, input.uv);
	}

	if (flag)
	{
		if (input.uv.x < 0.044f)
		{
			return float4(l, l, l, color.a);
		}
		else if (0.235f < input.uv.x)
		{
			return float4(l, l, l, color.a);
		}

		if (input.uv.y < 0.498f)
		{
			return float4(l, l, l, color.a);
		}
		else if (0.925f < input.uv.y)
		{
			return float4(l, l, l, color.a);
		}
	}
	return float4(color.rgb * brightNess3,color.a);
}
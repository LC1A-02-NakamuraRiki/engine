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
	//テクスチャの色
	float4 color = tex0.Sample(smp, input.uv);
	//輝度算出
	float whiteValue = color.r * 0.299f + color.g * 0.587f + color.b * 0.114f;

	//ブルーム
	float4 color2 = float4(0,0,0,0);
	float totalWeight = 0, sigma = 0.012f, stepWidth = 0.006f;
	for (float py = -sigma * 2; py <= sigma * 2; py += stepWidth)
	{
		for (float px = -sigma * 2; px <= sigma * 2; px += stepWidth)
		{
			float2 pickUV = input.uv + float2(px, py);
			float weight = Gaussian(input.uv, pickUV, sigma);
			color2 += tex1.Sample(smp, pickUV) * weight;
			totalWeight += weight;
		}
	}
	color2 = color2 / totalWeight;
	color.rgb = color.rgb + color2.rgb;
	
	//トーンマップ
	float brightNess = 0.27 * color.r + 0.67 * color.g + 0.06 * color.b;
	float brightNess1 = exp((1 / 2073600) * (log(0.01f + brightNess)));
	float brightNess2 = 1.5f * brightNess / brightNess1;
	float brightNess3 = (brightNess2 * (1 + brightNess2 / 4.0f)) / (1 + brightNess2);
	
	//ビネット
	float distanceX = 0.5f - input.uv.x;
	float distanceY = 0.5f - input.uv.y;
	float distanceAXY = distanceX * distanceX + distanceY * distanceY;
	float distanceXY = sqrt(distanceAXY);
	float blackColor = 0.1f;
	float value = distanceXY * 2;
	float4 vinetColor = float4(blackColor * value, blackColor * value, blackColor * value, 0);
	color = float4((color.rgb * brightNess3) - vinetColor, color.a);

	//グレイスケール
	float l = (color.r + color.g + color.b) / 3;
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
	return color;
}
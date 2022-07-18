#include "OBJ2.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
float4 shadecolor;
float3 basicColor = colors.xyz;
float3 t = float3(0.2f,0.2f,0.2f);
float3 eyedir = normalize(cameraPos.xyz - input.worldpos.xyz);
float3 intensity = saturate(dot(normalize(input.normal),normalize(lightv + eyedir)));

float3 lightColor = colors.xyz;
float3 darkColor = colors.xyz * float3(0.5f,0.5f,0.5f);
float3 a = float3(0.2f, 0.2f, 0.2f);
if (intensity.x < t.x)
{
	a.x = 0;
}
else if (intensity.x > t.x)
{
	a.x = 1;
}
if (intensity.y < t.y)
{
	a.y = 0;
}
else if (intensity.y > t.y)
{
	a.y = 1;
}
if (intensity.z < t.z)
{
	a.z = 0;
}
else if (intensity.z > t.z)
{
	a.z = 1;
}
shadecolor.rgb = (a * lightColor) + ((1- a) * darkColor);
shadecolor.a = m_alpha;
return shadecolor;
}
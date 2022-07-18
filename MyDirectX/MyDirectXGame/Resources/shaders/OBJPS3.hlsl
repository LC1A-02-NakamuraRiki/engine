#include "OBJ3.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
float4 shadecolor;
float4 phongcolor;
float3 t = float3(0.2f, 0.2f, 0.2f);
float3 eyedir = normalize(cameraPos.xyz - input.worldpos.xyz);
float3 intensity = saturate(dot(normalize(input.normal),normalize(lightv + eyedir)));
float3 reflect = pow(intensity,50);
float3 ambient = m_ambient;
float3 diffuse = intensity * m_diffuse;
float3 specular = reflect * float3(1,1,1);
float3 lightColor = colors.xyz;
float3 darkColor = colors.xyz * float3(0.5f, 0.5f, 0.5f);
float3 value = float3(0.2f, 0.2f, 0.2f);
if (intensity.x < t.x)
{
	value.x = 0;
}
else if (intensity.x > t.x)
{
	value.x = 1;
}
if (intensity.y < t.y)
{
	value.y = 0;
}
else if (intensity.y > t.y)
{
	value.y = 1;
}
if (intensity.z < t.z)
{
	value.z = 0;
}
else if (intensity.z > t.z)
{
	value.z = 1;
}
phongcolor.rgb = (ambient + diffuse + specular) * lightcolor;
phongcolor.a = m_alpha;
shadecolor.rgb = colors.xyz;
shadecolor.a = 1;

shadecolor.rgb = (value *specular) + ((value * diffuse) * lightColor) + ((1 - (value * diffuse)) * darkColor+ambient);
shadecolor.a = m_alpha;
return shadecolor;
}
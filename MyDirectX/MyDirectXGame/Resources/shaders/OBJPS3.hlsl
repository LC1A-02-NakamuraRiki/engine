#include "OBJ3.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
float2 scroll = time.xy;
float4 texcolor = tex.Sample(smp, input.uv + scroll);
float4 shadecolor;
float4 phongcolor;
float3 eyedir = normalize(cameraPos.xyz - input.worldpos.xyz);
float3 intensity = saturate(dot(normalize(input.normal),normalize(lightv + eyedir)));
float3 reflect = pow(intensity,50);
float3 ambient = m_ambient;
float3 diffuse = intensity * m_diffuse;
float3 specular = reflect * m_specular;

phongcolor.rgb = (ambient + diffuse + specular) * lightcolor;
phongcolor.a = m_alpha;
shadecolor.rgb = colors.xyz;
shadecolor.a = 1;
return texcolor * phongcolor;
}
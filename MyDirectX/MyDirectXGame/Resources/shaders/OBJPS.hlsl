#include "OBJ.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{		
	// テクスチャマッピング
	float4 texcolor = tex.Sample(smp, input.uv);

	// 光沢度
	const float shininess = 5.0f;
	// 頂点から視点への方向ベクトル
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);

	// 環境反射光
	float3 ambient = m_ambient;
	// シェーディングによる色
	float4 shadecolor = float4(ambientColor * ambient, m_alpha);
	for (int i = 0; i < DIRLIGHT_NUM; i++) {
		if (dirLights[i].active) {
			// ライトに向かうベクトルと法線の内積
			float3 dotlightnormal = dot(dirLights[i].lightv, input.normal);
			// 反射光ベクトル
			float3 reflect = normalize(-dirLights[i].lightv + 2 * dotlightnormal * input.normal);
			// 拡散反射光
			float3 diffuse = dotlightnormal * m_diffuse;
			// 鏡面反射光
			float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * float3(1.0f, 1.0f, 1.0f);

			float ax;
			float ay;
			float az;
			float axyz;
			float xyzDistanse;
			float scalr;
			
			float bx = shadowPos.x - input.worldpos.x;
			float by = -0 - input.worldpos.y;
			float bz = shadowPos.z - input.worldpos.z;
			float bxyz = bx * bx + by * by + bz * bz;
			float bxyzDistanse = sqrt(bxyz);
			float bscalr = 1.0 - (bxyzDistanse / 1.6);
			float3 darkColor = float3(0.7, 0.7, 0.7);
			// 全て加算する
			if (bscalr >= 0) {
				shadecolor.rgb -= ((diffuse + specular) * dirLights[i].lightcolor) * (darkColor * bscalr);
			}
			
			     if (lightScale0 == 1)
					{
						ax = 68 + (-24 * 0) - input.worldpos.x;
						ay = 4 - input.worldpos.y;
						az = -76 + (24 * 0) - input.worldpos.z;
						axyz = ax * ax + ay * ay + az * az;
						xyzDistanse = sqrt(axyz);
						scalr = 1.0 - (xyzDistanse / 7);
						// 全て加算する
						if (scalr >= 0) {
							shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
						}
				}
			     if (lightScale1 == 1)
				{
					ax = 68 + (-24 * 0) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 1) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
			     if (lightScale2 == 1)
				{
					ax = 68 + (-24 * 0) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 2) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
			     if (lightScale3 == 1)
				{
					ax = 68 + (-24 * 0) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 3) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
			     if (lightScale4 == 1)
				{
					ax = 68 + (-24 * 0) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 4) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
			     if (lightScale5 == 1)
				{
					ax = 68 + (-24 * 0) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 5) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
			     if (lightScale6 == 1)
				{
					ax = 68 + (-24 * 0) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 6) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
			     if (lightScale7 == 1)
				{
					ax = 68 + (-24 * 1) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 0) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
			     if (lightScale8 == 1)
				{
					ax = 68 + (-24 * 1) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 1) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
			     if (lightScale9 == 1)
				{
					ax = 68 + (-24 * 1) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 2) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
			    if (lightScale10 ==1)
				{
					ax = 68 + (-24 * 1) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 3) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
			    if (lightScale11 ==1)
				{
					ax = 68 + (-24 * 1) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 4) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
			    if (lightScale12 ==1)
				{
					ax = 68 + (-24 * 1) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 5) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
			    if (lightScale13 ==1)
				{
					ax = 68 + (-24 * 1) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 6) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale14 == 1)
				{
					ax = 68 + (-24 * 2) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 0) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale15 == 1)
				{
					ax = 68 + (-24 * 2) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 1) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale16 == 1)
				{
					ax = 68 + (-24 * 2) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 2) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale17 == 1)
				{
					ax = 68 + (-24 * 2) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 3) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale18 == 1)
				{
					ax = 68 + (-24 * 2) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 4) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale19 == 1)
				{
					ax = 68 + (-24 * 2) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 5) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale20 == 1)
				{
					ax = 68 + (-24 * 2) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 6) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale21 == 1)
				{
					ax = 68 + (-24 * 3) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 0) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale22 == 1)
				{
					ax = 68 + (-24 * 3) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 1) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale23 == 1)
				{
					ax = 68 + (-24 * 3) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 2) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale24 == 1)
				{
					ax = 68 + (-24 * 3) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 3) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale25 == 1)
				{
					ax = 68 + (-24 * 3) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 4) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale26 == 1)
				{
					ax = 68 + (-24 * 3) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 5) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale27 == 1)
				{
					ax = 68 + (-24 * 3) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 6) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}	
				if (lightScale28 == 1)
				{
					ax = 68 + (-24 * 4) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 0) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale29 == 1)
				{
					ax = 68 + (-24 * 4) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 1) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale30 == 1)
				{
					ax = 68 + (-24 * 4) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 2) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale31 == 1)
				{
					ax = 68 + (-24 * 4) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 3) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale32 == 1)
				{
					ax = 68 + (-24 * 4) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 4) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale33 == 1)
				{
					ax = 68 + (-24 * 4) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 5) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale34 == 1)
				{
					ax = 68 + (-24 * 4) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 6) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale35 == 1)
				{
					ax = 68 + (-24 * 5) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 0) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale36 == 1)
				{
					ax = 68 + (-24 * 5) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 1) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale37 == 1)
				{
					ax = 68 + (-24 * 5) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 2) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale38 == 1)
				{
					ax = 68 + (-24 * 5) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 3) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale39 == 1)
				{
					ax = 68 + (-24 * 5) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 4) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale40 == 1)
				{
					ax = 68 + (-24 * 5) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 5) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale41 == 1)
				{
					ax = 68 + (-24 * 5) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 6) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale42 == 1)
				{
					ax = 68 + (-24 * 6) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 0) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale43 == 1)
				{
					ax = 68 + (-24 * 6) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 1) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale44 == 1)
				{
					ax = 68 + (-24 * 6) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 2) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale45 == 1)
				{
					ax = 68 + (-24 * 6) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 3) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale46 == 1)
				{
					ax = 68 + (-24 * 6) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 4) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale47 == 1)
				{
					ax = 68 + (-24 * 6) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 5) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
				if (lightScale48 == 1)
				{
					ax = 68 + (-24 * 6) - input.worldpos.x;
					ay = 4 - input.worldpos.y;
					az = -76 + (24 * 6) - input.worldpos.z;
					axyz = ax * ax + ay * ay + az * az;
					xyzDistanse = sqrt(axyz);
					scalr = 1.0 - (xyzDistanse / 7);
					// 全て加算する
					if (scalr >= 0) {
						shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
					}
				}
		}
	}

	// シェーディングによる色で描画
	return shadecolor * texcolor;
}
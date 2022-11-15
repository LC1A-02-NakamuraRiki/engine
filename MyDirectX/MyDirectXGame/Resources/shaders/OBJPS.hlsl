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
			/*if (cameraPos.x + 40 > input.worldpos.x
				&& cameraPos.x - 40 < input.worldpos.x
				&& cameraPos.z + 40 > input.worldpos.z
				&& cameraPos.z - 40 < input.worldpos.z)
			{*/
			if (lightInfo.lightActive == 1 && lightInfo.allActive == 0)
			{
				ax = lightInfo.lightPos.x - input.worldpos.x;
				ay = lightInfo.lightPos.y - input.worldpos.y;
				az = lightInfo.lightPos.z - input.worldpos.z;
				axyz = ax * ax + ay * ay + az * az;
				xyzDistanse = sqrt(axyz);
				scalr = 1.0 - (xyzDistanse / 8);
				// 全て加算する
				if (scalr >= 0) {

					shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;

				}
			}
			else if (lightInfo.allActive == 1)
			{
				for (int x = 0; x < 7; x++)
				{
					for (int y = 0; y < 7; y++)
					{
						ax = 68 + (-24 * x) - input.worldpos.x;
						ay = 4 - input.worldpos.y;
						az = -76 + (24 * y) - input.worldpos.z;
						axyz = ax * ax + ay * ay + az * az;
						xyzDistanse = sqrt(axyz);
						scalr = 1.0 - (xyzDistanse / 8);
						// 全て加算する
						if (scalr >= 0) {

							shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;

						}
					}
				}
			}
			//}
			
		}
	}

	// シェーディングによる色で描画
	return shadecolor * texcolor;
}
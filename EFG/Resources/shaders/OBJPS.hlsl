#include "OBJ.hlsli"

Texture2D<float4> tex : register(t0);  // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

struct PSOutput
{
	float4 target0 : SV_TARGET0;
	float4 target1 : SV_TARGET1;
};

PSOutput main(VSOutput input) : SV_TARGET
{		
	PSOutput output;
	// �e�N�X�`���}�b�s���O
	float4 texcolor = tex.Sample(smp, input.uv);
	// ����x
	const float shininess = 5.0f;
	// ���_���王�_�ւ̕����x�N�g��
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);
	// �����ˌ�
	float3 ambient = m_ambient;
	// �V�F�[�f�B���O�ɂ��F
	float4 shadecolor = float4(ambientColor * ambient, m_alpha);
	for (int i = 0; i < DIRLIGHT_NUM; i++) {
		if (dirLights[i].active) {
			// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
			float3 dotlightnormal = dot(dirLights[i].lightv, input.normal);
			// ���ˌ��x�N�g��
			float3 reflect = normalize(-dirLights[i].lightv + 2.0f * dotlightnormal * input.normal);
			// �g�U���ˌ�
			float3 diffuse = dotlightnormal * m_diffuse;
			// ���ʔ��ˌ�
			float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * float3(1.0f, 1.0f, 1.0f);

			const float3 darkColor = float3(0.7f, 0.7f, 0.7f);
			//�ۉA
			float bx = shadowPos1.x - input.worldpos.x;
			float by = 0 - input.worldpos.y;
			float bz = shadowPos1.z - input.worldpos.z;
			float bxyz = bx * bx + by * by + bz * bz;
			float bxyzDistanse = sqrt(bxyz);
			float bscalr = 1.0f - (bxyzDistanse / 1.6f);
			
			// �S�ĉ��Z����
			if (bscalr >= 0) {
				shadecolor.rgb -= ((diffuse + specular) * dirLights[i].lightcolor) * (darkColor * bscalr);
			}
			float bx2 = shadowPos2.x - input.worldpos.x;
			float by2 = 0 - input.worldpos.y;
			float bz2 = shadowPos2.z - input.worldpos.z;
			float bxyz2 = bx2 * bx2 + by2 * by2 + bz2 * bz2;
			float bxyzDistanse2 = sqrt(bxyz2);
			float bscalr2 = 1.0f - (bxyzDistanse2 / 1.6f);
			//const float3 darkColor2 = float3(0.7f, 0.7f, 0.7f);
			// �S�ĉ��Z����
			if (bscalr2 >= 0) {
				shadecolor.rgb -= ((diffuse + specular) * dirLights[i].lightcolor) * (darkColor * bscalr2);
			}
			float bx3 = shadowPos3.x - input.worldpos.x;
			float by3 = 0 - input.worldpos.y;
			float bz3 = shadowPos3.z - input.worldpos.z;
			float bxyz3 = bx3 * bx3 + by3 * by3 + bz3 * bz3;
			float bxyzDistanse3 = sqrt(bxyz3);
			float bscalr3 = 1.0f - (bxyzDistanse3 / 1.6f);
			//const float3 darkColor3 = float3(0.7f, 0.7f, 0.7f);
			// �S�ĉ��Z����
			if (bscalr3 >= 0) {
				shadecolor.rgb -= ((diffuse + specular) * dirLights[i].lightcolor) * (darkColor * bscalr3);
			}

			//�|�C���g���C�g
			float ax;
			float ay;
			float az;
			float axyz;
			float xyzDistanse;
			float scalr;
			if (lightInfo.lightActive == 1 && lightInfo.allActive == 0)
			{
				ax = lightInfo.lightPos.x - input.worldpos.x;
				ay = lightInfo.lightPos.y - input.worldpos.y;
				az = lightInfo.lightPos.z - input.worldpos.z;
				axyz = ax * ax + ay * ay + az * az;
				xyzDistanse = sqrt(axyz);
				scalr = 1.0f - (xyzDistanse / 8.0f);
				// �S�ĉ��Z����
				if (scalr >= 0) {

					shadecolor.rgb += ((0.125f) * dirLights[i].lightcolor) * scalr;

				}
			}
			else if (lightInfo.allActive == 1 && lightInfo.lightActive)
			{
				for (int x = 0; x < 7; x++)
				{
					for (int y = 0; y < 7; y++)
					{
						ax = 68.0f + (-24.0f * x) - input.worldpos.x;
						ay = 4.0f - input.worldpos.y;
						az = -76.0f + (24.0f * y) - input.worldpos.z;
						axyz = ax * ax + ay * ay + az * az;
						xyzDistanse = sqrt(axyz);
						scalr = 1.0f - (xyzDistanse / 8.0f);
						// �S�ĉ��Z����
						if (scalr >= 0) {

							shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;

						}
					}
				}
			}
		}
	}

	// �V�F�[�f�B���O�ɂ��F�ŕ`��
	output.target0 = shadecolor * texcolor;
	float4 bloomColor = shadecolor * texcolor;
	float whiteValue = bloomColor.r * 0.299f + bloomColor.g * 0.587f + bloomColor.b * 0.114f;
	if (whiteValue < 0.95f)
	{
		output.target1 = float4(0, 0, 0, 1);
	}
	else
	{
		output.target1 = (shadecolor * texcolor) * 0.5f;
	}
	return output;
}
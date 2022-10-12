#include "OBJ.hlsli"

Texture2D<float4> tex : register(t0);  // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
	// �e�N�X�`���}�b�s���O
		float4 texcolor = tex.Sample(smp, input.uv);

		// ����x
		const float shininess = 4.0f;
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
				float3 reflect = normalize(-dirLights[i].lightv + 2 * dotlightnormal * input.normal);
				// �g�U���ˌ�
				float3 diffuse = dotlightnormal * m_diffuse;
				// ���ʔ��ˌ�
				float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

				float ax[10][10];
				float ay[10][10];
				float az[10][10];
				float axyz[10][10];
				float xyzDistanse[10][10];
				float scalr[10][10];

				for (int x = 0; x < 9; x++) {
					for (int z = 0; z < 10; z++) {
						ax[z][x] = 120 + (-32 * x) - input.worldpos.x;
						ay[z][x] = 6 - input.worldpos.y;
						az[z][x] = -152 + (32 * z) - input.worldpos.z;
						axyz[z][x] = ax[z][x] * ax[z][x] + ay[z][x] * ay[z][x] + az[z][x] * az[z][x];
						xyzDistanse[z][x] = sqrt(axyz[z][x]);
						scalr[z][x] = 1.0 - (xyzDistanse[z][x] / 16);
						// �S�ĉ��Z����
						if (scalr[z][x] >= 0)
						{
							shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr[z][x];
						}
					}
				}

				for (int x = 0; x < 10; x++) {
					for (int z = 0; z < 9; z++) {
						ax[z][x] = 136 + (-32 * x) - input.worldpos.x;
						ay[z][x] = 6 - input.worldpos.y;
						az[z][x] = -136 + (32 * z) - input.worldpos.z;
						axyz[z][x] = ax[z][x] * ax[z][x] + ay[z][x] * ay[z][x] + az[z][x] * az[z][x];
						xyzDistanse[z][x] = sqrt(axyz[z][x]);
						scalr[z][x] = 1.0 - (xyzDistanse[z][x] / 16);
						// �S�ĉ��Z����
						if (scalr[z][x] >= 0)
						{
							shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr[z][x];
						}
					}
				}
				/*float ax2 = -8 - input.worldpos.x;
				float ay2 = 12 - input.worldpos.y;
				float az2 = -72 - input.worldpos.z;
				float axyz2 = ax2 * ax2 + ay2 * ay2 + az2 * az2;
				float xyzDistanse2 = sqrt(axyz2);
				float scalr2 = 1.0 - (xyzDistanse2 / 16);
				
				float ax3 = -8 - input.worldpos.x+32;
				float ay3 = 12 - input.worldpos.y;
				float az3 = -40 - input.worldpos.z;
				float axyz3 = ax3 * ax3 + ay3 * ay3 + az3 * az3;
				float xyzDistanse3 = sqrt(axyz3);
				float scalr3 = 1.0 - (xyzDistanse3 / 16);

				float ax4 = -8 - input.worldpos.x -32;
				float ay4 = 12 - input.worldpos.y;
				float az4 = -40 - input.worldpos.z;
				float axyz4 = ax4 * ax4 + ay4 * ay4 + az4 * az4;
				float xyzDistanse4 = sqrt(axyz4);
				float scalr4 = 1.0 - (xyzDistanse4 / 18);*/
				// �S�ĉ��Z����
				/*if (scalr2 >= 0)
				{
					shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr2;
				}
				if (scalr3 >= 0)
				{
					shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr3;
				}
				if (scalr4 >= 0)
				{
					shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr4;
				}*/
			}
		}

		// �V�F�[�f�B���O�ɂ��F�ŕ`��
		return shadecolor * texcolor;
}
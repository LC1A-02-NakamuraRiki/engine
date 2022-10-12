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

				float ax = -8 - input.worldpos.x;
				float ay = 12 - input.worldpos.y;
				float az = -40 - input.worldpos.z;
				float axyz = ax * ax + ay * ay + az * az;
				float xyzDistanse = sqrt(axyz);
				float scalr = 1.0 - (xyzDistanse / 16);

				float ax2 = -8 - input.worldpos.x;
				float ay2 = 12 - input.worldpos.y;
				float az2 = -72 - input.worldpos.z;
				float axyz2 = ax2 * ax2 + ay2 * ay2 + az2 * az2;
				float xyzDistanse2 = sqrt(axyz2);
				float scalr2 = 1.0 - (xyzDistanse2 / 16);
				
				float ax3 = -40 - input.worldpos.x;
				float ay3 = 12 - input.worldpos.y;
				float az3 = -40 - input.worldpos.z;
				float axyz3 = ax3 * ax3 + ay3 * ay3 + az3 * az3;
				float xyzDistanse3 = sqrt(axyz3);
				float scalr3 = 1.0 - (xyzDistanse3 / 16);

				float ax4 = 40 - input.worldpos.x;
				float ay4 = 12 - input.worldpos.y;
				float az4 = -40 - input.worldpos.z;
				float axyz4 = ax4 * ax4 + ay4 * ay4 + az4 * az4;
				float xyzDistanse4 = sqrt(axyz4);
				float scalr4 = 1.0 - (xyzDistanse4 / 16);
				// �S�ĉ��Z����
				if (scalr >= 0)
				{
					shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr;
				}
				if (scalr2 >= 0)
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
				}
			}
		}

		// �V�F�[�f�B���O�ɂ��F�ŕ`��
		return shadecolor * texcolor;
}
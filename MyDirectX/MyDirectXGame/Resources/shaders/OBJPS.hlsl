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

				for (int x = 0; x < 7; x++) {
					for (int z = 0; z < 7; z++) {
						ax[z][x] = 68 + (-24 * x) - input.worldpos.x;
						ay[z][x] = 6 - input.worldpos.y;
						az[z][x] = -76 + (24 * z) - input.worldpos.z;
						axyz[z][x] = ax[z][x] * ax[z][x] + ay[z][x] * ay[z][x] + az[z][x] * az[z][x];
						xyzDistanse[z][x] = sqrt(axyz[z][x]);
						scalr[z][x] = 1.0 - (xyzDistanse[z][x] / 8);
						// �S�ĉ��Z����
						if (scalr[z][x] >= 0)
						{
							shadecolor.rgb += ((diffuse + specular) * dirLights[i].lightcolor) * scalr[z][x];
						}
					}
				}
			}
		}

		// �V�F�[�f�B���O�ɂ��F�ŕ`��
		return shadecolor * texcolor;
}
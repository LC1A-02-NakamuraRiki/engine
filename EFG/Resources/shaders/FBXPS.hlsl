#include "FBX.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

struct PSOutput
{
	float4 target0 : SV_TARGET0;
	float4 target1 : SV_TARGET1;
};

PSOutput main(VSOutput input) : SV_TARGET
{
	PSOutput output;
	//�e�N�X�`���̐F
	float4 texcolor = tex.Sample(smp, input.uv);
	//������
	float4 shadecolor = float4(0,0,0,1);
	// ����x
	const float shininess = 10.0f;
	// ���_���王�_�ւ̕����x�N�g��
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);
	// �����ˌ�
	float3 ambient = 0.175f;
	// �V�F�[�f�B���O�ɂ��F
	float3 lightv[9];
	lightv[0] = float3(0, 1, 0 );
	lightv[1] = float3(1, 0, 0 );
	lightv[2] = float3(-1, 0, 0 );
	lightv[3] = float3(0, 0, 1 ); 
	lightv[4] = float3(0, 0, -1 );
	lightv[5] = float3(0, -1, 0);
	

	for (int i = 0; i < 5; i++) {
		float3 dotlightnormal = dot(lightv[i], input.normal);
		// ���ˌ��x�N�g��
		float3 reflect = normalize(-lightv[i] + 2 * dotlightnormal * input.normal);
		// �g�U���ˌ�
		float3 diffuse = dotlightnormal * 1.0f;
		
		// ���ʔ��ˌ�
		float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * float3(1.0f, 1.0f, 1.0f);
		
		//��グ�̂��߂̒ǉ�
		if (i == 0)
		{
			shadecolor.rgb += ((diffuse + specular + ambient) * 1.5f);
		}
		else
		{
			shadecolor.rgb += ((diffuse + specular + ambient) * 1.5f);
		}

		//�|�C���g���C�g
		for (int x = 0; x < 7; x++)
		{
			for (int y = 0; y < 7; y++)
			{
				if (lightActive)
				{
					float ax = 68 + (-24 * x) - input.worldpos.x;
					float ay = 4 - input.worldpos.y;
					float az = -76 + (24 * y) - input.worldpos.z;
					float axyz = ax * ax + ay * ay + az * az;
					float xyzDistanse = sqrt(axyz);
					float scalr = 1.0 - (xyzDistanse / 8);
					// �S�ĉ��Z����
					if (scalr >= 0) {
						if (i == 0)
						{
							shadecolor.rgb += ((diffuse + specular+ ambient) * 2.0f) * scalr;
						}
						else
						{
							shadecolor.rgb += ((diffuse + specular+ ambient) * 2.0f) * scalr;

						}
					}
				}
			}
		}
	}
	
	output.target0 = shadecolor * texcolor;
	output.target1 = float4(0.0f, 0.0f, 0.0f, 1.0f);
	return output;
}
static const int LIGHT_NUM = 7;
cbuffer cbuff0 : register(b0)
{
	matrix viewproj;
	matrix world;
	float3 cameraPos;
	float3 shadowPos;
	uint lightScale0;
	uint lightScale1;
	uint lightScale2;
	uint lightScale3;
	uint lightScale4;
	uint lightScale5;
	uint lightScale6;
	uint lightScale7;
	uint lightScale8;
	uint lightScale9;
	uint lightScale10;
	uint lightScale11;
	uint lightScale12;
	uint lightScale13;
	uint lightScale14;
	uint lightScale15;
	uint lightScale16;
	uint lightScale17;
	uint lightScale18;
	uint lightScale19;
	uint lightScale20;
	uint lightScale21;
	uint lightScale22;
	uint lightScale23;
	uint lightScale24;
	uint lightScale25;
	uint lightScale26;
	uint lightScale27;
	uint lightScale28;
	uint lightScale29;
	uint lightScale30;
	uint lightScale31;
	uint lightScale32;
	uint lightScale33;
	uint lightScale34;
	uint lightScale35;
	uint lightScale36;
	uint lightScale37;
	uint lightScale38;
	uint lightScale39;
	uint lightScale40;
	uint lightScale41;
	uint lightScale42;
	uint lightScale43;
	uint lightScale44;
	uint lightScale45;
	uint lightScale46;
	uint lightScale47;
	uint lightScale48;

};

cbuffer cbuff1 : register(b1)
{
	float3 m_ambient  : packoffset(c0); // アンビエント係数
	float3 m_diffuse  : packoffset(c1); // ディフューズ係数
	float3 m_specular : packoffset(c2); // スペキュラー係数
	float m_alpha : packoffset(c2.w);	// アルファ
}

static const int DIRLIGHT_NUM = 6;

struct DirLight
{
	float3 lightv;    // ライトへの方向の単位ベクトル
	float3 lightcolor;    // ライトの色(RGB)
	uint active;
};

cbuffer cbuff2 : register(b2)
{
	float3 ambientColor;
	DirLight dirLights[DIRLIGHT_NUM];
}
// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos : SV_POSITION; // システム用頂点座標
	float4 worldpos : POSITION;
	float3 normal :NORMAL;
	float2 uv  :TEXCOORD; // uv値
};
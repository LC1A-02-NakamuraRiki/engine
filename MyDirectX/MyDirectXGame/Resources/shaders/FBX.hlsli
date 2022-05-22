cbuffer cbuff0 : register(b0)
{
	matrix viewproj; // L1-709
	matrix world; // 7-JLP(791
	float3 cameraPos; // DX
};

struct VSInput
{
	float4 pos : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

struct VSOutput
{
	float4 svpos : SV_POSITION;
	float3 normal : NORMAL; 
	float2 uv :TEXCOORD;
};

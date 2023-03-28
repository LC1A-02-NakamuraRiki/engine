cbuffer cbuff0 : register(b0)
{
	float4 color;
	matrix mat;
	bool flag;
	float4 alartColor;
}

struct VSOutput
{
	float4 svpos : SV_POSITION;
	float2 uv :TEXCOORD;
};

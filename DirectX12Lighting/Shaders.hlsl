struct VS_INPUT
{
	float3 pos : POSITION;
	float4 texCoord : TEX_COORD;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float4 texCoord : TEX_COORD;
};

cbuffer WvpConstantBuffer : register(b0)
{
	float4x4 wvp;
};

Texture2D tex : register(t0);
SamplerState samplerState : register(s0);

// simple vertex shader
VS_OUTPUT vsMain(VS_INPUT input)
{
	VS_OUTPUT output;
	output.pos = float4(input.pos, 1.0f);
	output.pos = mul(output.pos, wvp);
	output.texCoord = input.texCoord;

	return output;
}

// simple pixel shader
float4 psMain(VS_OUTPUT input) : SV_TARGET
{
	return tex.Sample(samplerState, input.texCoord);
}

Texture2D texDiffuse : register(t0);

Texture2D texNormal : register(t1);


SamplerState texSampler : register(s0);

cbuffer LightCameraBuffer:register(b1)
{
	float4 LightPosition;
	float4 CameraPosition;
};

cbuffer MaterialBuffer:register(b2)
{

	float4 diffuse;
	float4 ambient;
	float4 specular;
}

struct PSIn
{
	float4 Pos  : SV_Position;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
	float2 TexCoord : TEX;
	float3 WorldPos:POSITION;
};

//-----------------------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------------------

float4 PS_main(PSIn input) : SV_Target
{

	float shininess = 20;

//float3 N = input.Normal;

float3x3 TBN = transpose(float3x3(input.Tangent, input.Binormal,
	input.Normal));

float3 newN = texNormal.Sample(texSampler, input.TexCoord).xyz;

//return float4(newN,1);

newN = newN * 2 - 1;

//float3 newN = { 0,0,0 };

float3 N = mul(TBN, newN);

	float3 L = normalize(LightPosition.xyz - input.WorldPos);
	float3 V = normalize(CameraPosition.xyz - input.WorldPos);
	float3 R = reflect(-L,N); //negativ f�r kan inte reflektera vektor som g�r ifr�n

	float3 Id = diffuse.xyz * max(dot(L,N), 0)*0.6;
	float3 Is = specular.xyz * pow(max(dot(R , V),0), shininess)* 0.6;

	//return float4(Id,1);

	//return float4(input.TexCoord, 0, 1);

	//return texDiffuse.Sample(texSampler, input.TexCoord).xyz;
	
	//return float4(input.Binormal * 0.5 + 0.5, 1);

	//return newN

	return ambient +  float4(saturate(Id* texDiffuse.Sample(texSampler, input.TexCoord).xyz +Is),1);


	//return color;

	// Debug shading #1: map and return normal as a color, i.e. from [-1,1]->[0,1] per component
	// The 4:th component is opacity and should be = 1
	return float4(input.Normal*0.5+0.5, 1);
	
	// Debug shading #2: map and return texture coordinates as a color (blue = 0)
//	return float4(input.TexCoord, 0, 1);
}



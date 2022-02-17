
Texture2D texDiffuse : register(t0);

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
	float2 TexCoord : TEX;
	float3 WorldPos:POSITION;
};

//-----------------------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------------------

float4 PS_main(PSIn input) : SV_Target
{

	float shininess = 10;

float3 N = input.Normal;

	float3 L = normalize(LightPosition.xyz - input.WorldPos);
	float3 V = normalize(CameraPosition.xyz - input.WorldPos);
	float3 R = reflect(-L,N); //negativ för kan inte reflektera vektor som går ifrån

	float3 Id = diffuse.xyz * max(dot(L,N), 0)*0.6;
	float3 Is = specular.xyz * pow(max(dot(R , V),0), shininess)* 0.6;

	//return float4(Id,1);

	//return float4(input.TexCoord, 0, 1);

	//return texDiffuse.Sample(texSampler, input.TexCoord).xyz;

	return /*ambient +*/  float4(saturate(Id* texDiffuse.Sample(texSampler, input.TexCoord).xyz +Is),1);



	//return color;

	// Debug shading #1: map and return normal as a color, i.e. from [-1,1]->[0,1] per component
	// The 4:th component is opacity and should be = 1
	return float4(input.Normal*0.5+0.5, 1);
	
	// Debug shading #2: map and return texture coordinates as a color (blue = 0)
//	return float4(input.TexCoord, 0, 1);
}



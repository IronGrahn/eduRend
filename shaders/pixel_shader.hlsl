
Texture2D texDiffuse : register(t0);


cbuffer LightCameraBuffer:register(b1)
{
	float4 LightPosition;
	float4 CameraPosition;
	//ändra till vec4f från mat
};

cbuffer MaterialBuffer:register(b2)
{
	//float4 color;

	float4 diffuse;
	float4 ambient;
	float4 specular;

	//float4 lightVector;
	//float4 surfaceNormal;
	//float4 viewVector;
	//float4 reflective;
	//float shininess;

	//implmentera de andra faktorerna som ingår i summationsformeln. 
	//testa med snögubben, eventuellt ändra dess bakgrundsvärde färg från maya

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
	//kalkylera L med hjälp av ljusposition minus Pos
	//V = camera pos - pos?
	//R=L-2*(dot(L,N))*N
	//Kolla sida 31-32 i F6!!

	float shininess = 10;

float3 N = input.Normal;

	float3 L = normalize(LightPosition.xyz - input.WorldPos);
	float3 V = normalize(CameraPosition.xyz - input.WorldPos);
	float3 R = reflect(-L,N); //negativ för kan inte reflektera vektor som går ifrån

	float3 Id = diffuse.xyz * max(dot(L,N), 0)*0.6;
	float3 Is = specular.xyz * pow(max(dot(R , V),0), shininess)* 0.6;

	//return float4(Id,1);

	return /*ambient +*/  float4(saturate(Id+Is),1);

	//FRÅGOR
	//Lights mängd?
	// transforma normalen till world space
	//potens alpha i Is?
	//XYZ värden i float4 vid dot product?


	//return color;

	// Debug shading #1: map and return normal as a color, i.e. from [-1,1]->[0,1] per component
	// The 4:th component is opacity and should be = 1
	return float4(input.Normal*0.5+0.5, 1);
	
	// Debug shading #2: map and return texture coordinates as a color (blue = 0)
//	return float4(input.TexCoord, 0, 1);
}



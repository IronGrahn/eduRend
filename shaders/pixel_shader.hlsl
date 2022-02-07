
Texture2D texDiffuse : register(t0);


cbuffer LightCameraBuffer:register(b1)
{
	float4 LightPosition;
	float4 CameraPosition;
	//�ndra till vec4f fr�n mat
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

	//implmentera de andra faktorerna som ing�r i summationsformeln. 
	//testa med sn�gubben, eventuellt �ndra dess bakgrundsv�rde f�rg fr�n maya

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
	//kalkylera L med hj�lp av ljusposition minus Pos
	//V = camera pos - pos?
	//R=L-2*(dot(L,N))*N
	//Kolla sida 31-32 i F6!!

	float shininess = 10;

float3 N = input.Normal;

	float3 L = normalize(LightPosition.xyz - input.WorldPos);
	float3 V = normalize(CameraPosition.xyz - input.WorldPos);
	float3 R = reflect(-L,N); //negativ f�r kan inte reflektera vektor som g�r ifr�n

	float3 Id = diffuse.xyz * max(dot(L,N), 0)*0.6;
	float3 Is = specular.xyz * pow(max(dot(R , V),0), shininess)* 0.6;

	//return float4(Id,1);

	return /*ambient +*/  float4(saturate(Id+Is),1);

	//FR�GOR
	//Lights m�ngd?
	// transforma normalen till world space
	//potens alpha i Is?
	//XYZ v�rden i float4 vid dot product?


	//return color;

	// Debug shading #1: map and return normal as a color, i.e. from [-1,1]->[0,1] per component
	// The 4:th component is opacity and should be = 1
	return float4(input.Normal*0.5+0.5, 1);
	
	// Debug shading #2: map and return texture coordinates as a color (blue = 0)
//	return float4(input.TexCoord, 0, 1);
}



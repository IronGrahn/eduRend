
#pragma once
#ifndef MATRIXBUFFERS_H
#define MATRIXBUFFERS_H

#include "vec\vec.h"
#include "vec\mat.h"

using namespace linalg;

struct MatrixBuffer_t 
{
	mat4f ModelToWorldMatrix;
	mat4f WorldToViewMatrix;
	mat4f ProjectionMatrix;
};

struct LightCameraBuffer
{
	vec4f LightPosition;
	vec4f CameraPosition;
};

struct MaterialBuffer
{

	vec4f diffuse;
	vec4f ambient;
	vec4f specular;
	
	//vec4f lightVector; //L
	//vec4f surfaceNormal; //N
	//vec4f viewVector; //V
	//vec4f reflective; //R
	//float shininess=10; //alpha

	//endast färger plus alpha?
};

#endif
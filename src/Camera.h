
//
//  Camera.h
//
//	Basic camera class
//

#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "vec\vec.h"
#include "vec\mat.h"
#include <math.h>

using namespace linalg;


class Camera
{
public:
	// Aperture attributes
	float vfov, aspect;	
	
	// Clip planes in view space coordinates
	// Evrything outside of [zNear, zFar] is clipped away on the GPU side
	// zNear should be > 0
	// zFar should depend on the size of the scene
	// This range should be kept as tight as possibly to improve
	// numerical precision in the z-buffer
	float zNear, zFar;	
			
	mat4f R;

	vec3f position;

	 float rotationYaw, rotationPitch;



	Camera(
		float vfov,
		float aspect,
		float zNear,
		float zFar):
		vfov(vfov), aspect(aspect), zNear(zNear), zFar(zFar)
	{

		position = { 0.0f, 0.0f, 0.0f };
		rotationYaw = 0;
		rotationPitch = 0;
		R = mat4f::rotation(0, rotationYaw, rotationPitch);
	}

	// Move to an absolute position
	//
	void moveTo(const vec3f& p)
	{
		position = p;
	}

	// Move relatively
	//
	void move(const vec3f& v)
	{
		position += v;
	}

	void rotateTo(const float& yaw, const float& pitch)
	{
		float scale = 0.001;

		rotationYaw += yaw * scale;
		rotationPitch += pitch * scale;

		if (rotationYaw > PI)
			rotationYaw = -PI;
		else if (rotationYaw < -PI)
			rotationYaw = PI;

		if (rotationPitch > PI / 2)
			rotationPitch = PI / 2;
		else if (rotationPitch < -PI / 2)
			rotationPitch = -PI / 2;

	}


	void rotate(const vec3f& r)
	{ 
		//rotation += r;
	}

	// Return World-to-View matrix for this camera
	//
	mat4f get_WorldToViewMatrix()
	{
		// Assuming a camera's position and rotation is defined by matrices T(p) and R,
		// the View-to-World transform is T(p)*R (for a first-person style camera).
		//
		// World-to-View then is the inverse of T(p)*R;
		//		inverse(T(p)*R) = inverse(R)*inverse(T(p)) = transpose(R)*T(-p)
		// Since now there is no rotation, this matrix is simply T(-p)

		R = mat4f::rotation(0, rotationYaw, rotationPitch);
		
		double t = atan2(-R.m31, sqrt(pow(R.m32, 2) + pow(R.m33, 2)));

		if (t<0)
		{
			int i = 9;
		}

		return linalg::transpose( R) * mat4f::translation(-position);
	}

	// Matrix transforming from View space to Clip space
	// In a performance sensitive situation this matrix should be precomputed
	// if possible
	//
	mat4f get_ProjectionMatrix()
	{
		return mat4f::projection(vfov, aspect, zNear, zFar);
	}
};

#endif
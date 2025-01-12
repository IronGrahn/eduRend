
#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "stdafx.h"
#include "InputHandler.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
//inkluda shader buff i scene.cpp

// New files
// Material
// Texture <- stb

// TEMP



//struct D3D11_SAMPLER_DESC {
//	D3D11_FILTER               Filter;
//	D3D11_TEXTURE_ADDRESS_MODE AddressU;
//	D3D11_TEXTURE_ADDRESS_MODE AddressV;
//	D3D11_TEXTURE_ADDRESS_MODE AddressW;
//	FLOAT                      MipLODBias;
//	UINT                       MaxAnisotropy;
//	D3D11_COMPARISON_FUNC      ComparisonFunc;
//	FLOAT                      BorderColor[4];
//	FLOAT                      MinLOD;
//	FLOAT                      MaxLOD;
//} D3D11_SAMPLER_DESC;

class Scene
{
protected:
	ID3D11Device*			dxdevice;
	ID3D11DeviceContext*	dxdevice_context;
	int						window_width;
	int						window_height;


public:

	ID3D11SamplerState* sampler;

	Scene(
		ID3D11Device* dxdevice,
		ID3D11DeviceContext* dxdevice_context,
		int window_width,
		int window_height);

	virtual void Init() = 0;

	virtual void Update(
		float dt,
		InputHandler* input_handler) = 0;
	
	virtual void Render() = 0;
	
	virtual void Release() = 0;

	virtual void WindowResize(
		int window_width,
		int window_height);
};

class OurTestScene : public Scene
{
	//
	// Constant buffers (CBuffers) for data that is sent to shaders
	//

	// CBuffer for transformation matrices
	ID3D11Buffer* matrix_buffer = nullptr;
	ID3D11Buffer* lightcam_buffer = nullptr;
	ID3D11Buffer* material_buffer = nullptr;

	// + other CBuffers

	// 
	// CBuffer client-side definitions
	// These must match the corresponding shader definitions 
	//

	//struct TransformationBuffer
	//{
	//	mat4f ModelToWorldMatrix;
	//	mat4f WorldToViewMatrix;
	//	mat4f ProjectionMatrix;
	//};

	//
	// Scene content
	//
	Camera* camera;

	Cube* cube;
	Cube* middleCube, *smallCube, *smallest;
	QuadModel* quad;
	OBJModel* sponza;
	OBJModel* myModel;

	// Model-to-world transformation matrices
	mat4f Mcube, McubeMiddle, McubeSmall, Msmallest;
	mat4f Msponza, MmyModel;
	mat4f Mquad;


	// World-to-view matrix
	mat4f Mview;
	// Projection matrix
	mat4f Mproj;

	// Misc
	float angle = 0;			// A per-frame updated rotation angle (radians)...
	float angle_vel = fPI / 2;	// ...and its velocity (radians/sec)
	float camera_vel = 5.0f;	// Camera movement velocity in units/s
	float fps_cooldown = 0;

	void InitMatrixBuffer();

	void UpdateMatrixBuffer(
		mat4f ModelToWorldMatrix,
		mat4f WorldToViewMatrix,
		mat4f ProjectionMatrix);

	void InitLightCamBuffer();
	void UpdateLightCamBuffer(vec4f LightPosition, vec3f CameraPosition);

	void InitMaterialBuffer();
	void UpdateMaterialBuffer(vec4f color);

public:
	OurTestScene(
		ID3D11Device* dxdevice,
		ID3D11DeviceContext* dxdevice_context,
		int window_width,
		int window_height);

	void Init() override;

	void Update(
		float dt,
		InputHandler* input_handler) override;

	void Render() override;

	void Release() override;

	void WindowResize(
		int window_width,
		int window_height) override;
};

#endif
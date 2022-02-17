
#include "Scene.h"
#include "ShaderBuffers.h"
#include <math.h>

Scene::Scene(
	ID3D11Device* dxdevice,
	ID3D11DeviceContext* dxdevice_context,
	int window_width,
	int window_height) :
	dxdevice(dxdevice),
	dxdevice_context(dxdevice_context),
	window_width(window_width),
	window_height(window_height)
{ }

void Scene::WindowResize(
	int window_width,
	int window_height)
{
	this->window_width = window_width;
	this->window_height = window_height;
}

OurTestScene::OurTestScene(
	ID3D11Device* dxdevice,
	ID3D11DeviceContext* dxdevice_context,
	int window_width,
	int window_height) :
	Scene(dxdevice, dxdevice_context, window_width, window_height)
{ 
	InitMatrixBuffer();
	InitLightCamBuffer();
	InitMaterialBuffer();
	// + init other CBuffers
}

//
// Called once at initialization
//
void OurTestScene::Init()
{
	camera = new Camera(
		45.0f * fTO_RAD,		// field-of-view (radians)
		(float)window_width / window_height,	// aspect ratio
		1.0f,					// z-near plane (everything closer will be clipped/removed)
		500.0f);				// z-far plane (everything further will be clipped/removed)

	// Move camera to (0,0,5)
	camera->moveTo({ 0, 0, 5 });

	D3D11_SAMPLER_DESC samplerdesc =
	{
	D3D11_FILTER_MIN_MAG_MIP_LINEAR,  // Filter
	D3D11_TEXTURE_ADDRESS_WRAP, // AddressU
	D3D11_TEXTURE_ADDRESS_WRAP, // AddressV
	D3D11_TEXTURE_ADDRESS_CLAMP, // AddressW
	0.0f, // MipLODBias
	16, // MaxAnisotropy
	D3D11_COMPARISON_NEVER, // ComapirsonFunc
	{ 1.0f, 1.0f, 1.0f, 1.0f }, // BorderColor
	-FLT_MAX, // MinLOD
	FLT_MAX, // MaxLOD
	};
	dxdevice->CreateSamplerState(&samplerdesc, &sampler);



	const std::string filepath = "assets/textures/yroadcrossing.png";

	// Create objects
	cube = new Cube(filepath,dxdevice, dxdevice_context);
	middleCube = new Cube(filepath,dxdevice, dxdevice_context);
	smallCube = new Cube(filepath,dxdevice, dxdevice_context);
	smallest = new Cube(filepath,dxdevice, dxdevice_context);
	quad = new QuadModel(dxdevice, dxdevice_context);
	sponza = new OBJModel("assets/crytek-sponza/sponza.obj", dxdevice, dxdevice_context);
	myModel = new OBJModel("assets/snowman/snowman.obj", dxdevice, dxdevice_context);
}

//
// Called every frame
// dt (seconds) is time elapsed since the previous frame
//
void OurTestScene::Update(
	float dt,
	InputHandler* input_handler)
{


	// Basic camera control
	if (input_handler->IsKeyPressed(Keys::Up) || input_handler->IsKeyPressed(Keys::W))
		camera->move({ -camera_vel*dt*sin(camera->rotationYaw), 0.0f, -camera_vel * dt * cos(camera->rotationYaw)}); //COS PÅ Z?
	if (input_handler->IsKeyPressed(Keys::Down) || input_handler->IsKeyPressed(Keys::S))
		camera->move({ camera_vel * dt * sin(camera->rotationYaw), 0.0f, camera_vel * dt * cos(camera->rotationYaw) });
	if (input_handler->IsKeyPressed(Keys::Right) || input_handler->IsKeyPressed(Keys::D))
		camera->move({ camera_vel * dt * cos(camera->rotationYaw), 0.0f, -camera_vel * dt * sin(camera->rotationYaw) });
	if (input_handler->IsKeyPressed(Keys::Left) || input_handler->IsKeyPressed(Keys::A))
		camera->move({ -camera_vel * dt * cos(camera->rotationYaw), 0.0f, camera_vel * dt * sin(camera->rotationYaw) });

	long mousedx = input_handler->GetMouseDeltaX();
	long mousedy = input_handler->GetMouseDeltaY();

	camera->rotateTo(-mousedx, -mousedy);

	// Now set/update object transformations
	// This can be done using any sequence of transformation matrices,
	// but the T*R*S order is most common; i.e. scale, then rotate, and then translate.
	// If no transformation is desired, an identity matrix can be obtained 
	// via e.g. Mquad = linalg::mat4f_identity; 



	Mcube = mat4f::translation(0, 0, 0) *			// No translation
		mat4f::rotation(0, 0.0f, 1.0f, 0.0f) *	// Rotate continuously around the y-axis
		mat4f::scaling(1.5, 1.5, 1.5);				// Scale uniformly to 150%

	McubeMiddle = Mcube * mat4f::translation(0.5, 0.5, 0.5) *			
		mat4f::rotation(0, 0.0f, 1.0f, 0.0f) *	// Rotate continuously around the y-axis
		mat4f::scaling(0.75, 0.75, 0.75);				

	McubeSmall = McubeMiddle * mat4f::translation(0.5, 0.5, 0.5) *
		mat4f::rotation(0, 0.0f, 1.0f, 0.0f) *		// Rotate continuously around the y-axis
		mat4f::scaling(0.75, 0.75, 0.75);

	Msmallest = McubeSmall * mat4f::translation(0.5, 0.5, 0.5) *
		mat4f::rotation(-angle, 0.0f, 1.0f, 0.0f) *		// Rotate continuously around the y-axis
		mat4f::scaling(0.75, 0.75, 0.75);

	// Quad model-to-world transformation
	Mquad = mat4f::translation(0, 0, 0) *			// No translation
		mat4f::rotation(-angle, 0.0f, 1.0f, 0.0f) *	// Rotate continuously around the y-axis
		mat4f::scaling(1.5, 1.5, 1.5);				// Scale uniformly to 150%

	// Sponza model-to-world transformation
	Msponza = mat4f::translation(0, -5, 0) *		 // Move down 5 units
		mat4f::rotation(fPI / 2, 0.0f, 1.0f, 0.0f) * // Rotate pi/2 radians (90 degrees) around y
		mat4f::scaling(0.05f);						 // The scene is quite large so scale it down to 5%

	MmyModel = mat4f::translation(0, -5, 0) *		 // Move down 5 units
		mat4f::rotation(angle*4, 0.0f, 1.0f, 0.0f) * 
		mat4f::scaling(1.0f);						 


	// Increment the rotation angle.
	angle += angle_vel * dt;

	// Print fps
	fps_cooldown -= dt;
	if (fps_cooldown < 0.0)
	{
		std::cout << "fps " << (int)(1.0f / dt) << std::endl;
//		printf("fps %i\n", (int)(1.0f / dt));
		fps_cooldown = 2.0;
	}
}

//
// Called every frame, after update
//
void OurTestScene::Render()
{
	// Bind transformation_buffer to slot b0 of the VS
	dxdevice_context->VSSetConstantBuffers(0, 1, &matrix_buffer);

	dxdevice_context->PSSetConstantBuffers(1, 1, &lightcam_buffer);

	dxdevice_context->PSSetConstantBuffers(2, 1, &material_buffer);

	dxdevice_context->PSSetSamplers(
		0, // slot #
		1, // number of samplers to bind (1)
		&sampler);

	//första parametern är för specifik plats. NOTERA skillnad mellan PS och VS

	UpdateLightCamBuffer({ 5,8,0,1 }, camera->position);

	// Obtain the matrices needed for rendering from the camera
	Mview = camera->get_WorldToViewMatrix();
	Mproj = camera->get_ProjectionMatrix();

	//IMPLEMENTERA MATERIAL BUFFERS I KUBERNA

	UpdateMatrixBuffer(Mcube, Mview, Mproj);
	cube->Render(material_buffer);
	
	UpdateMatrixBuffer(McubeMiddle, Mview, Mproj);
	middleCube->Render(material_buffer);
	
	UpdateMatrixBuffer(McubeSmall, Mview, Mproj);
	smallCube->Render(material_buffer);

	UpdateMatrixBuffer(Msmallest, Mview, Mproj);
	smallest->Render(material_buffer);

	// Load matrices + the Quad's transformation to the device and render it
	//UpdateMatrixBuffer(Mquad, Mview, Mproj);
	//quad->Render();

	// Load matrices + Sponza's transformation to the device and render it
	UpdateMatrixBuffer(Msponza, Mview, Mproj);
	sponza->Render(material_buffer);

	UpdateMatrixBuffer(MmyModel, Mview, Mproj);
	myModel->Render(material_buffer);

}

void OurTestScene::Release()
{
	SAFE_DELETE(cube);
	SAFE_DELETE(middleCube);
	SAFE_DELETE(smallCube);
	SAFE_DELETE(quad);
	SAFE_DELETE(sponza);
	SAFE_DELETE(myModel);
	SAFE_DELETE(camera);

	SAFE_RELEASE(matrix_buffer);
	SAFE_RELEASE(lightcam_buffer);
	SAFE_RELEASE(material_buffer);
	SAFE_RELEASE(sampler);

	// + release other CBuffers
}

void OurTestScene::WindowResize(int window_width,int window_height)
{
	if (camera)
		camera->aspect = float(window_width) / window_height;

	Scene::WindowResize(window_width, window_height);
}

void OurTestScene::InitMatrixBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC MatrixBuffer_desc = { 0 };
	MatrixBuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	MatrixBuffer_desc.ByteWidth = sizeof(MatrixBuffer_t);
	MatrixBuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	MatrixBuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	MatrixBuffer_desc.MiscFlags = 0;
	MatrixBuffer_desc.StructureByteStride = 0;
	ASSERT(hr = dxdevice->CreateBuffer(&MatrixBuffer_desc, nullptr, &matrix_buffer));
}



void OurTestScene::UpdateMatrixBuffer(mat4f ModelToWorldMatrix, mat4f WorldToViewMatrix, mat4f ProjectionMatrix)
{
	// Map the resource buffer, obtain a pointer and then write our matrices to it
	D3D11_MAPPED_SUBRESOURCE resource;
	dxdevice_context->Map(matrix_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	MatrixBuffer_t* matrix_buffer_ = (MatrixBuffer_t*)resource.pData;
	matrix_buffer_->ModelToWorldMatrix = ModelToWorldMatrix;
	matrix_buffer_->WorldToViewMatrix = WorldToViewMatrix;
	matrix_buffer_->ProjectionMatrix = ProjectionMatrix;
	dxdevice_context->Unmap(matrix_buffer, 0);
}

void OurTestScene::InitLightCamBuffer()
{
	HRESULT hr;

	D3D11_BUFFER_DESC LightCameraBuffer_desc = { 0 };
	LightCameraBuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	LightCameraBuffer_desc.ByteWidth = sizeof(LightCameraBuffer);
	LightCameraBuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	LightCameraBuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	LightCameraBuffer_desc.MiscFlags = 0;
	LightCameraBuffer_desc.StructureByteStride = 0;
	ASSERT(hr = dxdevice->CreateBuffer(&LightCameraBuffer_desc, nullptr, &lightcam_buffer));

}

void OurTestScene::UpdateLightCamBuffer(vec4f LightPosition, vec3f CameraPosition)
{
	//ge egen ljusposition

	D3D11_MAPPED_SUBRESOURCE resource;
	dxdevice_context->Map(lightcam_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	LightCameraBuffer* lightcam_buffer_ = (LightCameraBuffer*)resource.pData;
	lightcam_buffer_->LightPosition = LightPosition;
	lightcam_buffer_->CameraPosition = {CameraPosition.x,CameraPosition.y,CameraPosition.z,1};
	dxdevice_context->Unmap(lightcam_buffer, 0);
}

void OurTestScene::InitMaterialBuffer()
{
	HRESULT hr;

	D3D11_BUFFER_DESC MaterialBuffer_desc = { 0 };
	MaterialBuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	MaterialBuffer_desc.ByteWidth = sizeof(MaterialBuffer);
	MaterialBuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	MaterialBuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	MaterialBuffer_desc.MiscFlags = 0;
	MaterialBuffer_desc.StructureByteStride = 0;
	ASSERT(hr = dxdevice->CreateBuffer(&MaterialBuffer_desc, nullptr, &material_buffer));

}

void OurTestScene::UpdateMaterialBuffer(vec4f color)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	dxdevice_context->Map(material_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	MaterialBuffer* material_buffer_ = (MaterialBuffer*)resource.pData;

	//Finns nu i Model.cpp Render
	//material_buffer_->color = color;
	dxdevice_context->Unmap(material_buffer, 0);
}

//kopiera matrix buffer rakt av? egen init och update?
//copy pastea init basically, men ändra parametrar då nya struct

//uppdatera material var? Render i model.cpp/PSmain
//VSMain i pixelshader? PSMain finns redan
//implementa material på ett objekt var? via Render också

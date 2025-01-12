//
//  Model.cpp
//
//  CJ Gribel 2016, cjgribel@gmail.com
//

#include "Model.h"


void rotateVertex(Vertex v, mat4f rotation)
{
  /*  v.Binormal = v.Binormal * v.Normal;

    v.Binormal=mul()*/

}


Cube::Cube(const std::string& filepath, const std::string& normal_filepath, ID3D11Device* dxdevice, ID3D11DeviceContext* dxdevice_context) :Model(dxdevice, dxdevice_context)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;

    Vertex v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23;

    //fram / +z

    v0.Pos = { -0.5, 0.5, 0.5 };
    v0.Normal = { 0, 0, 1 };
    v0.TexCoord = { 0, 0 };

    v1.Pos = { 0.5, 0.5, 0.5 };
    v1.Normal = { 0, 0, 1 };
    v1.TexCoord = { 0, 1 };

    v2.Pos = { -0.5, -0.5, 0.5 };
    v2.Normal = { 0, 0, 1 };
    v2.TexCoord = { 1, 0 };

    v3.Pos = { 0.5, -0.5, 0.5 };
    v3.Normal = { 0, 0, 1 };
    v3.TexCoord = { 1, 1 };

    v0.Binormal = { 0,1,0 };
    v0.Tangent = { 1,0,0 };

    v1.Binormal = { 0,1,0 };
    v1.Tangent = { 1,0,0 };

    v2.Binormal = { 0,1,0 };
    v2.Tangent = { 1,0,0 };

    v3.Binormal = { 0,1,0 };
    v3.Tangent = { 1,0,0 };

    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);




    // Triangle #1
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(1);
    // Triangle #2
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);

    //upp / +y

    v4.Pos = { -0.5, 0.5, -0.5 };
    v4.Normal = { 0, 1, 0 };
    v4.TexCoord = { 0, 0 };

    v5.Pos = { 0.5, 0.5f, -0.5 };
    v5.Normal = { 0, 1, 0 };
    v5.TexCoord = { 0, 1 };
    
    v6.Pos = { -0.5, 0.5, 0.5 };
    v6.Normal = { 0, 1, 0 };
    v6.TexCoord = { 1, 0 };
    
    v7.Pos = { 0.5, 0.5, 0.5 };
    v7.Normal = { 0, 1, 0 };
    v7.TexCoord = { 1, 1 };


    v4.Binormal = { 0,0,-1 };
    v4.Tangent = { 1,0,0 };

    v5.Binormal = { 0,0,-1 };
    v5.Tangent = { 1,0,0 };

    v6.Binormal = { 0,0,-1 };
    v6.Tangent = { 1,0,0 };

    v7.Binormal = { 0,0,-1 };
    v7.Tangent = { 1,0,0 };

    vertices.push_back(v4);
    vertices.push_back(v5);
    vertices.push_back(v6);
    vertices.push_back(v7);

    // Triangle #3
    indices.push_back(4);
    indices.push_back(6);
    indices.push_back(5);
    // Triangle #4
    indices.push_back(5);
    indices.push_back(6);
    indices.push_back(7);

    



    //h�ger / +x

    v8.Pos = { 0.5, 0.5, 0.5 };
    v8.Normal = { 1, 0, 0 };
    v8.TexCoord = { 0, 0 };
   
    v9.Pos = { 0.5, 0.5, -0.5 };
    v9.Normal = { 1, 0, 0 };
    v9.TexCoord = { 0, 1 };
    
    v10.Pos = { 0.5, -0.5, 0.5 };
    v10.Normal = { 1, 0, 0 };
    v10.TexCoord = { 1, 0 };
    
    v11.Pos = { 0.5, -0.5, -0.5 };
    v11.Normal = { 1, 0, 0 };
    v11.TexCoord = { 1, 1 };

    v8.Binormal = { 0,1,0 };
    v8.Tangent = { 0,0,-1 };

    v9.Binormal = { 0,1,0 };
    v9.Tangent = { 0,0,-1 };

    v10.Binormal = { 0,1,0 };
    v10.Tangent = { 0,0,-1 };

    v11.Binormal = { 0,1,0 };
    v11.Tangent = { 0,0,-1 };



    vertices.push_back(v8);
    vertices.push_back(v9);
    vertices.push_back(v10);
    vertices.push_back(v11);

    // Triangle #5
    indices.push_back(8);
    indices.push_back(10);
    indices.push_back(9);
    // Triangle #6
    indices.push_back(9);
    indices.push_back(10);
    indices.push_back(11);

 

    //ner / -y

    v12.Pos = { -0.5, -0.5, 0.5 };
    v12.Normal = { 0, -1, 0 };
    v12.TexCoord = { 0, 0 };

    v13.Pos = { 0.5, -0.5, 0.5 };
    v13.Normal = { 0, -1, 0 };
    v13.TexCoord = { 0, 1 };

    v14.Pos = { -0.5, -0.5, -0.5 };
    v14.Normal = { 0, -1, 0 };
    v14.TexCoord = { 1, 0 };
    
    v15.Pos = { 0.5, -0.5, -0.5 };
    v15.Normal = { 0, -1, 0 };
    v15.TexCoord = { 1, 1 };

    v12.Binormal = { 0,0,1 };
    v12.Tangent = { 1,0,0 };

    v13.Binormal = { 0,0,1 };
    v13.Tangent = { 1,0,0 };

    v14.Binormal = { 0,0,1 };
    v14.Tangent = { 1,0,0 };

    v15.Binormal = { 0,0,1 };
    v15.Tangent = { 1,0,0 };


    vertices.push_back(v12);
    vertices.push_back(v13);
    vertices.push_back(v14);
    vertices.push_back(v15);

    // Triangle #7
    indices.push_back(12);
    indices.push_back(14);
    indices.push_back(13);
    // Triangle #8
    indices.push_back(13);
    indices.push_back(14);
    indices.push_back(15);




    //v�nster / -x
    
    v16.Pos = { -0.5, 0.5, -0.5 };
    v16.Normal = { -1, 0, 0 };
    v16.TexCoord = { 0, 0 };

    v17.Pos = { -0.5, 0.5, 0.5 };
    v17.Normal = { -1, 0, 0 };
    v17.TexCoord = { 0, 1 };

    v18.Pos = { -0.5, -0.5, -0.5 };
    v18.Normal = { -1, 0, 0 };
    v18.TexCoord = { 1, 0 };

    v19.Pos = { -0.5, -0.5, 0.5 };
    v19.Normal = { -1, 0, 0 };
    v19.TexCoord = { 1, 1 };


    v16.Binormal = { 0,1,0 };
    v16.Tangent = { 0,0,1 };

    v17.Binormal = { 0,1,0 };
    v17.Tangent = { 0,0,1 };

    v18.Binormal = { 0,1,0 };
    v18.Tangent = { 0,0,1 };

    v19.Binormal = { 0,1,0 };
    v19.Tangent = { 0,0,1 };


    vertices.push_back(v16);
    vertices.push_back(v17);
    vertices.push_back(v18);
    vertices.push_back(v19);

    // Triangle #9
    indices.push_back(16);
    indices.push_back(18);
    indices.push_back(17);
    // Triangle #10
    indices.push_back(17);
    indices.push_back(18);
    indices.push_back(19);


    //bak / -z

    v20.Pos = { 0.5, 0.5, -0.5 };
    v20.Normal = { 0, 0, -1 };
    v20.TexCoord = { 0, 0 };

    v21.Pos = { -0.5, 0.5, -0.5 };
    v21.Normal = { 0, 0, -1 };
    v21.TexCoord = { 0, 1 };
    
    v22.Pos = { 0.5, -0.5, -0.5 };
    v22.Normal = { 0, 0, -1 };
    v22.TexCoord = { 1, 0 };
    
    v23.Pos = { -0.5, -0.5, -0.5 };
    v23.Normal = {0, 0, -1 };
    v23.TexCoord = { 1, 1 };


    v20.Binormal = { 0,1,0 };
    v20.Tangent = { -1,0,0 };

    v21.Binormal = { 0,1,0 };
    v21.Tangent = { -1,0,0 };

    v22.Binormal = { 0,1,0 };
    v22.Tangent = { -1,0,0 };

    v23.Binormal = { 0,1,0 };
    v23.Tangent = { -1,0,0 };


    vertices.push_back(v20);
    vertices.push_back(v21);
    vertices.push_back(v22);
    vertices.push_back(v23);

    // Triangle #11
    indices.push_back(20);
    indices.push_back(22);
    indices.push_back(21);
    // Triangle #12
    indices.push_back(21);
    indices.push_back(22);
    indices.push_back(23);




    // Vertex array descriptor
    D3D11_BUFFER_DESC vbufferDesc = { 0 };
    vbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbufferDesc.CPUAccessFlags = 0;
    vbufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vbufferDesc.MiscFlags = 0;
    vbufferDesc.ByteWidth = (UINT)(vertices.size() * sizeof(Vertex));
    // Data resource
    D3D11_SUBRESOURCE_DATA vdata;
    vdata.pSysMem = &vertices[0];
    // Create vertex buffer on device using descriptor & data
    const HRESULT vhr = dxdevice->CreateBuffer(&vbufferDesc, &vdata, &vertex_buffer);
    SETNAME(vertex_buffer, "VertexBuffer");

    //  Index array descriptor
    D3D11_BUFFER_DESC ibufferDesc = { 0 };
    ibufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibufferDesc.CPUAccessFlags = 0;
    ibufferDesc.Usage = D3D11_USAGE_DEFAULT;
    ibufferDesc.MiscFlags = 0;
    ibufferDesc.ByteWidth = (UINT)(indices.size() * sizeof(unsigned));
    // Data resource
    D3D11_SUBRESOURCE_DATA idata;
    idata.pSysMem = &indices[0];
    // Create index buffer on device using descriptor & data
    const HRESULT ihr = dxdevice->CreateBuffer(&ibufferDesc, &idata, &index_buffer);
    SETNAME(index_buffer, "IndexBuffer");

    nbr_indices = (unsigned int)indices.size();

    

    material.Kd_texture_filename = filepath;

    std::cout << "Loading textures..." << std::endl;
    HRESULT hr;

    // Load Diffuse texture
    //
    if (material.Kd_texture_filename.size()) {

        hr = LoadTextureFromFile(
            dxdevice,
            material.Kd_texture_filename.c_str(),
            &material.diffuse_texture);
        std::cout << "\t" << material.Kd_texture_filename
            << (SUCCEEDED(hr) ? " - OK" : "- FAILED") << std::endl;
    }



    material.normal_texture_filename = normal_filepath;
    HRESULT nhr;

    // Load Normal texture
    //
    if (material.normal_texture_filename.size()) {

        nhr = LoadTextureFromFile(
            dxdevice,
            material.normal_texture_filename.c_str(),
            &material.normal_texture);
        std::cout << "\t" << material.normal_texture_filename
            << (SUCCEEDED(nhr) ? " - OK" : "- FAILED") << std::endl;
    }

    // + other texture types here - see Material class
    // ...    std::cout << "Done." << std::endl;
}

void Cube::Render(ID3D11Buffer* material_buffer) const
{
    // Bind our vertex buffer
    const UINT32 stride = sizeof(Vertex); //  sizeof(float) * 8;
    const UINT32 offset = 0;
    dxdevice_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);

    // Bind our index buffer
    dxdevice_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

    // drawcall

    // Bind diffuse texture to slot t0 of the PS
    dxdevice_context->PSSetShaderResources(0, 1, &material.diffuse_texture.texture_SRV);
    dxdevice_context->PSSetShaderResources(1, 1, &material.normal_texture.texture_SRV);
    //binda constant buffer

    D3D11_MAPPED_SUBRESOURCE resource;
    dxdevice_context->Map(material_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
    MaterialBuffer* material_buffer_ = (MaterialBuffer*)resource.pData;
    material_buffer_->diffuse = vec4f(0.5, 0.5, 0.5,1);
    material_buffer_->ambient = vec4f(0.5, 0.5, 0.5, 1);
    material_buffer_->specular = vec4f(0.5, 0.5, 0.5, 1);
    dxdevice_context->Unmap(material_buffer, 0);

    //// + bind other textures here, e.g. a normal map, to appropriate slots



    // Make the drawcall

    dxdevice_context->DrawIndexed(nbr_indices, 0, 0);

}


QuadModel::QuadModel(
    ID3D11Device* dxdevice,
    ID3D11DeviceContext* dxdevice_context)
    : Model(dxdevice, dxdevice_context)
{
    // Vertex and index arrays
    // Once their data is loaded to GPU buffers, they are not needed anymore
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;

    // Populate the vertex array with 4 vertices
    Vertex v0, v1, v2, v3;
    v0.Pos = { -0.5, -0.5f, 0.0f };
    v0.Normal = { 0, 0, 1 };
    v0.TexCoord = { 0, 0 };
    v1.Pos = { 0.5, -0.5f, 0.0f };
    v1.Normal = { 0, 0, 1 };
    v1.TexCoord = { 0, 1 };
    v2.Pos = { 0.5, 0.5f, 0.0f };
    v2.Normal = { 0, 0, 1 };
    v2.TexCoord = { 1, 1 };
    v3.Pos = { -0.5, 0.5f, 0.0f };
    v3.Normal = { 0, 0, 1 };
    v3.TexCoord = { 1, 0 };
    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);

    // Populate the index array with two triangles
    // Triangle #1
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);
    // Triangle #2
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);

    // Vertex array descriptor
    D3D11_BUFFER_DESC vbufferDesc = { 0 };
    vbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbufferDesc.CPUAccessFlags = 0;
    vbufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vbufferDesc.MiscFlags = 0;
    vbufferDesc.ByteWidth = (UINT)(vertices.size()*sizeof(Vertex));
    // Data resource
    D3D11_SUBRESOURCE_DATA vdata;
    vdata.pSysMem = &vertices[0];
    // Create vertex buffer on device using descriptor & data
    const HRESULT vhr = dxdevice->CreateBuffer(&vbufferDesc, &vdata, &vertex_buffer);
    SETNAME(vertex_buffer, "VertexBuffer");
    
    //  Index array descriptor
    D3D11_BUFFER_DESC ibufferDesc = { 0 };
    ibufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibufferDesc.CPUAccessFlags = 0;
    ibufferDesc.Usage = D3D11_USAGE_DEFAULT;
    ibufferDesc.MiscFlags = 0;
    ibufferDesc.ByteWidth = (UINT)(indices.size()*sizeof(unsigned));
    // Data resource
    D3D11_SUBRESOURCE_DATA idata;
    idata.pSysMem = &indices[0];
    // Create index buffer on device using descriptor & data
    const HRESULT ihr = dxdevice->CreateBuffer(&ibufferDesc, &idata, &index_buffer);
    SETNAME(index_buffer, "IndexBuffer");
    
    nbr_indices = (unsigned int)indices.size();
}


void QuadModel::Render() const
{
    // Bind our vertex buffer
    const UINT32 stride = sizeof(Vertex); //  sizeof(float) * 8;
    const UINT32 offset = 0;
    dxdevice_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);

    // Bind our index buffer
    dxdevice_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

    // Make the drawcall
    dxdevice_context->DrawIndexed(nbr_indices, 0, 0);
}


OBJModel::OBJModel(
    const std::string& objfile,
    ID3D11Device* dxdevice,
    ID3D11DeviceContext* dxdevice_context)
    : Model(dxdevice, dxdevice_context)
{
    // Load the OBJ
    OBJLoader* mesh = new OBJLoader();
    mesh->Load(objfile);

    // Load and organize indices in ranges per drawcall (material)

    std::vector<unsigned> indices;
    unsigned int i_ofs = 0;

    for (auto& dc : mesh->drawcalls)
    {
        // Append the drawcall indices
        for (auto& tri : dc.tris)
            indices.insert(indices.end(), tri.vi, tri.vi + 3);

        // Create a range
        unsigned int i_size = (unsigned int)dc.tris.size() * 3;
        int mtl_index = dc.mtl_index > -1 ? dc.mtl_index : -1;
        index_ranges.push_back({ i_ofs, i_size, 0, mtl_index });

        i_ofs = (unsigned int)indices.size();
    }

    //loopa igenom indices +3 var g�ng. f�r lengyel

    // Vertex array descriptor
    D3D11_BUFFER_DESC vbufferDesc = { 0 };
    vbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbufferDesc.CPUAccessFlags = 0;
    vbufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vbufferDesc.MiscFlags = 0;
    vbufferDesc.ByteWidth = (UINT)(mesh->vertices.size()*sizeof(Vertex));
    // Data resource
    D3D11_SUBRESOURCE_DATA vdata;
    vdata.pSysMem = &(mesh->vertices)[0];
    // Create vertex buffer on device using descriptor & data
    HRESULT vhr = dxdevice->CreateBuffer(&vbufferDesc, &vdata, &vertex_buffer);
    SETNAME(vertex_buffer, "VertexBuffer");
    
    // Index array descriptor
    D3D11_BUFFER_DESC ibufferDesc = { 0 };
    ibufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibufferDesc.CPUAccessFlags = 0;
    ibufferDesc.Usage = D3D11_USAGE_DEFAULT;
    ibufferDesc.MiscFlags = 0;
    ibufferDesc.ByteWidth = (UINT)(indices.size()*sizeof(unsigned));
    // Data resource
    D3D11_SUBRESOURCE_DATA idata;
    idata.pSysMem = &indices[0];
    // Create index buffer on device using descriptor & data
    HRESULT ihr = dxdevice->CreateBuffer(&ibufferDesc, &idata, &index_buffer);
    SETNAME(index_buffer, "IndexBuffer");
    
    // Copy materials from mesh
    append_materials(mesh->materials);

    // Go through materials and load textures (if any) to device
    std::cout << "Loading textures..." << std::endl;
    for (auto& mtl : materials)
    {
        HRESULT hr;

        // Load Diffuse texture
        //
        if (mtl.Kd_texture_filename.size()) {

           

            hr = LoadTextureFromFile(
                dxdevice,
                mtl.Kd_texture_filename.c_str(), 
                &mtl.diffuse_texture);
            std::cout << "\t" << mtl.Kd_texture_filename 
                << (SUCCEEDED(hr) ? " - OK" : "- FAILED") << std::endl;
        }



        if (mtl.normal_texture_filename.size()) {

            hr = LoadTextureFromFile(
                dxdevice,
                mtl.normal_texture_filename.c_str(),
                &mtl.normal_texture);
            std::cout << "\t" << mtl.normal_texture_filename
                << (SUCCEEDED(hr) ? " - OK" : "- FAILED") << std::endl;
        }

        // + other texture types here - see Material class
        // ...
    }
    std::cout << "Done." << std::endl;

    SAFE_DELETE(mesh);
}


void OBJModel::Render(ID3D11Buffer* material_buffer) const
{
    //l�gg material buffer i argument

    // Bind vertex buffer
    const UINT32 stride = sizeof(Vertex);
    const UINT32 offset = 0;
    dxdevice_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);

    // Bind index buffer
    dxdevice_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

    // Iterate drawcalls
    for (auto& irange : index_ranges)
    {
        // Fetch material
        const Material& mtl = materials[irange.mtl_index];

        // Bind diffuse texture to slot t0 of the PS
        dxdevice_context->PSSetShaderResources(0, 1, &mtl.diffuse_texture.texture_SRV);
        dxdevice_context->PSSetShaderResources(1, 1, &mtl.normal_texture.texture_SRV);

        //binda constant buffer
        
        D3D11_MAPPED_SUBRESOURCE resource;
        dxdevice_context->Map(material_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
        MaterialBuffer* material_buffer_ = (MaterialBuffer*)resource.pData;
        material_buffer_->diffuse = mtl.Kd.xyz1();
        material_buffer_->ambient = mtl.Ka.xyz1();
        material_buffer_->specular = mtl.Ks.xyz1();
        dxdevice_context->Unmap(material_buffer, 0);

        // + bind other textures here, e.g. a normal map, to appropriate slots

        // Make the drawcall
        dxdevice_context->DrawIndexed(irange.size, irange.start, 0);
    }
}

OBJModel::~OBJModel()
{
    for (auto& material : materials)
    {
        SAFE_RELEASE(material.diffuse_texture.texture_SRV);

        // Release other used textures ...
    }
}
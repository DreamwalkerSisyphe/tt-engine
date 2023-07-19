#include "ModelLoader.h"

Neco::Neco()
{
    neco = LoadModel("assets/neco/neco.obj");
    /*Texture2D albedo = LoadTexture("assets/neco/necoarctposefeettilt_None_BaseColor.png");
    Texture2D height = LoadTexture("assets/neco/necoarctposefeettilt_None_Height.png");
    Texture2D metallic = LoadTexture("assets/neco/necoarctposefeettilt_None_Metallic.png");
    Texture2D normal = LoadTexture("assets/neco/necoarctposefeettilt_None_Normal.png");
    Texture2D roughness = LoadTexture("assets/neco/necoarctposefeettilt_None_Roughness.png");*/

    /*neco.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = albedo;
    neco.materials[0].maps[MATERIAL_MAP_HEIGHT].texture = height;
    neco.materials[0].maps[MATERIAL_MAP_METALNESS].texture = metallic;
    neco.materials[0].maps[MATERIAL_MAP_NORMAL].texture = normal;
    neco.materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture = roughness;*/
    BoundingBox bounds = GetMeshBoundingBox(neco.meshes[0]);
}

Neco::~Neco()
{
    //delete &neco;
}

Model& Neco::GetNeco()
{
    return neco;
}
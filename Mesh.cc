#include "Mesh.h"
#include <string>

namespace Advanced2D {
	Mesh::Mesh() {
		mesh = 0;
		materials = 0;
		d3dxMaterials = 0;
		matbuffer = 0;
		material_count = 0;
		textures = 0;
		position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	Mesh::~Mesh() {
		if (materials != NULL) delete [] materials;
		if (textures != NULL) {
			for (DWORD i = 0; i < material_count; ++i) {
				if (textures[i] != NULL)
					textures[i]->Release();
			}
			delete [] textures;
		}
		if (mesh != NULL) mesh->Release();
	}

	int Mesh::GetFaceCount() {
		return this->mesh->GetNumFaces();
	}

	int Mesh::GetVertexCount() {
		return this->mesh->GetNumVertices();
	}

	bool Mesh::Load(char *filename) {
		HRESULT result;
		result = D3DXLoadMeshFromX(
				filename,
				D3DXMESH_SYSTEMMEM,
				g_engine->getDevice(),
				NULL,
				&matbuffer,
				NULL,
				&material_count,
				&mesh);
		if (result != D3D_OK) {
			return false;
		}

		d3dxMaterials = (LPD3DXMATERIAL)matbuffer->GetBufferPointer();
		materials = new D3DMATERIAL9[material_count];
		textures = new LPDIRECT3DTEXTURE9[material_count];

		for (DWORD i = 0; i < material_count; ++i) {
			materials[i] = d3dxMaterials[i].MatD3D;
			materials[i].Ambient = materials[i].Diffuse;
			//materials[i].Emissive = materials[i].Diffuse;
			materials[i].Power = 0.5f;
			//materials[i].Specular = materials[i].Diffuse;
			textures[i] = NULL;
			if (d3dxMaterials[i].pTextureFilename != NULL &&
					lstrlen(d3dxMaterials[i].pTextureFilename) > 0) {
				result = D3DXCreateTextureFromFile(g_engine->getDevice(),
						d3dxMaterials[i].pTextureFilename, &textures[i]);
				if (result != D3D_OK) {
					return false;
				}
			}
		}

		matbuffer->Release();
		return true;
	}

	void Mesh::CreateSphere(float radius, int slices, int stacks) {
		D3DXCreateSphere(g_engine->getDevice(), radius, slices, stacks, 
				&mesh, NULL);
	}

	void Mesh::CreateCube(float width, float height, float depth) {
		D3DXCreateBox(g_engine->getDevice(), width, height, depth,
				&mesh, NULL);
	}

	void Mesh::Draw() {
		if (material_count == 0) {
			mesh->DrawSubset(0);
		} else {
			for (DWORD i = 0; i < material_count; ++i) {
				g_engine->getDevice()->SetMaterial(&materials[i]);
				if (textures[i]) {
					if (textures[i]->GetType() == D3DRTYPE_TEXTURE) {
						D3DSURFACE_DESC desc;
						textures[i]->GetLevelDesc(0, &desc);
						if (desc.Width > 0) {
							g_engine->getDevice()->SetTexture(0, textures[i]);
						}
					}
				}
				mesh->DrawSubset(i);
			}
		}
	}

	void Mesh::Transform() {
		float x = D3DXToRadian(rotation.x);
		float y = D3DXToRadian(rotation.y);
		float z = D3DXToRadian(rotation.z);
		D3DXMatrixRotationYawPitchRoll(&matRotate, x, y, z);
		D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
		D3DXMatrixTranslation(&matTranslate, position.x, position.y, position.z);
		matWorld = matRotate * matScale * matTranslate;
		g_engine->getDevice()->SetTransform(D3DTS_WORLD, &matWorld);
	}

	void Mesh::Rotate(D3DXVECTOR3 rot) {
		Rotate(rot.x, rot.y, rot.z);
	}

	void Mesh::Rotate(float x, float y, float z) {
		rotation.x += x;
		rotation.y += y;
		rotation.z += z;
	}

	void Mesh::Update() {
		position.x += velocity.x;
		position.y += velocity.y;
		position.z += velocity.z;
	}

	void Mesh::LimitBoundary(float left, float right, float top, float bottom,
			float back, float front) {
		if (position.x < left || position.x > right) {
			velocity.x *= -1;
		}
		if (position.y < left || position.y > right) {
			velocity.y *= -1;
		}
		if (position.z < left || position.z > right) {
			velocity.z *= -1;
		}
	}
}


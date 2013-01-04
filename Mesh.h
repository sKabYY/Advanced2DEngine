#pragma once

#include "Advanced2D.h"

namespace Advanced2D {
	class Mesh {
	private:
		LPD3DXBUFFER matbuffer;
		DWORD material_count;
		LPD3DXMESH mesh;
		LPD3DXMATERIAL d3dxMaterials;
		D3DMATERIAL9 *materials;
		LPDIRECT3DTEXTURE9 *textures;
		D3DXVECTOR3 position;
		D3DXVECTOR3 velocity;
		D3DXVECTOR3 rotation;
		D3DXVECTOR3 scale;
		D3DXMATRIX matRotate;
		D3DXMATRIX matScale;
		D3DXMATRIX matTranslate;
		D3DXMATRIX matWorld;
	public:
		Mesh();
		~Mesh();
		int GetFaceCount();
		int GetVertexCount();
		bool Load(char *filename);
		void CreateSphere(float radius, int slices, int stacks);
		void CreateCube(float width, float height, float depth);
		void Draw();
		void Transform();
		void Rotate(D3DXVECTOR3 rot);
		void Rotate(float x, float y, float z);
		void Update();
		void LimitBoundary(float left, float right, float top, float bottom,
			float back, float front);
		void SetScale(float x, float y, float z) {
			scale.x = x; scale.y = y; scale.z = z;
		}
		void SetPosition(float x, float y, float z) {
			position.x = x; position.y = y; position.z = z;
		}
		void SetVelocity(float x, float y, float z) {
			velocity.x = x; velocity.y = y; velocity.z = z;
		}
		void SetRotation(float x, float y, float z) {
			rotation.x = x; rotation.y = y; rotation.z = z;
		}
	};
}

#include "DXUT.h"
#include "CameraManager.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::Init()
{
	DEVICE->CreateVertexBuffer(sizeof(VertexType) * 4, D3DUSAGE_WRITEONLY, VertexType::FVF, D3DPOOL_DEFAULT, &m_vb, NULL);
	VertexType* vertices = nullptr;
	m_vb->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].m_position = { -0.5, 0.5, 0 };
	vertices[1].m_position = { 0.5, 0.5, 0 };
	vertices[2].m_position = { -0.5, -0.5, 0 };
	vertices[3].m_position = { 0.5, -0.5, 0 };

	vertices[0].m_uv = { 0, 0 };
	vertices[1].m_uv = { 1, 0 };
	vertices[2].m_uv = { 0, 1 };
	vertices[3].m_uv = { 1, 1 };
	m_vb->Unlock();

	DEVICE->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_ib, NULL);
	WORD idx[] = { 1, 2, 0, 1, 3, 2 };
	void* indices = NULL;
	m_ib->Lock(0, 0, &indices, 0);
	memcpy(indices, idx, sizeof(WORD) * 6);
	m_ib->Unlock();

	DEVICE->SetStreamSource(0, m_vb, 0, sizeof(VertexType));
	DEVICE->SetFVF(VertexType::FVF);
	DEVICE->SetIndices(m_ib);

	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}

void CameraManager::Update()
{
}

void CameraManager::Release()
{
}

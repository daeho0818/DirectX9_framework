#pragma once
class CameraManager : public Singleton<CameraManager>
{
public:
	CameraManager();
	~CameraManager();

	void Init();
	void Update();
	void Release();

private:
	struct VertexType
	{
		Vector3 m_position;
		Vector2 m_uv;
		static constexpr DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
	};

	LPDIRECT3DVERTEXBUFFER9 m_vb;
	LPDIRECT3DINDEXBUFFER9 m_ib;
};


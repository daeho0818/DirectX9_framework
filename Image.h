#pragma once
class Image
{
public:
	Image(LPDIRECT3DTEXTURE9 ptr, D3DXIMAGE_INFO info) : ptr(ptr), info(info) {}
	~Image() {}

	LPDIRECT3DTEXTURE9 ptr = null;
	D3DXIMAGE_INFO info;
};


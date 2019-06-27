#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "Main.h"

class Player;
class _2dobj;
class Billboard;

// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
struct Vertex2D
{
	D3DXVECTOR3 vtx;		// 頂点座標
	float rhw;				// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
	Vertex2D()
	{
		this->rhw = 1.0f;
		this->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
};

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
struct Vertex3D
{
	D3DXVECTOR3 vtx;		// 頂点座標
	D3DXVECTOR3 nor;		// 法線ベクトル
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
	Vertex3D()
	{
		this->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
};

// 三角形ポリゴン用の構造体
struct TriangleStr
{
	D3DXVECTOR3 pos0;
	D3DXVECTOR3 pos1;
	D3DXVECTOR3 pos2;
};

struct Int2D
{
	int x;
	int y;
	Int2D() {};
	Int2D(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

struct Float2D
{
	float x;
	float y;
	Float2D() {};
	Float2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

struct Texture
{
	LPDIRECT3DTEXTURE9 texture;
	const char* path;
	Int2D size;
	Texture() {};
	Texture(const char* path, int x, int y)
	{
		this->texture = NULL;
		this->path = path;
		this->size = Int2D(x, y);
	}
};

struct Slice
{
	int tileID;
	Int2D pos;
	Int2D size;
	Slice() {};
	Slice(int tileID, int x, int y, int w, int h)
	{
		this->tileID = tileID;
		this->pos = Int2D(x, y);
		this->size = Int2D(w, h);
	}
};

#endif

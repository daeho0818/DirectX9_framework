#pragma once
#pragma comment(lib, "dsound.lib")

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <functional>
#include <math.h>

const int WINSIZEX = 1920;
const int WINSIZEY = 1080;

using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;

using std::string;
using std::wstring;
using std::list;
using std::map;
using std::vector;
using std::function;

using std::make_pair;

enum ObjectType
{
	EPlayer,
	EEnemy,
	EP_Bullet,
	EE_Bullet,
	EItem,
	EButton,
	ENone,
} typedef ObjType;

#define DEVICE DXUTGetD3D9Device()
#define DELTA DXUTGetElapsedTime()
#define var auto
#define CENTER Vector2(WINSIZEX / 2, WINSIZEY / 2)

#include "RenderManager.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "CameraManager.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "ParticleManager.h"

#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
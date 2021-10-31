#pragma once
#pragma comment(lib, "dsound.lib")

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <functional>

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

#define DEVICE DXUTGetD3D9Device()
#define DELTA DXUTGetElapsedTime()
#define var auto

#include "RenderManager.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "CameraManager.h"

#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
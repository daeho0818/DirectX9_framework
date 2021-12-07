#include "DXUT.h"
#include "TestEnemy.h"

TestEnemy::TestEnemy(Object* object)
	:Component(object)
{
	OutputDebugStringW(L"생성됐답니다!\n");
}

TestEnemy::~TestEnemy()
{
	OutputDebugStringW(L"뒤졌답니다!\n");
}

void TestEnemy::Init()
{
	renderer = m_object->AddComponent<RendererC>();
	collider = m_object->AddComponent<BoxColliderC>();

	renderer->Setting(IMAGE->FindImage("White"), D3DXCOLOR(0, 0, 1, 1));

	m_object->OnCollisionEnter = [&](Object* other)->void
	{
		if (other->m_type == ObjType::EPlayer || other->m_type == ObjType::EP_Bullet)
			m_object->is_destroy = true;
	};
}

void TestEnemy::Update()
{
	m_object->CheckOut();
}

void TestEnemy::Render()
{
}

void TestEnemy::UIRender()
{
	char str[128];
	sprintf(str, "%f, %f", m_transform->m_position.x, m_transform->m_position.y);
	RENDER->TextRender(str, CENTER);
}

void TestEnemy::Release()
{
}

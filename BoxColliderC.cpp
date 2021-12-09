#include "DXUT.h"
#include "BoxColliderC.h"

BoxColliderC::BoxColliderC(Object* object) : Component(object)
{
}

BoxColliderC::~BoxColliderC()
{
}

void BoxColliderC::Init()
{
	show_collider = false;
}

void BoxColliderC::Update()
{
}

void BoxColliderC::Render()
{
}

void BoxColliderC::UIRender()
{
}

void BoxColliderC::Release()
{
}

void BoxColliderC::ShowCollider(bool active)
{
	show_collider = active;
}

bool BoxColliderC::OBBCheck(TransformC* other_transform)
{
	Vector2 directions[] = { m_transform->right, m_transform->up, other_transform->right, other_transform->up };
	RendererC* other_renderer = other_transform->GetComponent<RendererC>();

	for (int i = 0; i < 4; i++)
		if (!Dotting(directions[i], other_transform, other_renderer)) return false;

	return true;
}

bool BoxColliderC::Dotting(Vector2 direction, TransformC* other_transform, RendererC* other_renderer)
{
	D3DXIMAGE_INFO img1_info = 
		m_object->GetComponent<RendererC>()->GetImage()->info;

	Vector2 obj1_right_distance =
		(img1_info.Width / 2 * m_transform->m_scale) * m_transform->right;

	Vector2 obj1_up_distance =
		(img1_info.Height / 2 * m_transform->m_scale) * m_transform->up;

	float value1 =
		fabs(D3DXVec2Dot(&direction, &obj1_right_distance)) + 
		fabs(D3DXVec2Dot(&direction, &obj1_up_distance));

	D3DXIMAGE_INFO img2_info = other_renderer->GetImage()->info;

	Vector2 obj2_right_distance =
		(img2_info.Width / 2 * other_renderer->m_transform->m_scale) *
		other_transform->right;

	Vector2 obj2_up_distance =
		(img2_info.Height / 2 * other_renderer->m_transform->m_scale) *
		other_transform->up;

	float value2 =
		fabs(D3DXVec2Dot(&direction, &obj2_right_distance)) + 
		fabs(D3DXVec2Dot(&direction, &obj2_up_distance));

	float distance =
		fabs(D3DXVec2Dot(&direction, &(other_transform->m_position - m_transform->m_position)));

	return distance < value1 + value2;
}
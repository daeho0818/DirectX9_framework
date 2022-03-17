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
	show_collider = is_set = false;
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

void BoxColliderC::SetCollider(RendererC* renderer)
{
	D3DXIMAGE_INFO img_info = renderer->GetImage()->info;

	m_width = img_info.Width;
	m_height = img_info.Height;

	is_set = true;
}

void BoxColliderC::SetCollider(float width, float height)
{
	m_width = width;
	m_height = height;

	is_set = true;
}

bool BoxColliderC::OBBCheck(TransformC* other_transform)
{
	Vector2 directions[] = { m_transform->right, m_transform->up, other_transform->right, other_transform->up };
	BoxColliderC* other_collider= other_transform->GetComponent<BoxColliderC>();
	if (!other_collider->enabled) return false;

	for (int i = 0; i < 4; i++)
		if (!Dotting(directions[i], other_collider)) return false;

	return true;
}

bool BoxColliderC::Dotting(Vector2 direction, BoxColliderC* other_collider)
{
	Vector2 obj1_right_vector =
		(m_width / 2 * m_transform->m_localScale.x) * m_transform->right;

	Vector2 obj1_up_vector =
		(m_height / 2 * m_transform->m_localScale.y) * m_transform->up;

	float value1 =
		fabs(D3DXVec2Dot(&direction, &obj1_right_vector)) +
		fabs(D3DXVec2Dot(&direction, &obj1_up_vector));

	Vector2 obj2_right_vector =
		(other_collider->m_width / 2 * other_collider->m_transform->m_localScale.x) *
		other_collider->m_transform->right;

	Vector2 obj2_up_vector =
		(other_collider->m_height / 2 * other_collider->m_transform->m_localScale.y) *
		other_collider->m_transform->up;

	float value2 =
		fabs(D3DXVec2Dot(&direction, &obj2_right_vector)) +
		fabs(D3DXVec2Dot(&direction, &obj2_up_vector));

	float distance =
		fabs(D3DXVec2Dot(&direction, &(other_collider->m_transform->m_position - m_transform->m_position)));

	return distance < value1 + value2;
}
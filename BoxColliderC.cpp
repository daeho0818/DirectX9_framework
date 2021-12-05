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
	m_width = m_height = 0;
	show_collider = false;

	render_c = m_object->GetComponent<RendererC>();
}

void BoxColliderC::Update()
{
}

void BoxColliderC::Render()
{
	//if (show_collider)
	//{
	//	RENDER->CenterRender(IMAGE->FindImage(""), m_transform->m_position);
	//}
}

void BoxColliderC::UIRender()
{
}

void BoxColliderC::Release()
{
}

void BoxColliderC::SetCollider(float width, float height)
{
	m_width = width;
	m_height = height;
}

void BoxColliderC::ShowCollider(bool active)
{
	show_collider = active;
}

bool BoxColliderC::OBBCheck(TransformC* other_transform)
{
	Vector2 directions[] = { m_transform->right, m_transform->up, other_transform->right, other_transform->up };

	bool is_overlap[4] = { false, };
	for (int i = 0; i < 4; i++)
	{
		is_overlap[i] = Dotting(directions[i], other_transform);
	}

	return is_overlap[0] == is_overlap[1] == is_overlap[2] == is_overlap[3];
}

bool BoxColliderC::Dotting(Vector2 direction, TransformC* other_transform)
{
	D3DXIMAGE_INFO img1_info = render_c->GetImage()->info;
	Vector2 obj1_point = img1_info.Width * m_transform->right + img1_info.Height * m_transform->up;

	float value1 = D3DXVec2Dot(&direction, &(obj1_point - m_transform->m_position));

	D3DXIMAGE_INFO img2_info = other_transform->GetComponent<RendererC>()->GetImage()->info;
	Vector2 obj2_point = img2_info.Width * other_transform->right + img2_info.Height * other_transform->up;

	float up_dot = D3DXVec2Dot(&(other_transform->up), &(obj2_point - other_transform->m_position));
	float value2 = D3DXVec2Dot(&direction, &(up_dot * other_transform->up));

	float right_dot = D3DXVec2Dot(&(other_transform->right), &(obj2_point - other_transform->m_position));
	float value3 = D3DXVec2Dot(&direction, &(right_dot * other_transform->up));

	float distance_dot = D3DXVec2Dot(&direction, &(other_transform->m_position - m_transform->m_position));

	return distance_dot <= value1 + value2 + value3;
}

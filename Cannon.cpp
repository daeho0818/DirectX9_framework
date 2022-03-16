#include "DXUT.h"
#include "Cannon.h"

Cannon::Cannon(Object* object)
	: Component(object)
{
}

Cannon::~Cannon()
{
}

void Cannon::Init()
{
	m_object->m_hp = 50;
	m_transform->m_localScale = Vector2(0, 0);
}

void Cannon::Update()
{
	m_object->fire_helper->Update();
}

void Cannon::Render()
{
}

void Cannon::UIRender()
{
}

void Cannon::Release()
{
}

void Cannon::SetCannon(Image* image)
{
	renderer = m_object->AddComponent<RendererC>();
	renderer->SetRenderer(image, D3DXCOLOR(1, 1, 1, 1));

	collider = m_object->AddComponent<BoxColliderC>();
	collider->SetCollider(image->info.Width / 2, image->info.Height / 2);

	m_object->OnCollisionEnter = [&](Object* other) -> void
	{
		if (other->m_type == EP_Bullet)
		{
			m_object->HitAnimation(D3DXCOLOR(1, 0, 0, 1));
			m_object->m_hp--;
		}
	};
	m_object->OnDestroy = [&]()->void
	{
		PARTICLE->AddParticleAnim(IMAGE->MakeAnimation("Explosion"), m_transform->m_position, 0.01f);
	};

	m_object->fire_helper = new	FireHelper();
}

void Cannon::Rotation(Vector2 target_position)
{
	Vector2 direction = target_position - m_transform->m_position;
	D3DXVec2Normalize(&direction, &direction);
	m_transform->m_rotationZ = D3DXToDegree(atan2(direction.y, direction.x)) - 90;
}

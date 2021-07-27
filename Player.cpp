#include "Player.h"
#include "World.h"
#include "BlockWorldCollider.h"

Player::Player(float mass, BoundingBox boundingBox, Collider* collider) :
	RigidBody(mass, boundingBox, collider)
{
	camera = new Camera(position, 150.0f, glm::radians(70.0f), 0.1f, 1000.0f);
}

Player::Player(Camera* camera, float mass, BoundingBox boundingBox, Collider* collider) :
	camera(camera), RigidBody(mass, boundingBox, collider)
{
}

Player::Player(Camera* camera, glm::vec3 position, float mass, BoundingBox boundingBox, Collider* collider) :
	camera(camera), RigidBody(position, mass, boundingBox, collider)
{
}

Player::Player(Camera* camera, glm::vec3 position, glm::vec3 start_velocity, float mass, BoundingBox boundingBox, Collider* collider) :
	camera(camera), RigidBody(position, start_velocity, mass, boundingBox, collider)
{
}

Player::Player(Camera* camera, glm::vec3 position, glm::vec3 start_velocity, glm::mat4 rotation, float mass, BoundingBox boundingBox, Collider* collider) :
	camera(camera), RigidBody(position, start_velocity, rotation, mass, boundingBox, collider)
{
}

void Player::Jump() {
	if (!onGround) {
		return;
	}
	AddForce({ 0.0f, 400.0f, 0.0f }, ForceMode::Acceleration);
	SetOnGround(false);
}

void Player::Move(MoveDirection direction, float speed, bool fly) {
	if (fly)
	{
		switch (direction)
		{
		case MoveDirection::FRONT:
			AddForce(front * speed, ForceMode::Acceleration);
			break;

		case MoveDirection::BACK:
			AddForce(-front * speed, ForceMode::Acceleration);
			break;

		case MoveDirection::RIGHT:
			AddForce(right * speed, ForceMode::Acceleration);
			break;

		case MoveDirection::LEFT:
			AddForce(-right * speed, ForceMode::Acceleration);
			break;
		default:
			break;
		}
	}
	else {
		if (!onGround) {
			switch (direction)
			{
			case MoveDirection::FRONT:
				AddForce(baseFront * speed * 0.001f, ForceMode::Acceleration);
				break;

			case MoveDirection::BACK:
				AddForce(-baseFront * speed * 0.001f, ForceMode::Acceleration);
				break;

			case MoveDirection::RIGHT:
				AddForce(baseRight * speed * 0.001f, ForceMode::Acceleration);
				break;

			case MoveDirection::LEFT:
				AddForce(-baseRight * speed * 0.001f, ForceMode::Acceleration);
				break;
			default:
				break;
			}
		}

		switch (direction)
		{
		case MoveDirection::FRONT:
			AddForce(baseFront * speed, ForceMode::Acceleration);
			break;

		case MoveDirection::BACK:
			AddForce(-baseFront * speed, ForceMode::Acceleration);
			break;

		case MoveDirection::RIGHT:
			AddForce(baseRight * speed, ForceMode::Acceleration);
			break;

		case MoveDirection::LEFT:
			AddForce(-baseRight * speed, ForceMode::Acceleration);
			break;
		default:
			break;
		}
	}
}

void Player::Update() {

	up = camera->GetUpVector();
	right = camera->GetRightVector();
	front = camera->GetFrontVector();

	baseFront = camera->GetBaseFrontVector();
	baseRight = camera->GetBaseRightVector();

	camera->SetPosition(position);
	camera->SetVelocity(velocity);

	for (auto& force : forces) {
		force.ApplyForce(this);
	}
	
	if (onGround) {
		velocity.x = velocity.x * 50.0f * WorldTimer::phys_fdt();
		velocity.z = velocity.z * 50.0f * WorldTimer::phys_fdt();
	}
	else {
		velocity.x = velocity.x * 59.8f * WorldTimer::phys_fdt();
		velocity.z = velocity.z * 59.8f * WorldTimer::phys_fdt();
	}

	velocity.y = velocity.y * 40.9f * WorldTimer::phys_fdt();

	if (fabsf(velocity.x) < 0.00001f) {
		velocity.x = 0.0f;
	}

	if (fabsf(velocity.z) < 0.00001f) {
		velocity.z = 0.0f;
	}

	if (fabsf(velocity.y) < 0.00001f) {
		velocity.y = 0.0f;
	}

	boundingBox.Update(position);

	Force force(glm::vec3(0.0f), ForceMode::Acceleration);

	collider->ApplyNormalForce(this, force, renderer);

	forces.clear();
	forces.shrink_to_fit();
}

void Player::SetCamera(Camera* camera) {
	this->camera = camera;
}

Camera* Player::GetCamera() {
	return camera;
}

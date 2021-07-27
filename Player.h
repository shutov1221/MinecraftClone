#pragma once
#include "RigidBody.h"
#include "Camera.h"

enum class MoveDirection
{
	FRONT,
	BACK,
	RIGHT,
	LEFT
};


class Player : public RigidBody
{
public:
	Player(float mass, BoundingBox boundingBox, Collider* collider);
	Player(Camera* camera, float mass, BoundingBox boundingBox, Collider* collider);
	Player(Camera* camera, glm::vec3 position, float mass, BoundingBox boundingBox, Collider* collider);
	Player(Camera* camera, glm::vec3 position, glm::vec3 start_velocity, float mass, BoundingBox boundingBox, Collider* collider);
	Player(Camera* camera, glm::vec3 position, glm::vec3 start_velocity, glm::mat4 rotation, float mass, BoundingBox boundingBox, Collider* collider);

	void SetCamera(Camera* camera);
	Camera* GetCamera();
	void Jump();
	void Move(MoveDirection direction, float speed, bool fly);

	virtual void Update() override;

private:
	Camera* camera;
};


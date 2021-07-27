#include "BlockWorldCollider.h"

BoundingBox BlockWorldCollider::GetSweptBroadphaseBox(RigidBody* rigidBody) {
	BoundingBox broadphasebox(0.0f);
	auto& velocity = rigidBody->GetVelocity();
	auto& position = rigidBody->GetPosition();
	broadphasebox.minX = velocity.x > 0.0f ? position.x : position.x + velocity.x * WorldTimer::phys_fdt();
	broadphasebox.maxX = velocity.x < 0.0f ? position.x : position.x - velocity.x * WorldTimer::phys_fdt();
	broadphasebox.minY = velocity.y > 0.0f ? position.y : position.y + velocity.y * WorldTimer::phys_fdt();
	broadphasebox.maxY = velocity.y < 0.0f ? position.y : position.y - velocity.y * WorldTimer::phys_fdt();
	broadphasebox.minZ = velocity.z > 0.0f ? position.z : position.z + velocity.z * WorldTimer::phys_fdt();
	broadphasebox.maxZ = velocity.z < 0.0f ? position.z : position.z - velocity.z * WorldTimer::phys_fdt();

	return broadphasebox;
}

void BlockWorldCollider::ApplyNormalForce(RigidBody* rigidBody, Force& force, Renderer* renderer) {
	std::array<bool, 3> result = { false };
	auto& box = rigidBody->GetBoundingBox();
	auto position = rigidBody->GetPosition();
	auto velocity = rigidBody->GetVelocity();
	auto forceVector = force.GetForceVector();
	BoundingBox blockBB(1.0f);
	BoundingBox broadPhaseBox(1.0f);
	Block block;
	float collisionTime = 1.0f;
	float collisionTime_temp;
	
	float normalx = 0.0f, normaly = 0.0f, normalz = 0.0f;
	float normalx_temp = 0.0f, normaly_temp = 0.0f, normalz_temp = 0.0f;

	float x_b = fabsf(2.0f + velocity.x * WorldTimer::phys_fdt());
	float y_b = fabsf(2.0f + velocity.y * WorldTimer::phys_fdt());
	float z_b = fabsf(2.0f + velocity.z * WorldTimer::phys_fdt());


	if (Window::keyboard->IsKeyReleased(GLFW_KEY_P)) {
		auto a = 1;
	}

	for (int z = box.minZ - z_b; z <= box.maxZ + z_b; z += 1.0f) {
		for (int x = box.minX - x_b; x <= box.maxX + x_b; x += 1.0f) {
			for (int y = box.minY - y_b; y <= box.maxY + y_b; y += 1.0f) {
				blockBB.Update({ floorf(x), floorf(y), floorf(z) });
				broadPhaseBox = GetSweptBroadphaseBox(rigidBody);
				//broadPhaseBox.Draw(renderer, { 0.0, 0.0, 0.0 });
				if (AABB(broadPhaseBox, blockBB)) {
					block = World::GetBlock(floorf(x), floorf(y), floorf(z));
					if (block.getBlockType() != BlockType::AirBlock) {
						blockBB.Draw(renderer, { 0.0f, 0.0f, 1.0f });
						collisionTime_temp = SweptAABB(box, blockBB, velocity * WorldTimer::phys_fdt(), normalx_temp, normaly_temp, normalz_temp);

						if (collisionTime_temp < collisionTime) {
							collisionTime = collisionTime_temp;
							normalx = normalx_temp;
							normaly = normaly_temp;
							normalz = normalz_temp;
						}
					}
				}
			}
		}
	}


	float remainingTime = 1.0f - collisionTime;
	float dotprod = 0.0f;


		//std::cout << "normal_x = " << normalx << " normal_y = " << normaly << " normal_z = " << normalz << "      " << "\r" << std::flush;
	position += velocity * collisionTime * WorldTimer::phys_fdt();

	if (remainingTime >= 0.0f) {
		dotprod = glm::dot(velocity, { normalx, normaly, normalz }) * remainingTime;

		if (fabsf(normalz) > 0.000001f) {
			auto a = 1;
			velocity.z = dotprod * normalx;
			//position.z += normalz * 0.0005f;
		}

		if (fabsf(normalx) > 0.000001f) {
			velocity.x = dotprod * normalz;

			//position.x += normalx * 0.0005f;
		}
		
		if (fabsf(normaly) > 0.000001f) {
			rigidBody->SetOnGround(true);
			velocity.y = 0.0f;
			position.y += normaly * 0.005f;
		}

		std::cout << position.x << std::endl;;

		position += velocity * remainingTime * WorldTimer::phys_fdt();
	}




	//std::cout << position.y << std::endl;

	//std::cout << "\tvx = " << velocity.x << "\tvy = " << velocity.y << "\t" << "\tvz = " << velocity.z << "                                                           " << "\r" << std::flush;

	rigidBody->SetPosition(position);
	rigidBody->SetVelocity(velocity);
	force.SetForceVector(forceVector);

}

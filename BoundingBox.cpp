#include "BoundingBox.h"

extern bool AABB(BoundingBox box_1, BoundingBox box_2) {
	return 
		(box_1.minX <= box_2.maxX && box_1.maxX >= box_2.minX) &&
		(box_1.minY <= box_2.maxY && box_1.maxY >= box_2.minY) &&
		(box_1.minZ <= box_2.maxZ && box_1.maxZ >= box_2.minZ);
}

extern float SweptAABB(BoundingBox movable_box, BoundingBox static_box, glm::vec3 velocity, float& normalx, float& normaly, float& normalz) {
	// ��� ���������� ���������� ���������� �� ������ ��� ����� ���������� �������� � ����������� �������� � ����� ������ ����, ����� ���������� ������ "������" � �������������� ������.
	float xDistanceEntry, yDistanceEntry, zDistanceEntry;

	// ��� ���������� ���������� ���������� �� ������ ��� � ����� ������ ����, ����� ���������� ������ "�������" �������������� ������.
	float xDistanceExit, yDistanceExit, zDistanceExit;

	// ������� ���������� ����� ��������� �� ������� � ������� �������� ��� ��� x, ��� � ��� y
	// � ����������� �� ����������� �������� �� ������� ������� ����������, ����� ��������� ���������� ���� (������������� / �������������).
	if (velocity.x > 0.0f)
	{
		xDistanceEntry = static_box.minX - movable_box.maxX;
		xDistanceExit = static_box.maxX - movable_box.minX;
	}
	else
	{
		xDistanceEntry = static_box.maxX - movable_box.minX;
		xDistanceExit = static_box.minX - movable_box.maxX;
	}

	if (velocity.y > 0.0f)
	{
		yDistanceEntry = static_box.minY - movable_box.maxY;
		yDistanceExit = static_box.maxY - movable_box.minY;
	}
	else
	{
		yDistanceEntry = static_box.maxY - movable_box.minY;
		yDistanceExit = static_box.minY - movable_box.maxY;
	}

	if (velocity.z > 0.0f)
	{
		zDistanceEntry = static_box.minZ - movable_box.maxZ;
		zDistanceExit = static_box.maxZ - movable_box.minZ;
	}
	else
	{
		zDistanceEntry = static_box.maxZ - movable_box.minZ;
		zDistanceExit = static_box.minZ - movable_box.maxZ;
	}


	// ��� ���������� ���������� �����, � ������� ���������� ������ ������ / ������ �� ������������ �������.
	float xEntryTime, yEntryTime, zEntryTime;
	float xExitTime, yExitTime, zExitTime;


	// ������� ����� ������������ � ����� ����� ��� ������ ��� (���� ���������� ��������� ������� �� ����)
	if (velocity.x == 0.0f)
	{

		// ���� ���������� ���������� (���� ��� �����) ����� ����� ��������� ������, ��� ������ ����� �������� ������ ������, �� ������� ���� �� ������������.
		if (std::max(fabsf(xDistanceEntry), fabsf(xDistanceExit)) > ((movable_box.maxX - movable_box.minX) + (static_box.maxX - static_box.minX)))
		{

			// ��������� ����� �������� �� 2.0f ������� ���������� ������������ ����� � ���� �������.
			xEntryTime = 2.0f;
		}
		else
		{

			// � ��������� ������ �������� ������������� �������������, ����� ������������ ��� ����������.
			xEntryTime = -std::numeric_limits<float>::infinity();
		}


		// ��������� ����� ��������� �� ������������� ������������� ���������� ��� ����������.
		xExitTime = std::numeric_limits<float>::infinity();
	}
	else
	{

		// ���� ���� �������� �� ��� x, �� �� ����� ���������� ����� ������������ �� ������ ����������, ��������� �� ��������. (�����������, ��� �������� �� ��������.)
		xEntryTime = xDistanceEntry / velocity.x;
		xExitTime = xDistanceExit / velocity.x;
	}

	if (velocity.y == 0.0f)
	{
		if (std::max(fabsf(yDistanceEntry), fabsf(yDistanceExit)) > ((movable_box.maxY - movable_box.minY) + (static_box.maxY - static_box.minY)))
		{
			yEntryTime = 2.0f;
		}
		else
		{
			yEntryTime = -std::numeric_limits<float>::infinity();
		}

		yExitTime = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntryTime = yDistanceEntry / velocity.y;
		yExitTime = yDistanceExit / velocity.y;
	}

	if (velocity.z == 0.0f)
	{
		if (std::max(fabsf(zDistanceEntry), fabsf(zDistanceExit)) > ((movable_box.maxZ - movable_box.minZ) + (static_box.maxZ - static_box.minZ)))
		{
			zEntryTime = 2.0f;
		}
		else
		{
			zEntryTime = -std::numeric_limits<float>::infinity();
		}

		zExitTime = std::numeric_limits<float>::infinity();
	}
	else
	{
		zEntryTime = zDistanceEntry / velocity.z;
		zExitTime = zDistanceExit / velocity.z;
	}


	// �������� ������������ ����� ����� ��� ����������� ���������� ������������, ������� �� ����� ���� ���������� ��� ������������ ��������. (������ ��� ��� 3 ��� ������ �����������.)
	float entryTime = std::max(std::max(xEntryTime, yEntryTime), zEntryTime);


	// �������� ����������� ����� ������, ����� ����������, ����� ������� ������ �� ������������. (����� ������� ��������� ���� ����� �����.)
	float exitTime = std::min(std::min(xExitTime, yExitTime), zExitTime);

	// ���� ���-���� � ��������� ����������� �������, �������� ���.
	// ���� entryTime > exitTime, ��� ��������, ��� ���� �� ���� ������� �� �������������� �� ����, ��� ������ ��� ������������, ������� ��� �� ���������� ������ ������������ � ������������ ���.
	// ���� ��� ��� ������� ����� ������ ����, �� �������� ��� ��������� (��� �� �� ����������, �� � ����� ������ ..)
	// ���� �����-���� ����� ����� ������ 1.0f, �� �� ���� ����� ���������� / ������ ������������ �� ����������, ������� �� ���������.
	if (entryTime > exitTime || xEntryTime < 0.0f && yEntryTime < 0.0f && zEntryTime < 0.0f || xEntryTime > 1.0f || yEntryTime > 1.0f || zEntryTime > 1.0f)
	{

		// ��� ���������� ������������ �������� ������� � �������� ����������.
		normalx = 0.0f;
		normaly = 0.0f;
		normalz = 0.0f;

		// ���� ����������� ������������ �� ��������, ���������� ����������������� �������� if � ��������� ����� �������� �� ��������� std :: cout.
		// ����� �� ������ ��������� �������� ���������� � ���� ���������, ����� ���������, ��� ��� � �������.
		/*if (glm::distance(movable_box.GetPosition (), static_box.GetPosition ()) < 0.1)
		{
			std::cout << "something wrong.";
		}*/

		// 2.0f ��������, ��� ������������ �� ����.
		return 2.0f;
	}
	else  // ���� ��������� ������������
	{
		// ��������� ������� �������������� �����������
		if (xEntryTime > yEntryTime && xEntryTime > zEntryTime) // ���� ��� x ������������ ���������, �� ��� ��� ������������.
		{
			if (xDistanceEntry < 0.0f) // ���������� ������� �� ������ �������������� ��� ��������������.
			{
				normalx = 1.0f;
				normaly = 0.0f;
				normalz = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
				normalz = 0.0f;
			}
		}
		else if (yEntryTime > xEntryTime && yEntryTime > zEntryTime)
		{
			if (yDistanceEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
				normalz = 0.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
				normalz = 0.0f;
			}
		}
		else if (zEntryTime > xEntryTime && zEntryTime > yEntryTime)
		{
			if (zDistanceEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 0.0f;
				normalz = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = 0.0f;
				normalz = -1.0f;
			}
		}

		// ���������� ����� ������������
		return entryTime;
	}
}
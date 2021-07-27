#include "BoundingBox.h"

extern bool AABB(BoundingBox box_1, BoundingBox box_2) {
	return 
		(box_1.minX <= box_2.maxX && box_1.maxX >= box_2.minX) &&
		(box_1.minY <= box_2.maxY && box_1.maxY >= box_2.minY) &&
		(box_1.minZ <= box_2.maxZ && box_1.maxZ >= box_2.minZ);
}

extern float SweptAABB(BoundingBox movable_box, BoundingBox static_box, glm::vec3 velocity, float& normalx, float& normaly, float& normalz) {
	// Эти переменные обозначают расстояние по каждой оси между движущимся объектом и неподвижным объектом с точки зрения того, когда движущийся объект "войдет" в сталкивающийся объект.
	float xDistanceEntry, yDistanceEntry, zDistanceEntry;

	// Эти переменные обозначают расстояние по каждой оси с точки зрения того, когда движущийся объект "покинет" сталкивающийся объект.
	float xDistanceExit, yDistanceExit, zDistanceExit;

	// Находим расстояние между объектами на ближней и дальней сторонах как для x, так и для y
	// В зависимости от направления скорости мы изменим порядок вычислений, чтобы сохранить правильный знак (положительный / отрицательный).
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


	// Эти переменные обозначают время, в которое движущийся объект войдет / выйдет из неподвижного объекта.
	float xEntryTime, yEntryTime, zEntryTime;
	float xExitTime, yExitTime, zExitTime;


	// Находим время столкновения и время ухода для каждой оси (если инструкция запрещает деление на ноль)
	if (velocity.x == 0.0f)
	{

		// Если наибольшее расстояние (вход или выход) между двумя объектами больше, чем размер обоих объектов вместе взятых, то объекты явно не сталкиваются.
		if (std::max(fabsf(xDistanceEntry), fabsf(xDistanceExit)) > ((movable_box.maxX - movable_box.minX) + (static_box.maxX - static_box.minX)))
		{

			// Установка этого значения на 2.0f вызовет отсутствие столкновения позже в этой функции.
			xEntryTime = 2.0f;
		}
		else
		{

			// В противном случае передаем отрицательную бесконечность, чтобы игнорировать эту переменную.
			xEntryTime = -std::numeric_limits<float>::infinity();
		}


		// Установка этого параметра на положительную бесконечность игнорирует эту переменную.
		xExitTime = std::numeric_limits<float>::infinity();
	}
	else
	{

		// Если есть скорость по оси x, то мы можем определить время столкновения на основе расстояния, деленного на скорость. (Предполагая, что скорость не меняется.)
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


	// Получаем максимальное время входа для определения последнего столкновения, которое на самом деле происходит при столкновении объектов. (Потому что все 3 оси должны столкнуться.)
	float entryTime = std::max(std::max(xEntryTime, yEntryTime), zEntryTime);


	// Получить минимальное время выхода, чтобы определить, когда объекты больше не сталкиваются. (ИНАЧЕ объекты проходили друг через друга.)
	float exitTime = std::min(std::min(xExitTime, yExitTime), zExitTime);

	// Если что-либо в следующем утверждении истинно, коллизии нет.
	// Если entryTime > exitTime, это означает, что одна из осей выходит из «столкновения» до того, как другие оси пересекаются, поэтому они не пересекают объект одновременно и столкновения нет.
	// Если все три времени входа меньше нуля, то коллизия уже произошла (или мы ее пропустили, но в любом случае ..)
	// Если какое-либо время входа больше 1.0f, то на этом этапе обновления / физики столкновения не происходит, поэтому мы продолжим.
	if (entryTime > exitTime || xEntryTime < 0.0f && yEntryTime < 0.0f && zEntryTime < 0.0f || xEntryTime > 1.0f || yEntryTime > 1.0f || zEntryTime > 1.0f)
	{

		// При отсутствии столкновений передаем нормали с нулевыми значениями.
		normalx = 0.0f;
		normaly = 0.0f;
		normalz = 0.0f;

		// Если обнаружение столкновений не работает, попробуйте раскомментировать оператор if и поставить точку останова на операторе std :: cout.
		// Затем вы можете проверить значения переменных в этом алгоритме, чтобы убедиться, что все в порядке.
		/*if (glm::distance(movable_box.GetPosition (), static_box.GetPosition ()) < 0.1)
		{
			std::cout << "something wrong.";
		}*/

		// 2.0f означает, что столкновения не было.
		return 2.0f;
	}
	else  // Если произошло столкновение
	{
		// Вычислить нормаль сталкивающейся поверхности
		if (xEntryTime > yEntryTime && xEntryTime > zEntryTime) // Если ось x пересекается последней, то это ось столкновения.
		{
			if (xDistanceEntry < 0.0f) // Определяем нормаль на основе положительного или отрицательного.
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

		// Возвращаем время столкновения
		return entryTime;
	}
}
#pragma once

class WorldTimer {
public:
	static void CreateClock();
	static void Update();

	static double dt();
	static float fdt();
	static double phys_dt();
	static float phys_fdt();
	static double time();
	static float ftime();

private:
	WorldTimer();
	static WorldTimer* worldTimer;
	static double _dt;
	static double physics_dt;
	static double lastFrameTime;
	static double currentTime;
};

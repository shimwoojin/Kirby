#pragma once
#include"ISubSystem.h"

class Timer final : public ISubSystem
{
public:
	Timer(class Context* const context);
	~Timer() = default;

	virtual bool Initialize() override;
	virtual void Update() override;

	const float GetDeltaTimeMS() { return static_cast<float>(delta_time_ms); }
	const float GetDeltaTimeSEC() { return static_cast<float>(delta_time_ms / 1000); }

private:
	double delta_time_ms = 0.0;
	std::chrono::time_point<std::chrono::high_resolution_clock> previous_time;

};

class StopWatch final
{
public:
	StopWatch();
	~StopWatch() = default;

	void Start();

	const float GetElapsedTimeSec();
	const float GetElapsedTimeMs();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

};


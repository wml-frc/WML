#include "loops/LoopSystem.h"

#include <frc/Timer.h>

using namespace wml::loops;

void LoopSystem::UpdateOnce() {
  double dt = frc::Timer::GetFPGATimestamp().value() - _lastNotifierCall;
  Update(dt);
  _lastNotifierCall = frc::Timer::GetFPGATimestamp().value();
}

void LoopSystem::StartLoop(unsigned int hz) {
  _lastNotifierCall = frc::Timer::GetFPGATimestamp().value();
  _notifier.StartPeriodic((units::second_t)(1.0 / hz));
  _notifierRunning = true;
}

bool LoopSystem::IsLoopRunning() {
  return _notifierRunning;
}
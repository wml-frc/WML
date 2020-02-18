#include "loops/UpdateGroup.h"

using namespace wml::loops;

void UpdateGroup::Register(LoopSystem *loopSystem, bool dtPriority) {
  if (dtPriority) Register(std::bind(&LoopSystem::UpdateOnce, loopSystem));
  else Register(std::bind(&LoopSystem::Update, loopSystem, _dt));
}

void UpdateGroup::Register(std::function<void(double)> func) {
  _funcs.push_back(func);
}

void UpdateGroup::Update(double dt) {
  for (auto func : _funcs) func(dt);
}

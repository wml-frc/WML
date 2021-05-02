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


void UpdateGroup::operator()() { UpdateOnce(); }
void UpdateGroup::operator()(double dt) { Update(dt); }

UpdateGroup& UpdateGroup::operator+=(LoopSystem *rhs) { Register(rhs); return *this; }
UpdateGroup& UpdateGroup::operator+=(std::function<void(double)> rhs) { Register(rhs); return *this; }

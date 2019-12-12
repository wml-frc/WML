#include "drivebase/modules/Module.h"

using namespace wml::drivebase::modules;


void Module::Set(double power, double heading) {
  if (_move != nullptr) _move->Set(power);
  if (heading != INFINITY) SetDirection(heading);
}

void Module::Set(std::pair<double, double> pair) {
  Set(pair.first, pair.second);
}

void Module::SetDirection(double heading) {
  if (_turn != nullptr) _turn->SetDirection(heading);
}


wml::Mount Module::GetMount() {
  return _mount;
}

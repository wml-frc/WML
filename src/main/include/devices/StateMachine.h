#pragma once

#include <string>

#include "Devices/StateDevice.h"

namespace wml {
  namespace devices {
    class StateMachine : public StateDevice {
     public:
      StateMachine(std::string name = "<State Machine>") : StateDevice(name) {};
    };
  } // ns devices
} // ns wml

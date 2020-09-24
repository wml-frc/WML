#pragma once

#include <functional>
#include <map>
#include <string>

#include "Named.h"
#include "devices/State.h"

namespace wml {
  namespace devices {
    struct StateConnection {
      State *originalState;
      State *finalState;
      SDFunc<bool> func;
    };

    class StateDevice : public Named {
     public:
      StateDevice(std::string name) : Named(name) {};

      // ret false if fails
      bool AddState(State *state);
      bool AddConnection(StateConnection connection);

     protected:
      std::map<State*, State*> _states;
      std::map<State*, std::map<State*, SDFunc<bool>>> _stateConnections; // state -> state -> bool()
    };
  }  // ns devices
}  // ns wml

#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "Named.h"
#include "devices/State.h"

namespace wml {
  namespace devices {
    class StateDevice : public Named {
     public:
      StateDevice(std::string name = "<State Device>") : Named(name) {};

      struct StateConnection {
        State *originalState;
        State *finalState;
        SDFunc<bool> func;

        StateConnection(State *originalState, State *finalState, SDFunc<bool> func) :
          originalState(originalState),
          finalState(finalState),
          func(func) {};
      };

      bool AddState(State *state);
      std::vector<bool> AddState(std::vector<State*> states);

      bool AddConnection(StateConnection connection);
      std::vector<bool> AddConnection(std::vector<StateConnection> connections);


      // statics - i.e. common connections
      static std::vector<StateConnection> DualConnection(State *a, State *b, SDFunc<bool> onChange);

     protected:
      std::map<State*, State*> _states;
      std::map<State*, std::map<State*, SDFunc<bool>>> _stateConnections; // state -> state -> bool()
    };
  }  // ns devices
}  // ns wml

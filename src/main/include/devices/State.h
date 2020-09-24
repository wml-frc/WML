#pragma once

#include <functional>
#include <string>

#include "Named.h"

namespace wml {
  namespace devices {
    class StateDevice;
    template <typename R> using SDFunc = std::function<R(StateDevice&)>;

    class State : public Named {
     public:
      State(std::string name = "<State>", SDFunc<void> onEnterFunc = SDFunc<void>(), SDFunc<void> onExitFunc = SDFunc<void>()) :
        Named(name),
        _onEnterFunc(onEnterFunc),
        _onExitFunc(onExitFunc) {};

      SDFunc<void> GetOnEnterFunc() { return _onEnterFunc; };
      SDFunc<void> GetOnExitFunc() { return _onExitFunc; };

     protected:
      SDFunc<void> _onEnterFunc;
      SDFunc<void> _onExitFunc;
    };
  }  // ns devices
}  // ns wml

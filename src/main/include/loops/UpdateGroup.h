#pragma once

#include <functional>
#include <vector>

#include "loops/LoopSystem.h"

namespace wml {
  namespace loops {
    static auto _dt = std::placeholders::_1;

    class UpdateGroup : public LoopSystem {
     public:
      void Register(LoopSystem *loopSystem, bool dtPriority = false);
      void Register(std::function<void(double)> func);

      virtual void Update(double dt) override;

     private:
      std::vector<std::function<void(double)>> _funcs;
    };
  } // ns loops
} // ns wml

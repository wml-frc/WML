#pragma once

#include <cmath>
#include <utility>

#include "Mount.h"
#include "drivebase/modules/ModuleMove.h"
#include "drivebase/modules/ModuleTurn.h"

namespace wml {
  namespace drivebase {
    namespace modules {
      class Module {    // maybe StateDevice ? (e.g. SwerveModule)
       public:
        Module(Mount mount, ModuleMove *move, ModuleTurn *turn) : _mount(mount), _move(move), _turn(turn) {};

        void Set(double power, double heading = INFINITY);
        void Set(std::pair<double, double> pair); // power, heading
        void SetDirection(double heading);

        Mount GetMount();

       private:
        Mount _mount;
        ModuleMove *_move;
        ModuleTurn *_turn;
      };
    }
  }
}

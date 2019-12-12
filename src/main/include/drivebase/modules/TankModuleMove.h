#pragma once

#include <string>

#include "drivebase/modules/ModuleMove.h"
#include "Gearbox.h"

namespace wml {
  namespace drivebase {
    namespace modules {
      class TankModuleMove : public ModuleMove {
      public:
        TankModuleMove(Gearbox &gearbox, bool inverted = false, std::string name = "<TankModuleMove>") : ModuleMove(inverted, name), _gearbox(gearbox) {};

      protected:
        Gearbox &_gearbox;

        virtual void OnManual(double setpoint) override;
        virtual void OnIdle() override;

        virtual void OnInversion(bool newInversion) override;
      };
    }
  }
}

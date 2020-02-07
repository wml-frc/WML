#pragma once

#include <string>

#include <networktables/NetworkTable.h>

#include "controllers/Inputs.h"
#include "NTUtil/Slave.h"

namespace wml {
  namespace controllers {
    namespace inputs {
      class NTButton : public ContButton {
       public:
        NTButton(std::string name, std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("NTInputs")) : buttonSlave(table, name, &buttonBool) {};

        virtual bool Get() override { return buttonBool; };
      
       private:
        bool buttonBool = false;
        NTUtil::Slave<bool> buttonSlave;
      };

      class NTAxis : public ContAxis {
       public:
        NTAxis(std::string name, std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("NTInputs")) : axisSlave(table, name, &axisDouble) {};

        virtual double Get() override { return std::fabs(axisDouble) > 1 ? copysign(1.0, axisDouble) : axisDouble; };
      
       private:
        double axisDouble = false;
        NTUtil::Slave<double> axisSlave;
      };
    } // ns inputs
  } // ns controllers
} // ns wml

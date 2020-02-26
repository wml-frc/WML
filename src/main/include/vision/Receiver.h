#pragma once

#include <string>

#include "networktables/NetworkTableInstance.h"

#include "NTUtil/Slave.h"

namespace wml {
  namespace vision {
    struct Receiver {
      Receiver(std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("VisionTracking")) : _xOffset(table, "Target_X", &xOffset), _yOffset(table, "Target_Y", &yOffset) {}

      double xOffset;
      double yOffset;

     private:
      wml::NTUtil::Slave<double> _xOffset, _yOffset;
    };
  }
}

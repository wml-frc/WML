#pragma once

#include <string>

#include "networktables/NetworkTableInstance.h"

#include "NTUtil/Slave.h"

namespace wml {
  namespace vision {
    struct Receiver {
      Receiver(std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("VisionTracking")) : _ex(table, "offsetX", &ex), _ey(table, "offsetY", &ey), _RES_HEIGHT(table, "RES_HEIGHT", &RES_HEIGHT), _RES_WIDTH(table, "RES_WIDTH", &RES_WIDTH) {};

      double ex, ey;
      double RES_HEIGHT, RES_WIDTH;

      virtual double GetHorizontalDegrees() { // returns -30 left, 30 right
        return 60 * ex / RES_HEIGHT; // Camera FOV is about 60 deg; should probs have this in config. Also division is a good enough approx for +-30 deg.
      };

     private:
      wml::NTUtil::Slave<double> _ex, _ey;
      wml::NTUtil::Slave<double> _RES_HEIGHT, _RES_WIDTH;
    };
  }
}

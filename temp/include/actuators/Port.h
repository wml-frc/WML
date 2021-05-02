#pragma once

namespace wml {
  namespace actuators {
    struct Port {
     public:
      int _CAN;
      int _PDP = -1;

      operator int() { return this->_CAN; };
      Port(int n) { _CAN = n; };
    };
  } // namespace actuators
} // namespace wml

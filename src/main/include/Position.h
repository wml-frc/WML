#pragma once

#include <tuple>


namespace wml {
  using __POSITION_TYPE__ = double;
  using Position = std::tuple<__POSITION_TYPE__, __POSITION_TYPE__, __POSITION_TYPE__>;
}

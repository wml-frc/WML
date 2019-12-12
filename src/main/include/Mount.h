#pragma once

#include <utility>

#include "Position.h"

namespace wml {
  struct Mount {
    Position pos;
    std::pair<__POSITION_TYPE__, __POSITION_TYPE__> direction;    // horizontal, vertical

    Mount(Position pos, std::pair<__POSITION_TYPE__, __POSITION_TYPE__> direction) : pos(pos), direction(direction) {};
    Mount(std::pair<__POSITION_TYPE__, __POSITION_TYPE__> pos, __POSITION_TYPE__ direction) : pos({ pos.first, 0, pos.second }), direction({ direction, 0 }) {};
  };
}

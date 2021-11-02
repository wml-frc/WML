#pragma once


#include "MotionProfiler/Profiler/SplineUtil.h"

namespace wml {
namespace MotionProfiler {
namespace Profiler {
namespace Modifiers {
	struct Tank {
		static void modify_tank(std::vector<Segment> original, std::vector<Segment> &left_traj, std::vector<Segment> &right_traj, double wheelbase_width);
	};
} // modifiers
} // profiler
} // mp
} // wml
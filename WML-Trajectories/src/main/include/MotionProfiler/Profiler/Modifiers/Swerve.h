#pragma once


#include "MotionProfiler/Profiler/SplineUtil.h"

namespace wml {
namespace MotionProfiler {
namespace Profiler {
namespace Modifiers {
	struct Swerve {
		static void modify_swerve(std::vector<Segment> original, std::vector<Segment> &fl, std::vector<Segment> &fr, std::vector<Segment> &bl, std::vector<Segment> &br, double wheelbase_width, double wheelbase_depth);
	};
} // modifiers
} // profiler
} // mp
} // wml
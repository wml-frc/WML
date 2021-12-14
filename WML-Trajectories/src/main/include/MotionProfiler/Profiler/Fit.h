#pragma once

#include "MotionProfiler/Profiler/SplineUtil.h"

namespace wml {
namespace MotionProfiler {
namespace Profiler {
	struct Fit {
		enum class Type {
			HERMITE_PRE = 0,
			HERMITE_CUBIC,
			HERMITE_QUINTIC
		};
		
		static void fit_hermite_pre(Waypoint a, Waypoint b, Spline *s);
		static void fit_hermite_cubic(Waypoint a, Waypoint b, Spline *s);
		static void fit_hermite_quintic(Waypoint a, Waypoint b, Spline *s);

	};
} // profiler
} // mp
} // wml
#pragma once

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323
#endif

#ifndef TAU
#define TAU M_PI*2
#endif

namespace wml {
namespace MotionProfiler {
namespace Profiler {

	/**
	 * Math Utility for profiler
	 */
	struct MathUtil {
		static double min(double a, double b) {
			return (((a)<(b))?(a):(b));
		}

		static double max(double a, double b) {
			return (((a)>(b))?(a):(b));
		}

		static double r2d(double rad) {
			return rad * 180 / M_PI;
		}

		static double d2r(double deg) {
			return deg * M_PI / 180;
		}

		static double boundRadians(double angle) {
			double newAngle = fmod(angle, TAU);
			if (newAngle < 0) {
				newAngle = TAU + newAngle;
			}

			return newAngle;
		}
	};
} // profiler
} // mp
} // wml
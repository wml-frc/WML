#pragma once

#include "MotionProfiler/Profiler/SplineUtil.h"
#include "MotionProfiler/Profiler/MathUtil.h"

namespace wml {
namespace MotionProfiler {
namespace Profiler {

	/**
	 * Spline control functions
	 */
	struct SplineControl {
		/**
		 * Sample Speed
		 */
		struct Samples {
			static constexpr int kFast = 1000;
			static constexpr int kLow = kFast*10;
			static constexpr int kHigh = kLow*10;
		};

		/**
		 * Return Spline coords from percentage
		 */
		static Coord spline_coords(Spline s, double percentage);

		/**
		 * Return derivitive from percentage
		 */
		static double spline_deriv(Spline s, double percentage);

		/**
		 * Return derivitive from points
		 */
		static double spline_deriv_2(double a, double b, double c, double d, double e, double k, double p);

		/**
		 * Return spline angle from percentage
		 */
		static double spline_angle(Spline s, double percentage);

		/**
		 * return distance of spline
		 */
		static double spline_distance(Spline *s, int sample_count);

		/**
		 * Return progress
		 */
		static double spline_progress_for_distance(Spline s, double distance, int sample_count);
	};

} // profiler
} // mp
} // wml
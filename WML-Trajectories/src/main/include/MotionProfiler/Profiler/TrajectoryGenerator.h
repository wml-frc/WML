#pragma once

#include "SplineUtil.h"
#include "Fit.h"
#include "MathUtil.h"
#include "SplineControl.h"
#include <vector>

namespace wml {
namespace MotionProfiler {
namespace Profiler {

	/**
	 * Trajectory Generator
	 * prepare and create trajectories from waypoints and spline segments
	 */
	class TrajectoryGenerator {
	 public:
		/**
		 * Prepare a trajectory
		 */
		static int prepare(const std::vector<Waypoint> points, Fit::Type type, int sample_count, double dt, double max_velocity, double max_acceleration, double max_jerk, std::shared_ptr<Trajectory> traj);

		/**
		 * Generate trajectory
		 */
		static int generate(std::shared_ptr<Trajectory> traj, std::vector<Segment> &segments);

	 private:
		static void trajectory_copy(std::vector<Segment> src, std::vector<Segment> &dest);
		static TrajectoryInfo trajectory_prepare(TrajectoryConfig config);
		static int trajectory_fromSecondOrderFilter(int filter_1_l, int filter_2_l, double dt, double u, double v, double impulse, int len, std::vector<Segment> &seg);
		static int trajectory_create(TrajectoryInfo info, TrajectoryConfig config, std::vector<Segment> &seg);
	};

} // profiler
} // mp
} // wml
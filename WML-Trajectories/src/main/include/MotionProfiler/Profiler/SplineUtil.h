#pragma once

#include <memory>
#include <vector>

namespace wml {
namespace MotionProfiler {
namespace Profiler {

	/**
	 * WayPoint
	 * X and Y coords with an angle
	 */
	struct Waypoint {
		double x,y,angle;
	};

	/**
	 * Coordinates X,Y
	 */
	struct Coord {
		double x, y;
	};

	/**
	 * Complete spline structure
	 */
	struct Spline {
		double a,b,c,d,e;
		double x_offset, y_offset, angle_offset, knot_distance, arc_length;
	};

	/**
	 * Segment along a spline
	 */
	struct Segment {
		double dt, x, y, position, velocity, acceleration, jerk, heading;
	};

	/**
	 * Trajectory Configuration
	 */
	struct TrajectoryConfig {
		double dt, max_v, max_a, max_j, src_v, src_theta, dest_pos, dest_v, dest_theta;
		int sample_count;
	};

	/**
	 * Trajectory Information container
	 */
	struct TrajectoryInfo {
		int filter1, filter2, length;
		double dt, u, v, impulse;
	};

	/**
	 * Main Trajectory
	 */
	struct Trajectory {
		std::vector<Spline> saptr;
		std::vector<double> laptr;
		double totalLength;
		int length;
		int path_length;
		TrajectoryInfo info;
		TrajectoryConfig config;
	};

} // profiler
} // mp
} // wml
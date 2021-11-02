#include "MotionProfiler/Profiler/TrajectoryGenerator.h"

namespace wml {
namespace MotionProfiler {
namespace Profiler {
	int TrajectoryGenerator::prepare(const std::vector<Waypoint> points, Fit::Type type, int sample_count, double dt, double max_velocity, double max_acceleration, double max_jerk, std::shared_ptr<Trajectory> traj) {
		if (points.size() < 2) {
			return -1;
		}

		traj->saptr.resize(points.size()-1);
		traj->laptr.resize(points.size()-1);

		double totalLength = 0;

		for (size_t i = 0; i < points.size()-1; i++) {
			Spline s;
			switch(type) {
				case Fit::Type::HERMITE_PRE:
					Fit::fit_hermite_pre(points[i], points[i+1], &s);
					break;

				case Fit::Type::HERMITE_CUBIC:
					Fit::fit_hermite_cubic(points[i], points[i+1], &s);
					break;

				case Fit::Type::HERMITE_QUINTIC:
					Fit::fit_hermite_quintic(points[i], points[i+1], &s);
					break;

				default:
					Fit::fit_hermite_cubic(points[i], points[i+1], &s);
					break;
			}
			double dist = SplineControl::spline_distance(&s, sample_count);
			traj->saptr[i] = s;
			traj->laptr[i] = dist;
			totalLength += dist;
		}

		TrajectoryConfig config = {dt, max_velocity, max_acceleration, max_jerk, 0, points[0].angle, totalLength, 0, points[0].angle, sample_count};
		TrajectoryInfo info = trajectory_prepare(config);
		int trajectory_length = info.length;
		
		traj->totalLength = totalLength;
		traj->length = trajectory_length;
		traj->path_length = points.size();
		traj->info = info;
		traj->config = config;
		
		return trajectory_length;
	}
} // profiler
} // mp
} // wml
#pragma once

#include "MotionProfiler/Profiler/SplineControl.h"

namespace wml {
namespace MotionProfiler {
namespace Profiler {
namespace Followers {
	struct DistanceConfig {
		double kp, ki, kd, kv, ka;
	};

	struct DistanceFollowerContainer {
		double last_error, heading, output;
		int segment, finished;
	};

	struct DistanceFollower {
		static double followerDistance(DistanceConfig c, std::shared_ptr<DistanceFollowerContainer> follower, std::vector<Segment> trajectory, double distance);
		static double followerDistance2(DistanceConfig c, std::shared_ptr<DistanceFollowerContainer> follower, Segment segment, int trajectory_length, double distance);
	};
} // followers
} // profiler
} // mp
} // wml
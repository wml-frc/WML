#include "MotionProfiler/Profiler/Followers/DistanceFollower.h"

namespace wml {
namespace MotionProfiler {
namespace Profiler {
namespace Followers {

	double DistanceFollower::followerDistance(DistanceConfig c, std::shared_ptr<DistanceFollowerContainer> follower, std::vector<Segment> trajectory, double distance) {
		size_t segment = follower->segment;
		if (segment >= trajectory.size()) {
			follower->finished = 1;
			follower->output = 0.0;
			Segment last = trajectory[trajectory.size() - 1];
			follower->heading = last.heading;
			return 0.0;
		} else {
			return followerDistance2(c, follower, trajectory[segment], trajectory.size(), distance);
		}
	}

	double DistanceFollower::followerDistance2(DistanceConfig c, std::shared_ptr<DistanceFollowerContainer> follower, Segment segment, int trajectory_length, double distance) {
		if (follower->segment < trajectory_length) {
			follower->finished = 0;
			double error = segment.position - distance;
			double calculated_value = c.kp * error + c.kd * ((error - follower->last_error) / segment.dt) + (c.kv * segment.velocity + c.ka * segment.acceleration);

			follower->last_error = error;
			follower->heading = segment.heading;
			follower->output = calculated_value;
			follower->segment = follower->segment + 1;
			return calculated_value;
		} else {
			follower->finished = 1;
			return 0.0;
		}
	}

} // followers
} // profiler
} // mp
} // wml
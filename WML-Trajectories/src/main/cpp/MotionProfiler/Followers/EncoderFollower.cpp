#include "MotionProfiler/Profiler/Followers/EncoderFollower.h"

namespace wml {
namespace MotionProfiler {
namespace Profiler {
namespace Followers {
	double EncoderFollower::followerEncoder(EncoderConfig c, std::shared_ptr<EncoderFollowerContainer> follower, std::vector<Segment> trajectory, int encoder_tick) {
		size_t segment = follower->segment;
		if (segment >= trajectory.size()) {
			follower->finished = 1;
			follower->output = 0.0;
			Segment last = trajectory[trajectory.size() - 1];
			follower->heading = last.heading;
			return 0.0;
    } else {
      return followerEncoder2(c, follower, trajectory[segment], trajectory.size(), encoder_tick);
    }
	}

	double EncoderFollower::followerEncoder2(EncoderConfig c, std::shared_ptr<EncoderFollowerContainer> follower, Segment segment, int trajectory_length, int encoder_tick) {
		double distance_covered = ((double)encoder_tick - (double)c.initial_position) /  ((double)c.ticks_per_revolution);
		distance_covered = distance_covered * c.wheel_circumference;

		if (follower->segment < trajectory_length) {
			follower->finished = 0;
			double error = segment.position - distance_covered;
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
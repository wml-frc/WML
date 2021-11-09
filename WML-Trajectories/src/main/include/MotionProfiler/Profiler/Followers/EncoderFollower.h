#pragma once

#include "MotionProfiler/Profiler/SplineControl.h"

namespace wml {
namespace MotionProfiler {
namespace Profiler {
namespace Followers {
	struct EncoderConfig {
		int initial_position, ticks_per_revolution;
		double wheel_circumference;
		double kp, ki, kd, kv, ka;
	};

	struct EncoderFollowerContainer {
		double last_error, heading, output;
		int segment, finished;
	};

	struct EncoderFollower {
		static double followerEncoder(EncoderConfig c, std::shared_ptr<EncoderFollowerContainer> follower, std::vector<Segment> trajectory, int encoder_tick);
		static double followerEncoder2(EncoderConfig c, std::shared_ptr<EncoderFollowerContainer> follower, Segment segment, int trajectory_length, int encoder_tick);
	};
} // followers
} // profiler
} // mp
} // wml
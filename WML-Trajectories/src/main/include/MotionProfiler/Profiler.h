#pragma once

/**
 * Profiler, pathfinder implementation for WML
 */

// Utilities
#include "Profiler/MathUtil.h"
#include "Profiler/SplineUtil.h"

// Splines and Trajectories
#include "Profiler/Fit.h"
#include "Profiler/SplineControl.h"
#include "Profiler/TrajectoryGenerator.h"

// Modifiers
#include "Profiler/Modifiers/Tank.h"
#include "Profiler/Modifiers/Swerve.h"

// Followers
#include "Profiler/Followers/DistanceFollower.h"
#include "Profiler/Followers/EncoderFollower.h"

// IO/Error
#include "Profiler/IO.h"


namespace wml {
namespace MotionProfiler {
namespace Profiler {

	class Profiler : 
		public MathUtil, 
		public Fit, 
		public SplineControl, 
		public TrajectoryGenerator,
		public Modifiers::Tank,
		public Modifiers::Swerve,
		public Followers::DistanceFollower,
		public Followers::EncoderFollower
	{};

} // profiler
} // mp
} // wml
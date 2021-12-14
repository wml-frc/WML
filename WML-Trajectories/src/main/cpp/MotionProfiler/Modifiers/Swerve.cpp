#include "MotionProfiler/Profiler/Modifiers/Swerve.h"
#include <math.h>

namespace wml {
namespace MotionProfiler {
namespace Profiler {
namespace Modifiers {
	void Swerve::modify_swerve(std::vector<Segment> original, std::vector<Segment> &fl, std::vector<Segment> &fr, std::vector<Segment> &bl, std::vector<Segment> &br, double wheelbase_width, double wheelbase_depth) {
		for (size_t i = 0; i < original.size(); i++) {
			Segment seg = original[i];
			Segment fl_local = seg;
			Segment fr_local = seg;
			Segment bl_local = seg;
			Segment br_local = seg;
			
			fl_local.x = seg.x - wheelbase_width / 2;
			fl_local.y = seg.y + wheelbase_depth / 2;
			fr_local.x = seg.x + wheelbase_width / 2;
			fr_local.y = seg.y + wheelbase_depth / 2;
			
			bl_local.x = seg.x - wheelbase_width / 2;
			bl_local.y = seg.y - wheelbase_depth / 2;
			br_local.x = seg.x + wheelbase_width / 2;
			br_local.y = seg.y - wheelbase_depth / 2;
			
			fl[i] = fl_local;
			fr[i] = fr_local;
			bl[i] = bl_local;
			br[i] = br_local;
		}
	}
} // modifiers
} // profiler
} // mp
} // wml
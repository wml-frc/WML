#include "test_files.h"

TEST(Fit, Fit_Hermite_Cubic) {
	Profiler profiler;

	std::vector<Waypoint> points;
	points.push_back({-4, -1, MathUtil::d2r(45)});
	points.push_back({-1, -2, 0});
	points.push_back({2, 4, 0});

	ASSERT_EQ(points.size(), 3);

	// Pointer scope test
	{
		std::shared_ptr<Trajectory> traj = std::make_shared<Trajectory>();

		if (profiler.prepare(points, Fit::Type::HERMITE_CUBIC, SplineControl::Samples::kHigh, 0.001, 15.0, 10.0, 60.0, traj) != -1) {
			int length = traj->length;

			std::cout << "length: " << length << std::endl;

			ASSERT_EQ(length, 2418);
		}
	}
}
#include "test_files.h"

TEST(MathUtil, MinMax) {
	Profiler profiler;
	
	ASSERT_EQ(profiler.min(1,2), 1);
	ASSERT_EQ(profiler.min(2,1), 1);

	ASSERT_EQ(profiler.max(1,2), 2);
	ASSERT_EQ(profiler.max(2,1), 2);
}
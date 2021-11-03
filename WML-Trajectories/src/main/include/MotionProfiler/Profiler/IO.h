#pragma once

#include <string.h>
#include <string>
#include "MotionProfiler/Profiler/SplineControl.h"

namespace wml {
namespace MotionProfiler {
namespace Profiler {
	class IO {
	 public:
		static int serialize(FILE *fp, std::vector<Segment> trajectory);
		static int deserialize(FILE *fp, std::vector<Segment> target);

		static int serialize_csv(FILE *fp, std::vector<Segment> trajectory);
		static int deserialize_csv(FILE *fp, std::vector<Segment> target);

		static int getFileLen(FILE *fp);

	 private:
		inline static const char *csv_header = "dt,x,y,position,velocity,acceleration,jerk,heading\n";

		static void int2bytes(int n, char *bytes);
		static int bytes2int(char *bytes);
		static void long2bytes(unsigned long long n, char *bytes);
		static unsigned long long bytes2long(char *bytes);
		static double long2double(unsigned long long l);
		static unsigned long long double2long(double d);
		static void double2bytes(double n, char *bytes);
		static double bytes2double(char *bytes);

	};
} // profiler
} // mp
} // wml
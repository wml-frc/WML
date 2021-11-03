#include "MotionProfiler/Profiler/IO.h"

namespace wml {
namespace MotionProfiler {
namespace Profiler {

	void IO::int2bytes(int n, char *bytes) {
		bytes[0] = (n >> 24) & 0xFF;
		bytes[1] = (n >> 16) & 0xFF;
		bytes[2] = (n >> 8) & 0xFF;
		bytes[3] = n & 0xFF;
	}

	int IO::bytes2int(char *bytes) {
		int value = 0;
		int i;
		for (i = 0; i < 4; i++) {
			int shift = (4 - 1 - i) * 8;
			value += (bytes[i] & 0x000000FF) << shift;
		}
		return value;
	}

	void IO::long2bytes(unsigned long long n, char *bytes) {
		bytes[0] = (n >> 56) & 0xFF;
		bytes[1] = (n >> 48) & 0xFF;
		bytes[2] = (n >> 40) & 0xFF;
		bytes[3] = (n >> 32) & 0xFF;
		bytes[4] = (n >> 24) & 0xFF;
		bytes[5] = (n >> 16) & 0xFF;
		bytes[6] = (n >> 8) & 0xFF;
		bytes[7] = n & 0xFF;
	}

	unsigned long long IO::bytes2long(char *bytes) {
		unsigned long long value = 0;
		int i;
		for (i = 0; i < 8; i++) {
			int shift = (8 - 1 - i) * 8;
			value += (unsigned long long)(((unsigned long long)(bytes[i] & 0xFF)) << shift);
		}
		return value;
	}

	double IO::long2double(unsigned long long l) {
		double result;
		memcpy(&result, &l, 8);
		return result;
	}

	unsigned long long IO::double2long(double d) {
		unsigned long long result;
		memcpy(&result, &d, 8);
		return result;
	}

	void IO::double2bytes(double n, char *bytes) {
		long2bytes(double2long(n), bytes);
	}

	double IO::bytes2double(char *bytes) {
		return long2double(bytes2long(bytes));
	}

	//
	// Main functions (public)
	//

	int IO::serialize(FILE *fp, std::vector<Segment> trajectory) {
		if (fp == NULL) {
			// @ERROR
			return -1;
		}

		if (trajectory.empty()) {
			// @ERROR
			return -1;
		}

		char buf_1[4];
		int2bytes(trajectory.size(), buf_1);
		fwrite(buf_1, 1, 4, fp);

		char buf[8];
		for (size_t i = 0; i < trajectory.size(); i++) {
			Segment s = trajectory[i];

			double2bytes(s.dt, buf);
			fwrite(buf, 1, 8, fp);
							
			double2bytes(s.x, buf);
			fwrite(buf, 1, 8, fp);
			
			double2bytes(s.y, buf);
			fwrite(buf, 1, 8, fp);
			
			double2bytes(s.position, buf);
			fwrite(buf, 1, 8, fp);
			
			double2bytes(s.velocity, buf);
			fwrite(buf, 1, 8, fp);
			
			double2bytes(s.acceleration, buf);
			fwrite(buf, 1, 8, fp);
			
			double2bytes(s.jerk, buf);
			fwrite(buf, 1, 8, fp);
			
			double2bytes(s.heading, buf);
			fwrite(buf, 1, 8, fp);
		}
		return 0; // return success
	}

	int IO::deserialize(FILE *fp, std::vector<Segment> target) {
		if (fp == NULL) {
			// @ERROR
			return -1;
		}

		size_t useless_variable;
		char buf_1[4];
    useless_variable = fread(buf_1, 1, 4, fp);
    int length = bytes2int(buf_1);

		char buf[8];

		for (int i = 0; i < length; i++) {
			useless_variable = fread(buf, 1, 8, fp);
			double dt = bytes2double(buf);
							
			useless_variable = fread(buf, 1, 8, fp);
			double x = bytes2double(buf);
			
			useless_variable = fread(buf, 1, 8, fp);
			double y = bytes2double(buf);
			
			useless_variable = fread(buf, 1, 8, fp);
			double position = bytes2double(buf);
			
			useless_variable = fread(buf, 1, 8, fp);
			double velocity = bytes2double(buf);
			
			useless_variable = fread(buf, 1, 8, fp);
			double acceleration = bytes2double(buf);
			
			useless_variable = fread(buf, 1, 8, fp);
			double jerk = bytes2double(buf);
			
			useless_variable = fread(buf, 1, 8, fp);
			double heading = bytes2double(buf);
			
			Segment s = { dt, x, y, position, velocity, acceleration, jerk, heading };
			target.push_back(s);
		}

		if (length <= 0) {
			return useless_variable;
		} else {
			return length;
		}
	}
	
	int IO::serialize_csv(FILE *fp, std::vector<Segment> trajectory) {
		if (fp == NULL) {
			// @ERROR
			return -1;
		}

		if (trajectory.empty()) {
			// @ERROR
			return -1;
		}

		fputs(csv_header, fp);

		for (size_t i = 0; i < trajectory.size(); i++) {
			char buf[1024];
			Segment s = trajectory[i];
			sprintf(buf, "%f,%f,%f,%f,%f,%f,%f,%f\n", s.dt, s.x, s.y, s.position, s.velocity, s.acceleration, s.jerk, s.heading);
			fputs(buf, fp);
		}

		return 0;
	}

	int IO::deserialize_csv(FILE *fp, std::vector<Segment> target) {
		if (fp == NULL) {
			// @ERROR
			return -1;
		}

		char line[1024];
		int line_n = 0;
		int seg_n = 0;

		while (fgets(line, 1024, fp)) {
			char *tmp = strdup(line);
			if (tmp == NULL) {
				// @ERROR
				return -1;
			}

			if (line_n == 0) {} // hmmmmmmm, i thinky <- this won't work lol

			char *record;
			record = strtok(tmp, ",");
			double dt   = strtod(record, NULL);
			record = strtok(NULL, ",");
			double x    = strtod(record, NULL);
			record = strtok(NULL, ",");
			double y    = strtod(record, NULL);
			record = strtok(NULL, ",");
			double pos  = strtod(record, NULL);
			record = strtok(NULL, ",");
			double vel  = strtod(record, NULL);
			record = strtok(NULL, ",");
			double acc  = strtod(record, NULL);
			record = strtok(NULL, ",");
			double jerk = strtod(record, NULL);
			record = strtok(NULL, ",");
			double head = strtod(record, NULL);

			Segment s = {dt, x, y, pos, vel, acc, jerk, head};
			target.push_back(s);

			free(tmp);

			if (line_n != 0) {
				seg_n++;
			}

			line_n++;
		}

		return seg_n;
	}

	int IO::getFileLen(FILE *fp) {
		if (fp == NULL) {
			// @ERROR
			return -1;
		}

		char line[1024];
		int line_n = 0;

		while (fgets(line, 1024, fp)) {
			line_n++;
			if (strlen(line) >= 1024 - 1) {
				char buf[1024];
				sprintf(buf, "WARNING: Line %d is > 1024 characters long. If read, errors may occur.", line_n);
				// @ERROR
				return -1;
			}
		}

		rewind(fp);
		return line_n;
	}



} // profiler
} // mp
} // wml
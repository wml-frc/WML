#include "MotionProfiler/Profiler/TrajectoryGenerator.h"

namespace wml {
namespace MotionProfiler {
namespace Profiler {
	void TrajectoryGenerator::trajectory_copy(std::vector<Segment> src, std::vector<Segment> &dest) {
		for (size_t i = 0; i < src.size(); i++) {
			dest[i] = src[i];
		}
	}

	TrajectoryInfo TrajectoryGenerator::trajectory_prepare(TrajectoryConfig c) {
		double max_a2 = c.max_a * c.max_a;
		double max_j2 = c.max_j * c.max_j;
		
		double checked_max_v = MathUtil::min(c.max_v,
			(-(max_a2) + sqrt(max_a2 * max_a2 + 4 * (max_j2 * c.max_a * c.dest_pos)))
			/ (2 * c.max_j)
		);
		
		int filter1 = (int) ceil((checked_max_v / c.max_a) / c.dt);
		int filter2 = (int) ceil((c.max_a / c.max_j) / c.dt);
		
		double impulse = (c.dest_pos / checked_max_v) / c.dt;
		int time = (int) ceil(filter1 + filter2 + impulse);
		
		TrajectoryInfo info = { filter1, filter2, time, c.dt, 0, checked_max_v, impulse };
		return info;
	}

	int TrajectoryGenerator::trajectory_fromSecondOrderFilter(int filter_1_l, int filter_2_l, double dt, double u, double v, double impulse, int len, std::vector<Segment> &seg) {
		Segment last_section = {dt, 0, 0, 0, u, 0, 0, 0};
		if (len < 0) {
			return -1; // error
		}

		std::vector<double> f1_buffer;
		f1_buffer.resize(len);
		// double f1_buffer[len];
		f1_buffer[0] = (u/v) * filter_1_l;
		double f2;
		
		for (int i = 0; i < len; i++) {
			double input = MathUtil::min(impulse, 1);
			if (input < 1) {
				input -= 1;
				impulse = 0;
			} else {
				impulse -= input;
			}

			double f1_last;

			if (i > 0) {
				f1_last = f1_buffer[i-1];
			} else {
				f1_last = f1_buffer[0];
			}

			f1_buffer[i] = MathUtil::max(0.0, MathUtil::min(filter_1_l, f1_last + input));

			f2 = 0;
			for (int j = 0; j < filter_2_l; ++j) {
				if (i - j < 0) break;
				f2 += f1_buffer[i-j];
			}

			f2 = f2 / filter_1_l;

			seg[i].velocity = f2 / filter_2_l * v;

			seg[i].position = (last_section.velocity + seg[i].velocity) / 2.0 * dt + last_section.position;

			seg[i].x = seg[i].position;
			seg[i].y = 0;

			seg[i].acceleration = (seg[i].velocity - last_section.velocity) / dt;
			seg[i].jerk = (seg[i].acceleration - last_section.acceleration) / dt;
			seg[i].dt = dt;

			last_section = seg[i];
		}
		return 0;
	}

	int TrajectoryGenerator::trajectory_create(TrajectoryInfo info, TrajectoryConfig config, std::vector<Segment> &seg) {
		int ret = trajectory_fromSecondOrderFilter(info.filter1, info.filter2, info.dt, info.u, info.v, info.impulse, info.length, seg);

		if (ret < 0) {
			return ret;
		}
		
		double d_theta = config.dest_theta - config.src_theta;
		for (int i = 0; i < info.length; i++) {
			seg[i].heading = config.src_theta + d_theta * (seg[i].position) / (seg[info.length - 1].position);
		}
		return 0;
	}

	int TrajectoryGenerator::prepare(const std::vector<Waypoint> points, Fit::Type type, int sample_count, double dt, double max_velocity, double max_acceleration, double max_jerk, std::shared_ptr<Trajectory> traj) {
		if (points.size() < 2) {
			return -1;
		}

		traj->saptr.resize(points.size()-1);
		traj->laptr.resize(points.size()-1);

		double totalLength = 0;

		for (size_t i = 0; i < points.size()-1; i++) {
			Spline s;
			switch(type) {
				case Fit::Type::HERMITE_PRE:
					Fit::fit_hermite_pre(points[i], points[i+1], &s);
					break;

				case Fit::Type::HERMITE_CUBIC:
					Fit::fit_hermite_cubic(points[i], points[i+1], &s);
					break;

				case Fit::Type::HERMITE_QUINTIC:
					Fit::fit_hermite_quintic(points[i], points[i+1], &s);
					break;

				default:
					Fit::fit_hermite_cubic(points[i], points[i+1], &s);
					break;
			}
			double dist = SplineControl::spline_distance(&s, sample_count);
			traj->saptr[i] = s;
			traj->laptr[i] = dist;
			totalLength += dist;
		}

		TrajectoryConfig config = {dt, max_velocity, max_acceleration, max_jerk, 0, points[0].angle, totalLength, 0, points[0].angle, sample_count};
		TrajectoryInfo info = trajectory_prepare(config);
		int trajectory_length = info.length;
		
		traj->totalLength = totalLength;
		traj->length = trajectory_length;
		traj->path_length = points.size();
		traj->info = info;
		traj->config = config;

		return trajectory_length;
	}

	int TrajectoryGenerator::generate(std::shared_ptr<Trajectory> traj, std::vector<Segment> &segments) {
		int traj_length = traj->length;
		int path_length = traj->path_length;
		// double totalLength = traj->totalLength;

		int trajectory_status = trajectory_create(traj->info, traj->config, segments);
		if (trajectory_status < 0) return trajectory_status;

		int spline_i = 0;
		double spline_pos_initial = 0, splines_complete = 0;

		for (int i = 0; i < traj_length; ++i) {
			double pos = segments[i].position;

			int found = 0;
			while (!found) {
				double pos_relative = pos - spline_pos_initial;
				if (pos_relative <= traj->laptr[spline_i]) {
					Spline si = traj->saptr[spline_i];

					double percentage = SplineControl::spline_progress_for_distance(si, pos_relative, traj->config.sample_count);
					Coord coords = SplineControl::spline_coords(si, percentage);
					segments[i].heading = SplineControl::spline_angle(si, percentage);
					segments[i].x = coords.x;
					segments[i].y = coords.y;
					found = 1;
				} else if (spline_i < path_length - 2) {
					splines_complete += traj->laptr[spline_i];
					spline_pos_initial = splines_complete;
					spline_i += 1;
				} else {
					Spline si = traj->saptr[path_length - 2];
					segments[i].heading = SplineControl::spline_angle(si, 1.0);
					Coord coords = SplineControl::spline_coords(si, 1.0);
					segments[i].x = coords.x;
					segments[i].y = coords.y;
					found = 1;
				}
			}
		}

		return traj_length;
	}
} // profiler
} // mp
} // wml
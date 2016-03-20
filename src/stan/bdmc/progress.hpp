#ifndef STAN_BDMC_PROGRESS_HPP
#define STAN_BDMC_PROGRESS_HPP

#include <cstdio>
#include <ctime>
#include <iostream>
#include <iomanip>

namespace stan {
	namespace bdmc {

		class progress_bar {
			
			int ais_weights_;
			int rais_weights_;
			int start_steps_;
			int increment_;
			double load_;

			int percent_;
			// int angle_;
			bool is_complete_;
			// std::string eta_;
			std::ostream& o_;

			double raw_progress (int num_iter_index, int weight_index,
													 int step_index, bool is_ais) {
				int prev_iter = num_iter_index - 1;
				int load = (((prev_iter * (prev_iter - 1)) / 2) * increment_
									 + start_steps_ * prev_iter) * (ais_weights_ + rais_weights_);
				int num_prev_passes = weight_index - 1;
				if (is_ais) num_prev_passes += rais_weights_;
				load += num_prev_passes * (start_steps_ + prev_iter * increment_) + step_index;
				return load;
			}

			// std::string time_str(int t) {
			// 	int s = t % 60;
			// 	int m = (t / 60)%60;
			// 	int h = t/3600;

			// 	std::string ss;
			// 	if (h > 0) {
			// 		ss.append(" ");
			// 		ss.append(std::to_string(h));
			// 		ss.append("h");
			// 	}
			// 	if (m > 0) {
			// 		ss.append(" ");
			// 		ss.append(std::to_string(m));
			// 		ss.append("m");
			// 	}
			// 	if (s > 0) {
			// 		ss.append(" ");
			// 		ss.append(std::to_string(s));
			// 		ss.append("s");
			// 	}
			// 	return ss;
			// }

			void make_bar () {
				// char symbols[4] = {'/', '-', '\\', '|'};
				o_ << "[";
				for (int i = 1; i <= 100; i++) {
					if (i < percent_) o_ << "=";
					else if (i == percent_)
						// o_ << (percent_ == 100
						// 			 ? '=' : symbols[angle_]);
						o_ << "=";
					else o_ << " ";
				}
				o_ << "] [" << std::setw(3) << percent_ << "%]";
				// if (frequent_use_) o_ << " [ETA:" << eta_ << "]";
				// for (int i = 0; i < 11-eta_.length(); i++) o_ << " ";
				o_ << "\r";
				o_ << std::flush;
			}

		public:

			progress_bar(std::ostream& o, int ais_weights, int rais_weights, int start_steps,
									 int increment, int num_iter) :
				ais_weights_ (ais_weights),
				rais_weights_ (rais_weights),
				start_steps_ (start_steps),
				increment_ (increment),
				percent_ (0),
				is_complete_ (false),
				o_ (o) {
					load_ = raw_progress(num_iter, ais_weights,
															 start_steps + (num_iter-1)*increment, true);
					make_bar();
				}

			~progress_bar() {}

			void progress(int num_iter_index, int weight_index,
										int step_index, bool is_ais){
				if (is_complete_) return;
				double p = raw_progress(num_iter_index, weight_index,
													 			step_index, is_ais);
				int prev_percent = percent_;
				percent_ = 100.0 * (p/load_);
				if (percent_ != prev_percent)
					make_bar();
			}
		};
	}
}

// int main() {
// 	progress_bar p(std::cout, false);
// 	for (int i = 10; i <= 100; i+=10) {
// 		p.set(i);
// 		for (int j = 0; j < 10; j++) {
// 			usleep(100000);
// 			p.rotate(((100-i)/10)*1 + (10-j)*0.1);
// 		}
// 	}
// 	return 0;
// }

#endif
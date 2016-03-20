#ifndef STAN_BDMC_SCHEDULES_HPP
#define STAN_BDMC_SCHEDULES_HPP

#include <cmath>
#include <string>

namespace stan {
	namespace bdmc {

		class schedule {
			std::string name_;
			double delta_;

			double uniform_schedule (int index, int num_distributions) {
				return index * (1.0/num_distributions);
			}

			double sigmoid (double z) {
				return 1.0/(1.0 + std::exp(-1.0 * z));
			}

			double sigmoidal_schedule (int index, int num_distributions) {
				double beta_0 = sigmoid(-1.0*delta_);
				double beta_T = sigmoid(delta_);
				double beta_t = sigmoid(delta_*(((2.0*index)/num_distributions)-1.0));

				return (beta_t - beta_0)/(beta_T - beta_0);
			}

		public:

			schedule (std::string name) : name_(name) {};
			schedule (std::string name, double delta) : name_(name), delta_(delta) {
        std::cout << "Delta - " << delta << std::endl;};

			double alpha(int index, int num_distributions) {
				if (name_ == "uniform")
					return uniform_schedule(index, num_distributions);
				else return sigmoidal_schedule(index, num_distributions);
			}

		};

	}
}

#endif
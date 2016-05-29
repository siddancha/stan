#ifndef STAN_SERVICES_ARGUMENTS_ARG_AIS_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_AIS_HPP

#include <stan/services/arguments/categorical_argument.hpp>
#include <stan/services/arguments/arg_num_weights.hpp>
#include <stan/services/arguments/arg_sample_data.hpp>

namespace stan {
  namespace services {

    class arg_ais: public categorical_argument {
    public:
      arg_ais() {
        _name = "ais";
        _description = "Forward Annealed Importance Sampling.";

        _subarguments.push_back(new arg_num_weights());
        _subarguments.push_back(new arg_sample_data());
      }
    };

  }  // services
}  // stan

#endif
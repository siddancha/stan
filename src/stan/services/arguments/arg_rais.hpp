#ifndef STAN_SERVICES_ARGUMENTS_ARG_RAIS_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_RAIS_HPP

#include <stan/services/arguments/categorical_argument.hpp>
#include <stan/services/arguments/arg_num_weights.hpp>
#include <stan/services/arguments/arg_num_burn_in.hpp>

namespace stan {
  namespace services {

    class arg_rais: public categorical_argument {
    public:
      arg_rais() {
        _name = "rais";
        _description = "Reverse Annealed Importance Sampling.";

        _subarguments.push_back(new arg_num_weights());
        _subarguments.push_back(new arg_num_burn_in());
      }
    };

  }  // services
}  // stan

#endif
#ifndef STAN_SERVICES_ARGUMENTS_ARG_UNIFORM_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_UNIFORM_HPP

#include <stan/services/arguments/unvalued_argument.hpp>

namespace stan {
  namespace services {

    class arg_uniform: public unvalued_argument {
    public:
      arg_uniform() {
        _name = "uniform";
        _description = "Uniform Schedule";
      }
    };

  }  // services
}  // stan

#endif


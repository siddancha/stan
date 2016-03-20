#ifndef STAN_SERVICES_ARGUMENTS_ARG_SIGMOIDAL_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_SIGMOIDAL_HPP

#include <stan/services/arguments/categorical_argument.hpp>
#include <stan/services/arguments/arg_delta.hpp>

namespace stan {
  namespace services {

    class arg_sigmoidal: public categorical_argument {
    public:
      arg_sigmoidal() {
        _name = "sigmoidal";
        _description = "Sigmoidal Schedule";

        _subarguments.push_back(new arg_delta());
      }
    };

  }  // services
}  // stan

#endif


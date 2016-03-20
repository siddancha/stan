#ifndef STAN_SERVICES_ARGUMENTS_ARG_DELTA_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_DELTA_HPP

#include <stan/services/arguments/singleton_argument.hpp>

namespace stan {
  namespace services {

    class arg_delta: public real_argument {
    public:
      arg_delta(): real_argument() {
        _name = "delta";
        _description = "Delta for Sigmoidal schedule";
        _validity = "0 <= delta";
        _default = "4.0";
        _default_value = 4.0;
        _constrained = true;
        _good_value = 2.0;
        _bad_value = -1.0;
        _value = _default_value;
      }

      bool is_valid(double value) { return value >= 0; }
    };

  }  // services
}  // stan

#endif

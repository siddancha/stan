#ifndef STAN_SERVICES_ARGUMENTS_ARG_NUM_BURN_IN_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_NUM_BURN_IN_HPP

#include <stan/services/arguments/singleton_argument.hpp>

namespace stan {
  namespace services {

    class arg_num_burn_in: public int_argument {
    public:
      arg_num_burn_in(): int_argument() {
        _name = "num_burn_in";
        _description = "Number of steps for burn in";
        _validity = "0 <= num_burn_in";
        _default = "0";
        _default_value = 0;
        _constrained = true;
        _good_value = 2.0;
        _bad_value = -1.0;
        _value = _default_value;
      }

      bool is_valid(int value) { return value >= 0; }
    };

  }  // services
}  // stan

#endif
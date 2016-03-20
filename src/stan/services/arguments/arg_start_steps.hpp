#ifndef STAN_SERVICES_ARGUMENTS_ARG_START_STEPS_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_START_STEPS_HPP

#include <stan/services/arguments/singleton_argument.hpp>

namespace stan {
  namespace services {

    class arg_start_steps: public int_argument {
    public:
      arg_start_steps(): int_argument() {
        _name = "start_steps";
        _description = "Number of steps in the starting iteration";
        _validity = "0 <= start_steps";
        _default = "1000";
        _default_value = 1000;
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
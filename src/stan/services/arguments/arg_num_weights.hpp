#ifndef STAN_SERVICES_ARGUMENTS_ARG_NUM_WEIGHTS_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_NUM_WEIGHTS_HPP

#include <stan/services/arguments/singleton_argument.hpp>

namespace stan {
  namespace services {

    class arg_num_weights: public int_argument {
    public:
      arg_num_weights(): int_argument() {
        _name = "num_weights";
        _description = "Number of weight samples to average for BDMC";
        _validity = "0 <= num_weights";
        _default = "1";
        _default_value = 1;
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

#ifndef STAN_SERVICES_ARGUMENTS_ARG_NUM_ITER_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_NUM_ITER_HPP

#include <stan/services/arguments/singleton_argument.hpp>

namespace stan {
  namespace services {

    class arg_num_iter: public int_argument {
    public:
      arg_num_iter(): int_argument() {
        _name = "num_iter";
        _description = "Number of iterations of experiment";
        _validity = "0 <= num_weights";
        _default = "10";
        _default_value = 10;
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
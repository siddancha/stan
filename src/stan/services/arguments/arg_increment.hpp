#ifndef STAN_SERVICES_ARGUMENTS_ARG_INCREMENT_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_INCREMENT_HPP

#include <stan/services/arguments/singleton_argument.hpp>

namespace stan {
  namespace services {

    class arg_increment: public int_argument {
    public:
      arg_increment(): int_argument() {
        _name = "increment";
        _description = "Size of increment";
        _validity = "0 <= increment";
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

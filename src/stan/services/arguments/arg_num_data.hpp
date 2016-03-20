#ifndef STAN_SERVICES_ARGUMENTS_ARG_NUM_DATA_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_NUM_DATA_HPP

#include <stan/services/arguments/singleton_argument.hpp>

namespace stan {
  namespace services {

    class arg_num_data: public int_argument {
    public:
      arg_num_data(): int_argument() {
        _name = "num_data";
        _description = "Number of data points";
        _validity = "0 <= num_data";
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

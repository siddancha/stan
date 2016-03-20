#ifndef STAN_SERVICES_ARGUMENTS_ARG_SAMPLE_DATA_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_SAMPLE_DATA_HPP

#include <stan/services/arguments/singleton_argument.hpp>

namespace stan {
  namespace services {

    class arg_sample_data: public bool_argument {
    public:
      arg_sample_data(): bool_argument() {
        _name = "sample_data";
        _description = "Sample data from prior in AIS";
         _validity = "[0, 1]";
        _default = "1";
        _default_value = true;
        _constrained = false;
        _good_value = 1;
        _value = _default_value;
      }
    };

  }  // services
}  // stan

#endif


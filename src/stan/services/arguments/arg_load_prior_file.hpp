#ifndef STAN_SERVICES_ARGUMENTS_ARG_LOAD_PRIOR_FILE_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_LOAD_PRIOR_FILE_HPP

#include <stan/services/arguments/singleton_argument.hpp>

namespace stan {
  namespace services {

    class arg_load_prior_file: public string_argument {
    public:
      arg_load_prior_file(): string_argument() {
        _name = "load_prior_file";
        _description = "File to load prior sample from";
        _validity = "Path to existing file";
        _default = "\"\"";
        _default_value = "";
        _constrained = false;
        _good_value = "good";
        _value = _default_value;
      }
    };

  }  // services
}  // stan

#endif

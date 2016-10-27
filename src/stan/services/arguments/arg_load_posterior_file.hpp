#ifndef STAN_SERVICES_ARGUMENTS_ARG_LOAD_POSTERIOR_FILE_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_LOAD_POSTERIOR_FILE_HPP

#include <stan/services/arguments/singleton_argument.hpp>

namespace stan {
  namespace services {

    class arg_load_posterior_file: public string_argument {
    public:
      arg_load_posterior_file(): string_argument() {
        _name = "load_posterior_file";
        _description = "File to load posterior sample from";
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

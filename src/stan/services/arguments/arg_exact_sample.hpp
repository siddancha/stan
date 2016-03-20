#ifndef STAN_SERVICES_ARGUMENTS_ARG_EXACT_SAMPLE_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_EXACT_SAMPLE_HPP

#include <stan/services/arguments/categorical_argument.hpp>

#include <stan/services/arguments/arg_load_file.hpp>
#include <stan/services/arguments/arg_save_file.hpp>

namespace stan {
  namespace services {

    class arg_exact_sample: public categorical_argument {
    public:
      arg_exact_sample(): categorical_argument() {
        _name = "exact_sample";
        _description = "Options to save and load exact samples";

        _subarguments.push_back(new arg_load_file());      
        _subarguments.push_back(new arg_save_file());
      }
    };

  }  // services
}  // stan

#endif

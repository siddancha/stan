#ifndef STAN_SERVICES_ARGUMENTS_ARG_ITERATIONS_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_ITERATIONS_HPP

#include <stan/services/arguments/categorical_argument.hpp>

#include <stan/services/arguments/arg_start_steps.hpp>
#include <stan/services/arguments/arg_num_iter.hpp>
#include <stan/services/arguments/arg_increment.hpp>

namespace stan {
  namespace services {

    class arg_iterations: public categorical_argument {
    public:
      arg_iterations(): categorical_argument() {
        _name = "iterations";
        _description = "Options for BDMC experiment layout";

        _subarguments.push_back(new arg_start_steps());
        _subarguments.push_back(new arg_increment());
        _subarguments.push_back(new arg_num_iter());
      }
    };

  }  // services
}  // stan

#endif

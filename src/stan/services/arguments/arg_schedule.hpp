#ifndef STAN_SERVICES_ARGUMENTS_ARG_SCHEDULE_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_SCHEDULE_HPP

#include <stan/services/arguments/list_argument.hpp>
#include <stan/services/arguments/arg_uniform.hpp>
#include <stan/services/arguments/arg_sigmoidal.hpp>

namespace stan {
  namespace services {

    class arg_schedule: public list_argument {
    public:
      arg_schedule() {
        _name = "schedule";
        _description = "Schedule for intermediate annealed distributions in BDMC";

        _values.push_back(new arg_uniform());
        _values.push_back(new arg_sigmoidal());

        _default_cursor = 0;
        _cursor = _default_cursor;
      }
    };

  }  // services
}  // stan

#endif


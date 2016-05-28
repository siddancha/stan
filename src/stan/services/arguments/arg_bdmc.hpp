#ifndef STAN_SERVICES_ARGUMENTS_ARG_BDMC_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_BDMC_HPP

#include <stan/services/arguments/categorical_argument.hpp>
#include <stan/services/arguments/arg_ais.hpp>
#include <stan/services/arguments/arg_iterations.hpp>
#include <stan/services/arguments/arg_rais.hpp>
#include <stan/services/arguments/arg_adapt.hpp>
#include <stan/services/arguments/arg_num_warmup.hpp>
#include <stan/services/arguments/arg_sample_algo.hpp>
#include <stan/services/arguments/arg_schedule.hpp>
#include <stan/services/arguments/arg_exact_sample.hpp>
#include <stan/services/arguments/arg_save_samples.hpp>

namespace stan {
  namespace services {

    class arg_bdmc: public categorical_argument {
    public:
      arg_bdmc() {
        _name = "bdmc";
        _description = "Bidirectional Monte Carlo for Bayesian Likelihood Inference";

        _subarguments.push_back(new arg_ais());
        _subarguments.push_back(new arg_rais());
        _subarguments.push_back(new arg_save_samples());
        _subarguments.push_back(new arg_schedule());
        _subarguments.push_back(new arg_adapt());
        _subarguments.push_back(new arg_num_warmup());
        _subarguments.push_back(new arg_sample_algo());
        _subarguments.push_back(new arg_iterations());
        _subarguments.push_back(new arg_exact_sample());
      }
    };

  }  // services
}  // stan

#endif


#ifndef STAN_MCMC_HMC_NUTS_ADAPT_DENSE_E_NUTS_HPP
#define STAN_MCMC_HMC_NUTS_ADAPT_DENSE_E_NUTS_HPP

#include <stan/interface_callbacks/writer/base_writer.hpp>
#include <stan/mcmc/stepsize_covar_adapter.hpp>
#include <stan/mcmc/hmc/nuts/dense_e_nuts.hpp>

namespace stan {
  namespace mcmc {

    // The No-U-Turn Sampler (NUTS) on a
    // Euclidean manifold with dense metric
    // and adaptive stepsize
    template <class Model, class BaseRNG>
    class adapt_dense_e_nuts : public dense_e_nuts<Model, BaseRNG>,
                               public stepsize_covar_adapter {
    public:
        adapt_dense_e_nuts(Model &model, BaseRNG& rng)
          : dense_e_nuts<Model, BaseRNG>(model, rng),
          stepsize_covar_adapter(model.num_params_r()) {}

      ~adapt_dense_e_nuts() {}

      sample transition(sample& init_sample,
                        interface_callbacks::writer::base_writer& writer) {
        sample s = dense_e_nuts<Model, BaseRNG>::transition(init_sample,
                                                            writer);

        if (this->adapt_flag_) {
          this->stepsize_adaptation_.learn_stepsize(this->nom_epsilon_,
                                                    s.accept_stat());

          bool update = this->covar_adaptation_.learn_covariance(this->z_.mInv,
                                                                 this->z_.q);

          if (update) {
            this->init_stepsize(writer);

            this->stepsize_adaptation_.set_mu(log(10 * this->nom_epsilon_));
            this->stepsize_adaptation_.restart();
          }
        }
        return s;
      }

      void disengage_adaptation() {
        base_adapter::disengage_adaptation();
        this->stepsize_adaptation_.complete_adaptation(this->nom_epsilon_);
      }
    };

  }  // mcmc
}  // stan
#endif

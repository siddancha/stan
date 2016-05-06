#ifndef STAN_BDMC_AIS_HPP
#define STAN_BDMC_AIS_HPP

#include <stan/bdmc/progress.hpp>
#include <stan/bdmc/schedules.hpp>
#include <stan/interface_callbacks/writer/base_writer.hpp>
#include <stan/math/prim/mat/fun/Eigen.hpp>
#include <stan/model/util.hpp>
#include <stan/services/mcmc/sample.hpp>

namespace stan {
	namespace bdmc {

		/*
		Does Annealed-Importance Sampling to estimate marginal
		likelihood, as described in http://arxiv.org/abs/1412.8566.
		This function assumes that cont_params is sampled from the
		prior of the model.
		NOTE: sampler should be initialized with the same instance
		of the model.
		*/
		template <class Model, class RNG, class SampleRecorder,
							class DiagnosticRecorder, class MessageRecorder>
		double ais(stan::mcmc::base_mcmc* sampler,
							 int num_steps,
							 schedule &sch,
							 stan::mcmc::sample& init_s,
							 Model& model,
							 bool save,
							 stan::services::sample::mcmc_writer<
               Model, SampleRecorder, DiagnosticRecorder, MessageRecorder>&
               mcmc_writer,
							 RNG& base_rng,
							 progress_bar& bdmc_progress,
							 int iter_index,
							 int weight_index,
							 stan::interface_callbacks::writer::base_writer&
			         writer) {

			double weight = 0.0;
			
			// init_s is x_{k-1}
			for (int k = 1; k <= num_steps; k++) {
				double next_log_prob;
				double prev_log_prob;
				Eigen::VectorXd cont_params;
				init_s.cont_params(cont_params);

				if ( save )
					mcmc_writer.write_sample_params(base_rng, init_s, *sampler, model);

				// calculating f_{t-1}(x_{t-1})
				model.set_alpha(sch.alpha(k-1, num_steps));
				prev_log_prob = stan::model::log_prob_exact<true>(model,
																													cont_params,
																									  			&std::cout);
				
				// calculating f_{t}(x_{t-1})
				model.set_alpha(sch.alpha(k, num_steps));
				next_log_prob = stan::model::log_prob_exact<true>(model,
																													cont_params,
																													&std::cout);
				
				// update weight
				weight += next_log_prob - prev_log_prob;

				init_s = sampler->transition(init_s, writer);
				
				bdmc_progress.progress(iter_index, weight_index, k, true);
			}
			model.set_alpha(1.0);
			return weight;

		}


		/*
		Does Reverse Annealed-Importance Sampling to estimate 
		marginal likelihood, as described in 
		http://arxiv.org/abs/1412.8566. This function assumes that
		cont_params is sampled from the posterior of the model.
		NOTE: sampler should be initialized with the same instance
		of the model.
		*/
		template <class Model, class RNG, class SampleRecorder,
							class DiagnosticRecorder, class MessageRecorder>
		double rais(stan::mcmc::base_mcmc* sampler,
						 	  int num_steps,
						 	  schedule& sch,
							  stan::mcmc::sample& init_s,
							  Model& model,
							  bool save,
							  stan::services::sample::mcmc_writer<
                Model, SampleRecorder, DiagnosticRecorder, MessageRecorder>&
                mcmc_writer,
							  RNG& base_rng,
							  progress_bar& bdmc_progress,
							  int iter_index,
								int weight_index,
							  stan::interface_callbacks::writer::base_writer&
			          writer) {

			double weight = 0.0;

			// init_s is x_{k-1}
			for (int k = num_steps; k >= 1; k--) {
				double next_log_prob;
				double prev_log_prob;
				Eigen::VectorXd cont_params;
				init_s.cont_params(cont_params);

				if ( save )
					mcmc_writer.write_sample_params(base_rng, init_s, *sampler, model);

				// calculating f_{t-1}(x_{t-1})
				model.set_alpha(sch.alpha(k, num_steps));
				prev_log_prob = stan::model::log_prob_exact<true>(model,
																													cont_params,
																													&std::cout);

				// calculating f_{t}(x_{t-1})
				model.set_alpha(sch.alpha(k-1, num_steps));
				next_log_prob = stan::model::log_prob_exact<true>(model,
																													cont_params,
																													&std::cout);

				// update weight
				weight += next_log_prob - prev_log_prob;

				init_s = sampler->transition(init_s, writer);

				bdmc_progress.progress(iter_index, weight_index, num_steps-k+1, false);
			}
			model.set_alpha(1.0);
			return -1.0*weight;

		}

	}
}

#endif
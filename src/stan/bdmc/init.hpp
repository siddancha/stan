#ifndef STAN_BDMC_INIT_HPP
#define STAN_BDMC_INIT_HPP

#include <stan/io/array_var_context.hpp>
#include <stan/math/prim/mat/fun/Eigen.hpp>

#include <string>
#include <vector>

namespace stan {
  namespace bdmc {

    template <class Model, class RNG>
    void sample_data_and_params (Model& model,
                                 std::vector<double>& vars_param,
                                 std::vector<double>& vars_data,
                                 RNG& base_rng) {
      model.exact_sample(base_rng, vars_param, vars_data);
    }

    template <class Model>
    void set_data (Model& model,
                   std::vector<double>& vars_data) {
      // Creating var_context for exact data sample.
      std::vector<std::string> data_var_names;
      std::vector<std::vector<size_t> > data_dims;
      model.get_data_names(data_var_names);
      model.get_data_dims(data_dims);
      stan::io::array_var_context exact_data_context(data_var_names,
                                                     vars_data,
                                                     data_dims);
      // Creating new model with exact data sample.
      model = Model(exact_data_context, &std::cout);
    }

    template <class Model>
    void set_params (Model& model,
                     Eigen::VectorXd& cont_params,
                     std::vector<double>& vars_param) {
      // Creating var_context for sample.
      std::vector<std::string> param_var_names;
      std::vector<std::vector<size_t> > param_dims;
      model.get_param_names(param_var_names);
      model.get_param_dims(param_dims);
      stan::io::array_var_context exact_param_context(param_var_names,
                                                      vars_param,
                                                      param_dims);
      // Creating sample from var_context.
      cont_params.resize(model.num_params_r());
      model.transform_inits(exact_param_context, cont_params, 0);
    }

    // template <class Model, class RNG>
    // void initialize_with_prior (Eigen::VectorXd& cont_params,
    //                             Model& model,
    //                             RNG& base_rng) {
    //   std::vector<double> vars_param;
    //   std::vector<double> vars_data;
    //   // Sample from prior and generate exact sample.
    //   model.exact_sample(base_rng, vars_param, vars_data);

    //   // Creating var_context for prior sample.
    //   std::vector<std::string> param_var_names;
    //   std::vector<std::vector<size_t> > param_dims;
    //   model.get_param_names(param_var_names);
    //   model.get_param_dims(param_dims);
    //   stan::io::array_var_context exact_param_context(param_var_names,
    //                                                   vars_param,
    //                                                   param_dims);
      
    //   // Creating prior sample from var_context.
    //   cont_params.resize(model.num_params_r());
    //   model.transform_inits(exact_param_context, cont_params, 0);
    // }

    // template <class Model, class RNG>
    // void initialize_with_prior_and_exact_sample (Eigen::VectorXd& cont_params,
    //                                              Model& model,
    //                                              RNG& base_rng) {
    //   std::vector<double> vars_param;
    //   std::vector<double> vars_data;
    //   model.exact_sample(base_rng, vars_param, vars_data);
    //   // Sample from prior and generate exact sample.
    //   model.exact_sample(base_rng, vars_param, vars_data);

    //   // Creating var_context for exact data sample.
    //   std::vector<std::string> data_var_names;
    //   std::vector<std::vector<size_t> > data_dims;
    //   model.get_data_names(data_var_names);
    //   model.get_data_dims(data_dims);
    //   stan::io::array_var_context exact_data_context(data_var_names,
    //                                                  vars_data,
    //                                                  data_dims);

    //   // Creating var_context for prior sample.
    //   std::vector<std::string> param_var_names;
    //   std::vector<std::vector<size_t> > param_dims;
    //   model.get_param_names(param_var_names);
    //   model.get_param_dims(param_dims);
    //   stan::io::array_var_context exact_param_context(param_var_names,
    //                                                   vars_param,
    //                                                   param_dims);

    //   // Creating new model with exact data sample.
    //   model = Model(exact_data_context, &std::cout);

    //   // Creating prior sample from var_context.
    //   cont_params.resize(model.num_params_r());
    //   model.transform_inits(exact_param_context, cont_params, 0);
    // }

  }
}

#endif
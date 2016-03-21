#ifndef STAN_BDMC_IO_HPP
#define STAN_BDMC_IO_HPP

#include <fstream>
#include <string>
#include <vector>

namespace stan {
	namespace bdmc {

		void save_exact_sample (std::string filename,
													  std::vector<double>& vars_prior_params,
													  std::vector<double>& vars_posterior_params,
													  std::vector<double>& vars_data) {
			std::ofstream file(filename, std::ofstream::binary);
			if (!file.is_open()) {
				std::cerr << "Could not open file - " << filename << std::endl;
				exit(1);
			}

			int vars_prior_params_size = vars_prior_params.size();
			int vars_posterior_params_size = vars_posterior_params.size();
			int vars_data_size = vars_data.size();

			file.write(reinterpret_cast<char*> (&vars_prior_params_size), sizeof vars_prior_params_size);
			file.write(reinterpret_cast<char*> (&vars_posterior_params_size), sizeof vars_posterior_params_size);
			file.write(reinterpret_cast<char*> (&vars_data_size), sizeof vars_data_size);


			for (size_t i = 0; i < vars_prior_params.size(); i++)
				file.write(reinterpret_cast<char*> (&vars_prior_params[i]), sizeof vars_prior_params[i]);
			
			for (size_t i = 0; i < vars_posterior_params.size(); i++)
				file.write(reinterpret_cast<char*> (&vars_posterior_params[i]), sizeof vars_posterior_params[i]);

			for (size_t i = 0; i < vars_data.size(); i++)
				file.write(reinterpret_cast<char*> (&vars_data[i]), sizeof vars_data[i]);

			file.close();

			// std::cout << "Generated exact sample - \n";
			// for (int i = 0; i < vars_prior_params.size(); i++)
			// 	if (i == vars_prior_params.size() - 1)
			// 		std::cout << vars_prior_params[i] << "\n\n";
			// 	else std::cout << vars_prior_params[i] << ", ";
			
			// for (int i = 0; i < vars_posterior_params.size(); i++)
			// 	if (i == vars_posterior_params.size() - 1)
			// 		std::cout << vars_posterior_params[i] << "\n\n";
			// 	else std::cout << vars_posterior_params[i] << ", ";

			// for (int i = 0; i < vars_data.size(); i++)
			// 	if (i == vars_data.size() - 1)
			// 		std::cout << vars_data[i] << "\n\n";
			// 	else std::cout << vars_data[i] << ", ";
		}

		template <class Model>
		void load_exact_sample (std::string filename,
													  std::vector<double>& vars_prior_params,
													  std::vector<double>& vars_posterior_params,
													  std::vector<double>& vars_data,
													  Model& model) {

			std::ifstream file(filename, std::ifstream::binary);
			if (!file.is_open()) {
				std::cerr << "Could not open file - " << filename << std::endl;
				exit(1);
			}

			// calculating size
			size_t size = 0;
			std::vector<std::vector<size_t> > param_dims;
			model.get_param_dims(param_dims);
			for (size_t i = 0; i < param_dims.size(); i++) {
				size_t m_size = 1;
				for (size_t j = 0; j < param_dims[i].size(); j++)
					m_size *= param_dims[i][j];
				size += m_size;
			}
			size *= 2;
			std::vector<std::vector<size_t> > data_dims;
			model.get_data_dims(data_dims);
			for (size_t i = 0; i < data_dims.size(); i++) {
				size_t m_size = 1;
				for (size_t j = 0; j < data_dims[i].size(); j++)
					m_size *= data_dims[i][j];
				size += m_size;
			}
			size *= sizeof(double);
			size += 3 * sizeof(int);

			file.seekg(0, file.end);
			size_t filesize = file.tellg();

			if (filesize != size) {
				std::cerr << filename
									<< " size not compatible with required size of exact sample for this model."
									<< " Required size is " << size << " bytes, but file size is " << filesize
									<< " bytes.\n"; 
				exit(1);
			}

			file.seekg(0, file.beg);

			vars_prior_params.clear();
			vars_posterior_params.clear();
			vars_data.clear();

			int vars_prior_params_size;
			int vars_posterior_params_size;
			int vars_data_size;

			file.read(reinterpret_cast<char*> (&vars_prior_params_size), sizeof vars_prior_params_size);
			file.read(reinterpret_cast<char*> (&vars_posterior_params_size), sizeof vars_posterior_params_size);
			file.read(reinterpret_cast<char*> (&vars_data_size), sizeof vars_data_size);

			for (int i = 0; i < vars_prior_params_size; i++) {
				double val;
				file.read(reinterpret_cast<char*> (&val), sizeof val);
				vars_prior_params.push_back(val);
			}
			
			for (int i = 0; i < vars_posterior_params_size; i++) {
				double val;
				file.read(reinterpret_cast<char*> (&val), sizeof val);
				vars_posterior_params.push_back(val);
			}

			for (int i = 0; i < vars_data_size; i++) {
				double val;
				file.read(reinterpret_cast<char*> (&val), sizeof val);
				vars_data.push_back(val);
			}

			file.close();

			// std::cout << "Loaded exact sample - \n";
			// for (int i = 0; i < vars_prior_params.size(); i++)
			// 	if (i == vars_prior_params.size() - 1)
			// 		std::cout << vars_prior_params[i] << "\n\n";
			// 	else std::cout << vars_prior_params[i] << ", ";
			
			// for (int i = 0; i < vars_posterior_params.size(); i++)
			// 	if (i == vars_posterior_params.size() - 1)
			// 		std::cout << vars_posterior_params[i] << "\n\n";
			// 	else std::cout << vars_posterior_params[i] << ", ";

			// for (int i = 0; i < vars_data.size(); i++)
			// 	if (i == vars_data.size() - 1)
			// 		std::cout << vars_data[i] << "\n\n";
			// 	else std::cout << vars_data[i] << ", ";
		}

		// class printer {
		// private:
		// 	int num_ais_steps_;
		// 	int num_rais_steps_;
		// 	int total_steps_;
		// 	std::ostream& o_;

		// public:
		// 	printer (int num_ais_steps, int num_rais_steps, 
		// 					 int num_ais_weights, std::ostream& o)
		// 		:	num_ais_steps_(num_ais_steps),
		// 			num_rais_steps_(num_rais_steps),
		// 			o_ (o) {
		// 				total_steps_ = num_rais_steps + num_ais_weights * num_ais_steps;
		// 	}

		// 	~printer() {}

		// 	void progress (bool is_ais, int num_steps, int num_weights) {
		// 		int present_steps;
		// 		if (!is_ais)
		// 			present_steps = num_steps;
		// 		else
		// 			present_steps = num_rais_steps_
		// 											+ num_weights * num_ais_steps_
		// 											+ num_steps;
		// 		if (present_steps % 1000 != 0 && present_steps > 1 && present_steps < total_steps_)
		// 			return;
		// 		int it_print_width = std::ceil(std::log10(static_cast<double>(total_steps_)));
		// 		o_ << "Iteration: ";
		// 		o_ << std::setw(it_print_width) << present_steps
		// 			 << " / " << total_steps_;
		// 		o_ << " [" << std::setw(3)
		// 			 << static_cast<int>( (100.0 * present_steps) / total_steps_)
		// 			 << "%] ";
		// 		o_ << (is_ais ? "(AIS)" : "(RAIS)") << "\n";
		// 		o_ << std::flush;
		// 	}

		// };

		// void write_timing (std::string prefix, std::string suffix,
		// 									 double ais_time, double rais_time, std::ostream& o) {
		// 	o << prefix
		// 		<< "Elapsed Time: " << ais_time << " seconds (AIS)\n"
		// 		<< "              " << rais_time << " seconds (RAIS)\n"
		// 		<< "              " << ais_time + rais_time << " seconds (Total)\n"
		// 		<< suffix << std::flush;
		// }
	}
}

#endif
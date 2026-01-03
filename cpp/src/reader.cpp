#include "utility.hpp"

#include <tdsreader/reader.hpp>
#include <format>

namespace tdsreader {


tds read(const fs::path &path) {
	tds res;
	std::vector<fs::path> file_E = find_files(path, "E");
	if (file_E.size() > 1) {
		throw std::runtime_error("More than one E matrix!");
	} else if (file_E.size() == 1) {
		std::vector<std::vector<double>> mat = read_matrix(file_E[0]);
		Eigen::MatrixXd matrix = convert_to(mat);
		res.E = std::move(matrix);
	}
	for(Matrices m: {Matrices::A, Matrices::H, Matrices::B1, Matrices::B2, Matrices::C1, Matrices::C2,
					 Matrices::D11, Matrices::D21, Matrices::D12, Matrices::D22}) {
		const std::string prefix = get_filename_prefix(m);
		int nb_rows = -1;
		int nb_cols = -1;
		// Find matrix files
		std::vector<fs::path> files = find_files(path, prefix);
		std::ranges::sort(files, [](const fs::path& a, const fs::path& b) { return a.string() < b.string(); });
		for (const auto& file_path: files) {
			std::vector<std::vector<double>> mat = read_matrix(file_path);
			if (nb_rows == -1) {
				nb_rows = mat.size();
			} else if (nb_rows != mat.size()) {
				throw std::runtime_error(std::format("Inconsistent number of rows for matrices in {}!", prefix));
			}
			if (nb_cols == -1) {
				nb_cols = mat.size();
			} else if (nb_cols != mat[0].size()) {
				throw std::runtime_error(std::format("Inconsistent number of columns for matrices in {}!", prefix));
			}
			if ((m == Matrices::A || m == Matrices::H) && nb_rows != nb_cols) {
				throw std::runtime_error(std::format("Matrices in {} are not square!", prefix));
			}
			Eigen::MatrixXd matrix = convert_to(mat);
			res.get_matrices(m).push_back(std::move(matrix));
		}
		// Find delay file
		std::vector<fs::path> file_delay = find_files(path, "h" + prefix);
		if (file_delay.size() > 1) {
			throw std::runtime_error(std::format("More than one h{} file!", prefix));
		} else if (file_delay.size() == 1) {
			std::vector<double> delays = read_delays(file_delay[0]);
			if (delays.size() != res.get_matrices(m).size()) {
				throw std::runtime_error(std::format("Number of delays in {}, does not match the number of matrices!", prefix));
			}
			res.get_delays(m) = std::move(delays);
		}
	}
	return res;
}

}
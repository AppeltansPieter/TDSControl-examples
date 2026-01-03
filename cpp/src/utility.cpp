#include "utility.hpp"
#include <filesystem>
#include <fstream>
#include <utility>
#include <Eigen/Core>
#include <sstream>
#include <format>
#include <algorithm>

namespace tdsreader {

std::ifstream open_file(const fs::path& path) {
	std::ifstream res(path);
	if (!res.is_open()) {
		throw std::runtime_error(std::format("Could not open file {}!", path.string()));
	}
	return res;
}

std::vector<fs::path> find_files(const fs::path& path, const std::string &prefix) {
	std::vector<fs::path> res;
	for (const auto& entry: fs::directory_iterator(path)) {
		if (entry.is_regular_file()) {
			const std::string filename = entry.path().filename().string();
			if (filename.rfind(prefix, 0) == 0) {
				res.push_back(entry.path());
			}
		}
	}
	return res;
}

Eigen::MatrixXd convert_to(const std::vector<std::vector<double>>& mat) {
	std::size_t nrows = mat.size();
	std::size_t ncols = mat[0].size();
	Eigen::MatrixXd res(nrows, ncols);
	for (std::size_t i = 0; i < nrows; ++i) {
		for (std::size_t j = 0; j < ncols; ++j) {
			res(i, j) = mat[i][j];
		}
	}
	return res;
}

std::vector<std::vector<double>> read_matrix(const fs::path &path) {
	std::ifstream file = open_file(path);
	std::vector<std::vector<double>> rows;
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		std::string cell;
		std::vector<double> row;
		while (std::getline(ss, cell, ',')) {
			row.push_back(std::stod(cell));
		}
		if (!row.empty()) {
			rows.push_back(std::move(row));
		}
	}
	const std::size_t nrows = rows.size();
	if (nrows == 0) {
		throw std::runtime_error(std::format("No matrix found in {}!", path.string()));
	}
	const std::size_t ncols = rows[0].size();
	if (ncols == 0) {
		throw std::runtime_error(std::format("No matrix found in {}!", path.string()));
	}
	for (const auto& r : rows) {
		if (r.size() != ncols) {
			throw std::runtime_error(std::format("Inconsistent number of columns in file {}!", path.string()));
		}
	}
	return rows;
}

std::vector<double> read_delays(const fs::path &path) {
	std::ifstream file = open_file(path);
	std::string line;
	if (!std::getline(file, line)) {
		throw std::runtime_error(std::format("Could not read delays file {}!", path.string()));
	}
	std::stringstream ss(line);
	std::string cell;
	std::vector<double> values;
	while (std::getline(ss, cell, ',')) {
		values.push_back(std::stod(cell));
	}
	return values;
}
}
#pragma once

#include <filesystem>
#include <fstream>
#include <utility>
#include <Eigen/Core>

namespace fs = std::filesystem;

namespace tdsreader {
/**
 * @brief Open a given file
 *
 * @param path Path to file
 * @returns std::ifstream
 * @throws runtime_error When file can not be opened
 */
std::ifstream open_file(const fs::path& path);

/**
 * @brief Find all files in a folder that start with a given prefix.
 *
 * @param path Folder to search through
 * @param prefix Search prefix
 * @returns std::vector<fs::path> containg the path of all files matching the prefix
 */
std::vector<fs::path> find_files(const fs::path& path, const std::string &prefix);

/**
 * @brief Read a matrix from a file where the elements are seperated by commas and the row by new lines
 *
 * @param path to file containing the matrix
 * @returns std::vector<std::vector<double>> parsed matrix
 * @throws std::invalid_argument when the elements could not be converted to doubles
 * @throws std::out_of_range when the elements are not within the range of the doubles
 * @throws std::runtime_error when the file contains no valid matrix
 * @throws std::runtime_error when the number of elements in the different rows is not the same
 */
std::vector<std::vector<double>> read_matrix(const fs::path &path);

/**
 * @brief Convert a vector of vectors of doubles to an Eigen matrix.
 *
 * @brief mat the vector of vectors of doubles to convert
 * @returns Eigen::MatrixXd
 */
Eigen::MatrixXd convert_to(const std::vector<std::vector<double>>& mat);

/**
 * @brief Read delay vector from file where the delays are separated by commas
 *
 * @param path to file containing the delays
 * @returns std::vector<double> containing the delays
 * @throws std::invalid_argument when the elements could not be converted to doubles
 * @throws std::out_of_range when the elements are not within the range of the doubles
 * @throws std::runtime_error when the file does not contain a delay vector
 */
std::vector<double> read_delays(const fs::path &path);
}
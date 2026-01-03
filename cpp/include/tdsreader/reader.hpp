#pragma once

#include <tdsreader/system.hpp>
#include <filesystem>

namespace fs = std::filesystem;

namespace tdsreader {

/**
 * @brief Create a time-delay system from the matrices and delay vectors in a given folder.
 *
 * @param path of the folder containing the time-delay system
 * @returns tds
 * @throws std::invalid_argument when the elements of a system matrix or delay vector could not be converted to doubles
 * @throws std::out_of_range when the elements of a system matrix or delay are not within the range of the doubles
 * @throws std::runtime_error other problems such as incompatible dimension or incompatible number of system matrices
 *                            and delays
 */
tds read(const fs::path &path);
}
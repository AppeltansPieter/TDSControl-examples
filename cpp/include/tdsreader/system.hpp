#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <Eigen/Dense>

namespace tdsreader {
   enum class Matrices {
      A, H, B1, B2, C1, C2, D11, D21, D12, D22
   };

   /**
    * @brief Get the file prefix for a given term of a time delay system
    */
   std::string get_filename_prefix(Matrices m);

   struct tds {
      Eigen::MatrixXd E;
      std::vector<Eigen::MatrixXd> A;
      std::vector<double> hA;
      std::vector<Eigen::MatrixXd> H;
      std::vector<double> hH;
      std::vector<Eigen::MatrixXd> B1;
      std::vector<double> hB1;
      std::vector<Eigen::MatrixXd> B2;
      std::vector<double> hB2;
      std::vector<Eigen::MatrixXd> C1;
      std::vector<double> hC1;
      std::vector<Eigen::MatrixXd> C2;
      std::vector<double> hC2;
      std::vector<Eigen::MatrixXd> D11;
      std::vector<double> hD11;
      std::vector<Eigen::MatrixXd> D21;
      std::vector<double> hD21;
      std::vector<Eigen::MatrixXd> D12;
      std::vector<double> hD12;
      std::vector<Eigen::MatrixXd> D22;
      std::vector<double> hD22;

      /**
       * @brief Get the system matrices associated with a given term.
       */
      std::vector<Eigen::MatrixXd> &get_matrices(Matrices m);

      /**
       * @brief Get the delays associated with a given term.
       */
      std::vector<double> &get_delays(Matrices m);
   };

}
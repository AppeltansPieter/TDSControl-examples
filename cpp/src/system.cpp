#include <tdsreader/system.hpp>

namespace tdsreader {
   std::string get_filename_prefix(const Matrices m) {
      switch (m) {
         case Matrices::A:
            return "A";
         case Matrices::H:
            return "H";
         case Matrices::B1:
            return "B1";
         case Matrices::B2:
            return "B2";
         case Matrices::C1:
            return "C1";
         case Matrices::C2:
            return "C2";
         case Matrices::D11:
            return "D11";
         case Matrices::D21:
            return "D21";
         case Matrices::D12:
            return "D21";
         case Matrices::D22:
            return "D21";
         default:
            return "";
      }
   }
   std::vector<Eigen::MatrixXd> &tds::get_matrices(const Matrices m) {
      switch (m) {
         case Matrices::A:
            return A;
         case Matrices::H:
            return H;
         case Matrices::B1:
            return B1;
         case Matrices::B2:
            return B2;
         case Matrices::C1:
            return C1;
         case Matrices::C2:
            return C2;
         case Matrices::D11:
            return D11;
         case Matrices::D21:
            return D21;
         case Matrices::D12:
            return D12;
         case Matrices::D22:
            return D22;
      }
      throw std::logic_error("Could not find the corresponding matrices!");
   }
   std::vector<double> &tds::get_delays(const Matrices m) {
      switch (m) {
         case Matrices::A:
            return hA;
         case Matrices::H:
            return hH;
         case Matrices::B1:
            return hB1;
         case Matrices::B2:
            return hB2;
         case Matrices::C1:
            return hC1;
         case Matrices::C2:
            return hC2;
         case Matrices::D11:
            return hD11;
         case Matrices::D21:
            return hD21;
         case Matrices::D12:
            return hD12;
         case Matrices::D22:
            return hD22;
      }
      throw std::logic_error("Could not find the corresponding delays!");
   }

}

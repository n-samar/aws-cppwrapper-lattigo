#pragma once

#include <cassert>
#include <sstream>
#include <string>
#include <unordered_map>

namespace latticpp {

namespace {
const std::unordered_map<int, int> log_q0_from_bootstrapping_precision{
    {19, 55}, {25, 60}, {32, 60}};

}  // namespace

class LattigoParam {
 public:
  LattigoParam() = delete;
  LattigoParam(int log_N, int log_scale, int usable_levels,
               int bootstrapping_precision)
      : log_N_(log_N),
        log_scale_(log_scale),
        usable_levels_(usable_levels),
        bootstrapping_precision_(bootstrapping_precision) {
    // These are the only precision our lattigo currently supports
    assert(bootstrapping_precision_ == 19 || bootstrapping_precision_ == 26 ||
           bootstrapping_precision_ == 32);
    int log_q0 =
        log_q0_from_bootstrapping_precision.at(bootstrapping_precision);
    // otherwise, the compiler shouts log_q0 is  unused, even tho it is used in
    // the assert
    (void)log_q0;
    // Required by
    // https://github.com/n-samar/lattigo/blob/master/ckks/bootstrapping/bootstrap.go#L37-L39
    // (message ratio is 256 in lattigo (= 2^8))
    assert(log_q0 - 8 >= log_scale_);
  }

  int LogN() const { return log_N_; }
  int LogScale() const { return log_scale_; }
  int UsableLevels() const { return usable_levels_; }
  int BootstrappingPrecision() const { return bootstrapping_precision_; }
  std::string GetMarshalFolderExtension() const {
    return "LogN" + std::to_string(log_N_) + "LogScale" +
           std::to_string(log_scale_) + "UsableLevels" +
           std::to_string(usable_levels_) + "BootstrappingPrecision" +
           std::to_string(bootstrapping_precision_);
  }
  static LattigoParam ReadStream(std::istream& stream) {
    int log_N;
    int log_scale;
    int usable_levels;
    int bootstrapping_precision;
    stream >> log_N >> log_scale >> usable_levels >> bootstrapping_precision;
    return {log_N, log_scale, usable_levels, bootstrapping_precision};
  }

 private:
  int log_N_;
  int log_scale_;
  int usable_levels_;
  int bootstrapping_precision_;
};

inline std::ostream& operator<<(std::ostream& os, const LattigoParam& param) {
  return os << param.LogN() << " " << param.LogScale() << " "
            << param.UsableLevels() << " " << param.BootstrappingPrecision();
}

inline bool operator==(const LattigoParam& lhs, const LattigoParam& rhs) {
  return lhs.LogN() == rhs.LogN() && lhs.LogScale() == rhs.LogScale() &&
         lhs.UsableLevels() == rhs.UsableLevels() &&
         lhs.BootstrappingPrecision() == rhs.BootstrappingPrecision();
}

}  // namespace latticpp

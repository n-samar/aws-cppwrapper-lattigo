#pragma once

#include <sstream>
#include <string>

namespace latticpp {

class LattigoParam {
 public:
  LattigoParam() = delete;
  LattigoParam(int log_N, int log_scale, int usable_levels,
               int bootstrapping_precision)
      : log_N_(log_N),
        log_scale_(log_scale),
        usable_levels_(usable_levels),
        bootstrapping_precision_(bootstrapping_precision) {}

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

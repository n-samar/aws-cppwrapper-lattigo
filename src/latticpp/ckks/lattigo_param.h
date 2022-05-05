#pragma once

#include <sstream>
#include <string>

namespace latticpp {

class LattigoParam {
 public:
  LattigoParam() : log_N_(-1), log_scale_(-1), usable_levels_(-1) {}
  LattigoParam(int log_N, int log_scale, int usable_levels)
      : log_N_(log_N), log_scale_(log_scale), usable_levels_(usable_levels) {}

  int LogN() const { return log_N_; }
  int LogScale() const { return log_scale_; }
  int UsableLevels() const { return usable_levels_; }
  std::string GetMarshalFolderExtension() const {
    return "LogN" + std::to_string(log_N_) + "LogScale" +
           std::to_string(log_scale_) + "UsableLevels" +
           std::to_string(usable_levels_);
  }

 private:
  int log_N_;
  int log_scale_;
  int usable_levels_;
};

inline std::istream& operator>>(std::istream& is, LattigoParam& param) {
  int log_N;
  int log_scale;
  int usable_levels;
  is >> log_N >> log_scale >> usable_levels;
  param = LattigoParam(log_N, log_scale, usable_levels);
  return is;
}

inline std::ostream& operator<<(std::ostream& os, const LattigoParam& param) {
  return os << param.LogN() << " " << param.LogScale() << " "
            << param.UsableLevels();
}

inline bool operator==(const LattigoParam& lhs, const LattigoParam& rhs) {
  return lhs.LogN() == rhs.LogN() && lhs.LogScale() == rhs.LogScale() &&
         lhs.UsableLevels() == rhs.UsableLevels();
}

}  // namespace latticpp

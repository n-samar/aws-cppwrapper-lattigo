// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "bootstrap_params.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iterator>

using namespace std;

namespace latticpp {

BootstrappingParameters getBootstrappingParams(const LattigoParam& param) {
  uint8_t index = ParamToIndex(param);
  return BootstrappingParameters(lattigo_getBootstrappingParams(index));
}

uint8_t ParamToIndex(const LattigoParam& param) {
  static std::vector<LattigoParam> params;
  if (params.empty()) {
    // Initialize params
    std::string file = std::string{__FILE__};
    std::string filepath = "/tmp/default_params.scheme";
    std::ifstream ifs(filepath);
    assert(ifs);
    std::cout << "NIKOLA FILEPATH: " << filepath << std::endl;
    std::istream_iterator<LattigoParam> start(ifs), end;
    params = std::vector<LattigoParam>(start, end);
  }
  assert(!params.empty());
  auto result_idx = std::find(params.begin(), params.end(), param);
  assert(result_idx != params.end());
  std::cout << "NEW NIKOLA INDEX: " << param << " " << params[0] << std::endl;
  std::cout << "NEW NIKOLA INDEX: " << result_idx - params.begin() << std::endl;
  return result_idx - params.begin();
}

}  // namespace latticpp

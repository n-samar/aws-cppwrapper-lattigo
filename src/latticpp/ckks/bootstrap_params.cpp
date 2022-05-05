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
    std::ifstream ifstream("lattigo/ckks/bootstrapping/default_params.scheme");
    std::istream_iterator<LattigoParam> start(ifstream), end;
    params = std::vector<LattigoParam>(start, end);
  }
  auto result_idx = std::find(params.begin(), params.end(), param);
  assert(result_idx != params.end());
  return result_idx - params.begin();
}

}  // namespace latticpp

// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "bootstrap_params.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

namespace latticpp {

BootstrappingParameters getBootstrappingParams(const LattigoParam& param) {
  auto [logN, log_scale, usable_levels, bootstrapping_params] =
      ParamToIndex(param);
  return BootstrappingParameters(lattigo_getBootstrappingParams(
      logN, log_scale, usable_levels, bootstrapping_params));
}

Parameters getDefaultCKKSParams(const LattigoParam& param) {
  auto [logN, log_scale, usable_levels, bootstrapping_params] =
      ParamToIndex(param);
  return Parameters(lattigo_getDefaultCKKSParams(logN, log_scale, usable_levels,
                                                 bootstrapping_params));
}

std::tuple<uint64_t, uint64_t, uint64_t, uint64_t> ParamToIndex(
    const LattigoParam& param) {
  return std::make_tuple(param.LogN(), param.LogScale(), param.UsableLevels(),
                         param.BootstrappingPrecision());
}

}  // namespace latticpp

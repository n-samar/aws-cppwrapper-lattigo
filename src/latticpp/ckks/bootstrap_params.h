// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "cgo/bootstrap_params.h"
#include "latticpp/ckks/lattigo_param.h"
#include "latticpp/marshal/gohandle.h"

namespace latticpp {

uint8_t ParamToIndex(const LattigoParam& param);

BootstrappingParameters getBootstrappingParams(const LattigoParam& param);

Parameters genParams(const BootstrappingParameters& bootParams);

// Get the secret key Hamming weight for which these bootstrapping parameters
// were created
uint64_t secretHammingWeight(const BootstrappingParameters& bootParams);

// The multiplicative depth of the bootstrapping circuit
int bootstrapDepth(const BootstrappingParameters& bootParams);

inline Parameters getDefaultCKKSParams(const LattigoParam& param) {
  uint8_t index = ParamToIndex(param);
  return Parameters(lattigo_getDefaultCKKSParams(index));
}

}  // namespace latticpp


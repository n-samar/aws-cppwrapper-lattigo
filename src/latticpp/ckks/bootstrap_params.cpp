// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "bootstrap_params.h"

using namespace std;

namespace latticpp {

BootstrappingParameters getBootstrappingParams(uint8_t index) {
  return BootstrappingParameters(lattigo_getBootstrappingParams(index));
}

}  // namespace latticpp

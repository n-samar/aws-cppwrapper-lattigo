// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "cgo/bootstrap.h"
#include "latticpp/marshal/gohandle.h"

namespace latticpp {

Bootstrapper newBootstrapper(const Parameters& params,
                             const BootstrappingParameters& bootParams,
                             const EvaluationKey& bootKey);

Ciphertext bootstrap(const Bootstrapper& btp, const Ciphertext& ct);
}  // namespace latticpp

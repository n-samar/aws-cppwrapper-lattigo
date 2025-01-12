// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "bootstrap.h"

using namespace std;

namespace latticpp {

Bootstrapper newBootstrapper(const Parameters& params,
                             const BootstrappingParameters& bootParams,
                             const SecretKey& sk) {
  return Bootstrapper(lattigo_newBootstrapper(
      params.getRawHandle(), bootParams.getRawHandle(), sk.getRawHandle()));
}

Ciphertext bootstrap(const Bootstrapper& btp, const Ciphertext& ct) {
  return Ciphertext(ct.GetLattigoParam(),
                    lattigo_bootstrap(btp.getRawHandle(), ct.getRawHandle()));
}
}  // namespace latticpp

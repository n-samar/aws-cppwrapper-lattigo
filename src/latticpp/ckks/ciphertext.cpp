// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "ciphertext.h"

#include "latticpp/ckks/lattigo_param.h"

namespace latticpp {

uint64_t level(const Ciphertext& ct) {
  return lattigo_level(ct.getRawHandle());
}

double scale(const Ciphertext& ct) {
  return lattigo_ciphertextScale(ct.getRawHandle());
}

Ciphertext copyNew(const Ciphertext& ct) {
  // a handle of 0 is an invalid Go reference (my equivalent of a nil/null
  // pointer)
  if (ct.getRawHandle() == 0) {
    return ct;
  }
  return Ciphertext(ct.GetLattigoParam(), lattigo_copyNew(ct.getRawHandle()));
}

Ciphertext newCiphertext(const LattigoParam& param, const Parameters& params,
                         uint64_t degree, uint64_t level, double scale) {
  return Ciphertext(param, lattigo_newCiphertext(params.getRawHandle(), degree,
                                                 level, scale));
}
}  // namespace latticpp

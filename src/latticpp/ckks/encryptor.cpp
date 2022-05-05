// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "encryptor.h"

namespace latticpp {

Encryptor newEncryptorFromPk(const Parameters& params, const PublicKey& pk) {
  return Encryptor(
      lattigo_newEncryptorFromPk(params.getRawHandle(), pk.getRawHandle()));
}

Ciphertext encryptNew(const LattigoParam& param, const Encryptor& encryptor,
                      const Plaintext& pt) {
  return Ciphertext(
      param, lattigo_encryptNew(encryptor.getRawHandle(), pt.getRawHandle()));
}
}  // namespace latticpp

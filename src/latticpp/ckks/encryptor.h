// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "cgo/encryptor.h"
#include "latticpp/ckks/lattigo_param.h"
#include "latticpp/marshal/gohandle.h"

namespace latticpp {

Encryptor newEncryptorFromPk(const Parameters& params, const PublicKey& pk);

Ciphertext encryptNew(const LattigoParam& param, const Encryptor& encryptor,
                      const Plaintext& pt);
}  // namespace latticpp

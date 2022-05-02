// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <vector>

#include "cgo/keygen.h"
#include "latticpp/marshal/gohandle.h"

namespace latticpp {

struct KeyPairHandle {
  SecretKey sk;
  PublicKey pk;
};

KeyGenerator newKeyGenerator(const Parameters& params);

KeyPairHandle genKeyPair(const KeyGenerator& keygen);

KeyPairHandle genKeyPairSparse(const KeyGenerator& keygen, uint64_t hw);

RelinearizationKey genRelinKey(const KeyGenerator& keygen, const SecretKey& sk);

RotationKeys genRotationKeysForRotations(const KeyGenerator& keygen,
                                         const SecretKey& sk,
                                         std::vector<int> shifts);

EvaluationKey makeEvaluationKey(const RelinearizationKey& relinKey,
                                const RotationKeys& rotKeys);

EvaluationKey genBootstrappingKey(const BootstrappingParameters& bootParams,
                                  const Parameters& params,
                                  const SecretKey& sk);

EvaluationKey makeBootstrappingKey(const RelinearizationKey& relinKey,
                                   const RotationKeys& rotKeys);

}  // namespace latticpp

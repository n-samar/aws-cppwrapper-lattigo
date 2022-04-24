// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <vector>

#include "cgo/evaluator.h"
#include "latticpp/marshal/gohandle.h"

namespace latticpp {

Evaluator newEvaluator(const Parameters& params, const EvaluationKey& evakey);

void rotate(const Evaluator& eval, const Ciphertext& ctIn, uint64_t k,
            Ciphertext& ctOut);

std::vector<Ciphertext> rotateHoisted(const Evaluator& eval,
                                      const Ciphertext& ctIn,
                                      std::vector<uint64_t> ks);

void multByConst(const Evaluator& eval, const Ciphertext& ctIn, double constant,
                 Ciphertext& ctOut);

void addConst(const Evaluator& eval, const Ciphertext& ctIn, double constant,
              Ciphertext& ctOut);

void rescale(const Evaluator& eval, const Ciphertext& ctIn, double threshold,
             Ciphertext& ctOut);

void rescaleMany(const Evaluator& eval, const Parameters& params,
                 const Ciphertext& ctIn, uint64_t numRescales,
                 Ciphertext& ctOut);

Ciphertext mulRelinNew(const Evaluator& eval, const Ciphertext& ct0,
                       const Ciphertext& ct1);

void mulRelin(const Evaluator& eval, const Ciphertext& ct0,
              const Ciphertext& ct1, Ciphertext& ctOut);

void mul(const Evaluator& eval, const Ciphertext& ct0, const Ciphertext& ct1,
         Ciphertext& ctOut);

void mulPlain(const Evaluator& eval, const Ciphertext& ctIn,
              const Plaintext& pt, Ciphertext& ctOut);

void add(const Evaluator& eval, const Ciphertext& ct0, const Ciphertext& ct1,
         Ciphertext& ctOut);

void addPlain(const Evaluator& eval, const Ciphertext& ctIn,
              const Plaintext& pt, Ciphertext& ctOut);

void neg(const Evaluator& eval, const Ciphertext& ctIn, Ciphertext& ctOut);

void sub(const Evaluator& eval, const Ciphertext& ct0, const Ciphertext& ct1,
         Ciphertext& ctOut);

void subPlain(const Evaluator& eval, const Ciphertext& ctIn,
              const Plaintext& pt, Ciphertext& ctOut);

void multByGaussianIntegerAndAdd(const Evaluator& eval, const Ciphertext& ctIn,
                                 uint64_t cReal, uint64_t cImag,
                                 Ciphertext& ctOut);

void dropLevel(const Evaluator& eval, Ciphertext& ct, uint64_t levels);

void relinearize(const Evaluator& eval, const Ciphertext& ctIn,
                 Ciphertext& ctOut);

void setScale(const Evaluator& eval, const Ciphertext& ct, double scale);

}  // namespace latticpp

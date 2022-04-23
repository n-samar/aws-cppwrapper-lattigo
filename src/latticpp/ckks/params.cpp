// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "params.h"

using namespace std;

namespace latticpp {

Parameters getDefaultClassicalParams(NamedClassicalParams paramId) {
  return Parameters(lattigo_getDefaultClassicalParams(paramId));
}

Parameters getDefaulPQParams(NamedPQParams paramId) {
  return Parameters(lattigo_getDefaultPQParams(paramId));
}

Parameters newParametersFromLogModuli(uint64_t logN,
                                      const vector<uint8_t>& logQi,
                                      const vector<uint8_t>& logPi,
                                      uint8_t logScale) {
  if (logQi.size() > 255 || logPi.size() > 255) {
    throw invalid_argument(
        "newParametersFromLogModuli requires <=255 primes of each type.");
  }
  return Parameters(lattigo_newParametersFromLogModuli(
      logN, logQi.data(), logQi.size(), logPi.data(), logPi.size(), logScale));
}

uint64_t numSlots(const Parameters& params) {
  return lattigo_numSlots(params.getRawHandle());
}

uint64_t logN(const Parameters& params) {
  return lattigo_logN(params.getRawHandle());
}

uint64_t logQP(const Parameters& params) {
  return lattigo_logQP(params.getRawHandle());
}

uint64_t maxLevel(const Parameters& params) {
  return lattigo_maxLevel(params.getRawHandle());
}

double scale(const Parameters& params) {
  return lattigo_paramsScale(params.getRawHandle());
}

double sigma(const Parameters& params) {
  return lattigo_sigma(params.getRawHandle());
}

uint64_t qi(const Parameters& params, uint64_t i) {
  return lattigo_getQi(params.getRawHandle(), i);
}

uint64_t pi(const Parameters& params, uint64_t i) {
  return lattigo_getPi(params.getRawHandle(), i);
}

uint64_t qiCount(const Parameters& params) {
  return lattigo_qiCount(params.getRawHandle());
}

uint64_t piCount(const Parameters& params) {
  return lattigo_piCount(params.getRawHandle());
}

uint64_t logQLvl(const Parameters& params, uint64_t lvl) {
  return lattigo_logQLvl(params.getRawHandle(), lvl);
}

uint64_t logSlots(const Parameters& params) {
  return lattigo_logSlots(params.getRawHandle());
}
}  // namespace latticpp

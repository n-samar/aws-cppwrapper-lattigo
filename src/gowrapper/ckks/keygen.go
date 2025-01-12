// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

package ckks

// cgo will automatically generate a struct for functions which return multiple values,
// but the auto-generated struct with generated names loses its semantic value. We opt
// to define our own struct here.

/*
#include "stdint.h"
struct Lattigo_KeyPairHandle {
  uint64_t sk;
  uint64_t pk;
};
*/
import "C"

import (
	"github.com/tuneinsight/lattigo/v4/ckks"
	"github.com/tuneinsight/lattigo/v4/ckks/bootstrapping"
	"github.com/tuneinsight/lattigo/v4/rlwe"
	"lattigo-cpp/marshal"
	"unsafe"
)

// https://github.com/golang/go/issues/35715#issuecomment-791039692
type Handle5 = uint64

func getStoredKeyGenerator(keygenHandle Handle5) *rlwe.KeyGenerator {
	ref := marshal.CrossLangObjMap.Get(keygenHandle)
	return (*rlwe.KeyGenerator)(ref.Ptr)
}

func getStoredSecretKey(skHandle Handle5) *rlwe.SecretKey {
	ref := marshal.CrossLangObjMap.Get(skHandle)
	return (*rlwe.SecretKey)(ref.Ptr)
}

func getStoredPublicKey(pkHandle Handle5) *rlwe.PublicKey {
	ref := marshal.CrossLangObjMap.Get(pkHandle)
	return (*rlwe.PublicKey)(ref.Ptr)
}

func getStoredEvaluationKey(evalKeyHandle Handle5) *rlwe.EvaluationKey {
	ref := marshal.CrossLangObjMap.Get(evalKeyHandle)
	return (*rlwe.EvaluationKey)(ref.Ptr)
}

func getStoredRelinKey(relinKeyHandle Handle5) *rlwe.RelinearizationKey {
	ref := marshal.CrossLangObjMap.Get(relinKeyHandle)
	return (*rlwe.RelinearizationKey)(ref.Ptr)
}

func getStoredRotationKeys(rotKeysHandle Handle5) *rlwe.RotationKeySet {
	ref := marshal.CrossLangObjMap.Get(rotKeysHandle)
	return (*rlwe.RotationKeySet)(ref.Ptr)
}

func getStoredBootstrappingKey(bootKeyHandle Handle5) *rlwe.EvaluationKey {
	ref := marshal.CrossLangObjMap.Get(bootKeyHandle)
	return (*rlwe.EvaluationKey)(ref.Ptr)
}

//export lattigo_newKeyGenerator
func lattigo_newKeyGenerator(paramHandle Handle5) Handle5 {
	paramPtr := getStoredParameters(paramHandle)
	var keyGenerator rlwe.KeyGenerator
	keyGenerator = ckks.NewKeyGenerator(*paramPtr)
	return marshal.CrossLangObjMap.Add(unsafe.Pointer(&keyGenerator))
}

//export lattigo_genKeyPair
func lattigo_genKeyPair(keygenHandle Handle5) C.struct_Lattigo_KeyPairHandle {
	var keygen *rlwe.KeyGenerator
	keygen = getStoredKeyGenerator(keygenHandle)
	var sk *rlwe.SecretKey
	var pk *rlwe.PublicKey
	sk, pk = (*keygen).GenKeyPair()
	var kpHandle C.struct_Lattigo_KeyPairHandle
	kpHandle.sk = C.uint64_t(marshal.CrossLangObjMap.Add(unsafe.Pointer(sk)))
	kpHandle.pk = C.uint64_t(marshal.CrossLangObjMap.Add(unsafe.Pointer(pk)))
	return kpHandle
}

// only generates relinearization keys for ciphertexts up to degree 2
// (i.e., you must relinearize after each ct/ct multiplication)
//
//export lattigo_genRelinearizationKey
func lattigo_genRelinearizationKey(keygenHandle Handle5, skHandle Handle5) Handle5 {
	var keygen *rlwe.KeyGenerator
	keygen = getStoredKeyGenerator(keygenHandle)
	var sk *rlwe.SecretKey
	sk = getStoredSecretKey(skHandle)
	return marshal.CrossLangObjMap.Add(unsafe.Pointer((*keygen).GenRelinearizationKey(sk, 2)))
}

// Positive k is for left rotation by k positions
// Negative k is equivalent to a right rotation by k positions
//
//export lattigo_genRotationKeysForRotations
func lattigo_genRotationKeysForRotations(keygenHandle Handle5, skHandle Handle5, ks *C.int64_t, ksLen uint64) Handle5 {
	var keygen *rlwe.KeyGenerator
	keygen = getStoredKeyGenerator(keygenHandle)

	var sk *rlwe.SecretKey
	sk = getStoredSecretKey(skHandle)

	rotations := make([]int, ksLen)
	size := unsafe.Sizeof(uint64(0))
	basePtrIn := uintptr(unsafe.Pointer(ks))
	for i := range rotations {
		rotations[i] = int(*(*int64)(unsafe.Pointer(basePtrIn + size*uintptr(i))))
	}

	var rotKeys *rlwe.RotationKeySet
	// The second argument determines if conjugation keys are generated or not. This wrapper API does
	// not support generating a conjugation key.
	rotKeys = (*keygen).GenRotationKeysForRotations(rotations, false, sk)
	return marshal.CrossLangObjMap.Add(unsafe.Pointer(rotKeys))
}

//export lattigo_makeEvaluationKey
func lattigo_makeEvaluationKey(relinKeyHandle Handle5, rotKeyHandle Handle5) Handle5 {
	var relinKey *rlwe.RelinearizationKey
	relinKey = getStoredRelinKey(relinKeyHandle)

	var rotKeys *rlwe.RotationKeySet
	rotKeys = getStoredRotationKeys(rotKeyHandle)

	var evalKey rlwe.EvaluationKey
	evalKey = rlwe.EvaluationKey{Rlk: relinKey, Rtks: rotKeys}

	return marshal.CrossLangObjMap.Add(unsafe.Pointer(&evalKey))
}

// Generates any missing Galois keys
//
//export lattigo_genBootstrappingKey
func lattigo_genBootstrappingKey(btpParamsHandle Handle5, paramHandle Handle5, skHandle Handle5) Handle5 {

	var params *ckks.Parameters
	params = getStoredParameters(paramHandle)

	var btpParams *bootstrapping.Parameters
	btpParams = getStoredBootstrappingParameters(btpParamsHandle)

	var sk *rlwe.SecretKey
	sk = getStoredSecretKey(skHandle)

	var result bootstrapping.EvaluationKeys
	result = bootstrapping.GenEvaluationKeys(*btpParams, *params, sk)
	return marshal.CrossLangObjMap.Add(unsafe.Pointer(&result))
}

//export lattigo_makeBootstrappingKey
func lattigo_makeBootstrappingKey(relinKeyHandle Handle5, rotKeyHandle Handle5) Handle5 {
	// get existing keys
	var relinKey *rlwe.RelinearizationKey
	relinKey = getStoredRelinKey(relinKeyHandle)

	var rotKeys *rlwe.RotationKeySet
	rotKeys = getStoredRotationKeys(rotKeyHandle)

	var btpKey rlwe.EvaluationKey
	btpKey = rlwe.EvaluationKey{Rlk: relinKey, Rtks: rotKeys}

	return marshal.CrossLangObjMap.Add(unsafe.Pointer(&btpKey))
}

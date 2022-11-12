// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

package ckks

import "C"

import (
	"github.com/tuneinsight/lattigo/v4/ckks"
	"github.com/tuneinsight/lattigo/v4/ckks/bootstrapping"
	"lattigo-cpp/marshal"
	"unsafe"
)

// https://github.com/golang/go/issues/35715#issuecomment-791039692
type Handle11 = uint64

func getStoredBootstrappingParameters(bootParamHandle Handle11) *bootstrapping.Parameters {
	ref := marshal.CrossLangObjMap.Get(bootParamHandle)
	return (*bootstrapping.Parameters)(ref.Ptr)
}

//export lattigo_getBootstrappingParams
func lattigo_getBootstrappingParams(logN uint64, logScale uint64, usableLevels uint64, bootstrappingPrecision uint64) Handle11 {
	bootParams := bootstrapping.MakeFrontendParameters(logN, logScale, usableLevels, bootstrappingPrecision).GetDefaultParametersSparse().BootstrappingParams
	return marshal.CrossLangObjMap.Add(unsafe.Pointer(&bootParams))
}

//export lattigo_getDefaultCKKSParams
func lattigo_getDefaultCKKSParams(logN uint64, logScale uint64, usableLevels uint64, bootstrappingPrecision uint64) Handle11 {
	scheme_params := bootstrapping.MakeFrontendParameters(logN, logScale, usableLevels, bootstrappingPrecision).GetDefaultParametersSparse().SchemeParams
	params, err := ckks.NewParametersFromLiteral(scheme_params)
	if err != nil {
		panic(err)
	}
	return marshal.CrossLangObjMap.Add(unsafe.Pointer(&params))
}

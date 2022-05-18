// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

package ckks

import "C"

import (
	"errors"
	"github.com/tuneinsight/lattigo/v3/ckks"
	"github.com/tuneinsight/lattigo/v3/ckks/bootstrapping"
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
	for i := 0; i < len(bootstrapping.DefaultParametersSparse); i++ {
		candidate := bootstrapping.DefaultParametersSparse[i].SchemeParams
		if logN == uint64(candidate.LogN) && logScale == candidate.LogScale && usableLevels == candidate.UsableLevels && bootstrappingPrecision == candidate.BootstrappingPrecision {
			bootParams := &bootstrapping.DefaultParametersSparse[i].BootstrappingParams
			return marshal.CrossLangObjMap.Add(unsafe.Pointer(bootParams))
		}
	}
	panic(errors.New("The requested set of bootstrapping.Parameters does not exist"))
}

//export lattigo_getDefaultCKKSParams
func lattigo_getDefaultCKKSParams(logN uint64, logScale uint64, usableLevels uint64, bootstrappingPrecision uint64) Handle11 {
	for i := 0; i < len(bootstrapping.DefaultParametersSparse); i++ {
		candidate := bootstrapping.DefaultParametersSparse[i].SchemeParams
		if logN == uint64(candidate.LogN) && logScale == candidate.LogScale && usableLevels == candidate.UsableLevels && bootstrappingPrecision == candidate.BootstrappingPrecision {
			scheme_params := &bootstrapping.DefaultParametersSparse[i].SchemeParams
			params, err := ckks.NewParametersFromLiteral(*scheme_params)
			if err != nil {
				panic(err)
			}
			return marshal.CrossLangObjMap.Add(unsafe.Pointer(&params))
		}
	}
	panic(errors.New("The requested set of bootstrapping.Parameters does not exist"))
}

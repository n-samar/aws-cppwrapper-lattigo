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
func lattigo_getBootstrappingParams(bootParamEnum uint8) Handle11 {
	if int(bootParamEnum) >= len(bootstrapping.DefaultParametersSparse) {
		panic(errors.New("bootstrapping parameter enum index out of bounds"))
	}

	var bootParams *bootstrapping.Parameters
	bootParams = &bootstrapping.DefaultParametersSparse[bootParamEnum].BootstrappingParams

	return marshal.CrossLangObjMap.Add(unsafe.Pointer(bootParams))
}

//export lattigo_getDefaultCKKSParams
func lattigo_getDefaultCKKSParams(bootParamEnum uint8) Handle11 {
	if int(bootParamEnum) >= len(bootstrapping.DefaultParametersSparse) {
		panic(errors.New("bootstrapping parameter enum index out of bounds"))
	}
	scheme_params := &bootstrapping.DefaultParametersSparse[bootParamEnum].SchemeParams
	params, err := ckks.NewParametersFromLiteral(*scheme_params)
	if err != nil {
		panic(err)
	}
	marshal.CrossLangObjMap.Add(unsafe.Pointer(scheme_params))
	return marshal.CrossLangObjMap.Add(unsafe.Pointer(&params))
}

/*******************************************************************************
 * Copyright (c) 2015-2018 Skymind, Inc.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License, Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/

/*
 * transform.h
 *
 *  Created on: Dec 28, 2015
 *  @author: agibsonccc
 *  @author: raver119@gmail.com
 */

#ifndef TRANSFORM_STRICT_H_
#define TRANSFORM_STRICT_H_
#include <vector>
#include <templatemath.h>
#include <ops/ops.h>

#ifdef _OPENMP
#include <omp.h>
#endif
#include <pairwise_util.h>
#include <dll.h>

//#include <loops/reduce.h>
//#include <loops/scalar.h>
//#include <loops/indexreduce.h>
//#include <loops/broadcasting.h>

#ifdef __CUDACC__
#include <cuda.h>
#include <cuda_runtime.h>
#endif

#include "legacy_ops.h"


namespace functions {
    namespace transform {

        template<typename X>
        class TransformStrict {
        public:

#ifdef __CUDACC__

	template<typename OpType>
	static  __device__ void transformCuda(
			void *dy,
			Nd4jLong *shapeInfo,
			void *params,
			void *result,
			Nd4jLong *resultShapeInfo,
			int *allocationPointer,
			void *reductionPointer,
			Nd4jLong *tadShapeInfo,
			Nd4jLong *tadOffsets);


	template <typename OpType>
	static _CUDA_H void intermediateShaped(dim3 launchDims, cudaStream_t *stream, void *x, Nd4jLong *xShape, int xRank, void *extraParams, void *z, Nd4jLong *zShape, int zRank, int *allocationPointer, void *reductionPointer,  Nd4jLong *tadShapeInfo, Nd4jLong *tadOffsets);

	static _CUDA_H void executeTransformShaped(dim3 launchDims, cudaStream_t *stream, int opNum, void *x, Nd4jLong *xShape, int xRank, void *extraParams, void *z, Nd4jLong *zShape, int zRank, int *allocationPointer, void *reductionPointer,  Nd4jLong *tadShapeInfo, Nd4jLong *tadOffsets);

#else



			static void exec(int opNum, void *dx, Nd4jLong *xShapeInfo, void *result, Nd4jLong *resultShapeInfo, void *extraParams, uint64_t threadId, uint64_t numThreads);

			template<typename OpType>
			static ND4J_EXPORT void exec(void *dx, Nd4jLong *xShapeInfo, void *result, Nd4jLong *resultShapeInfo, void *extraParams, uint64_t threadId, uint64_t numThreads);

#endif
        };
    }
}


#endif /* TRANSFORM_H_ */

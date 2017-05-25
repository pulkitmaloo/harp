/* file: maximum_pooling3d_layer_types.h */
/*******************************************************************************
* Copyright 2014-2016 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Implementation of maximum 3D pooling layer.
//--
*/

#ifndef __MAXIMUM_POOLING3D_LAYER_TYPES_H__
#define __MAXIMUM_POOLING3D_LAYER_TYPES_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "data_management/data/homogen_tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/pooling3d/pooling3d_layer_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
/**
 * @defgroup maximum_pooling3d Three-dimensional Max Pooling Layer
 * \copydoc daal::algorithms::neural_networks::layers::maximum_pooling3d
 * @ingroup pooling3d
 * @{
 */
namespace maximum_pooling3d
{
/**
 * <a name="DAAL-ENUM-ALGORITHMS__NEURAL_NETWORKS__LAYERS__MAXIMUM_POOLING3D__METHOD"></a>
 * \brief Computation methods for the maximum 3D pooling layer
 */
enum Method
{
    defaultDense = 0    /*!< Default: performance oriented method */
};

/**
 * \brief Identifiers of input tensors for the backward maximum 3D pooling layer
 *        and results for the forward maximum 3D pooling layer
 */
enum LayerDataId
{
    auxSelectedIndices = 0,         /*!< p-dimensional tensor that stores the positions of maximum elements */
};

/**
 * \brief Identifiers of input numeric tables for the backward maximum 3D pooling layer
 *        and results for the forward maximum 3D pooling layer
 */
enum LayerDataNumericTableId
{
    auxInputDimensions  = 1,         /*!< Numeric table of size 1 x p that contains the sizes
                                          of the dimensions of the input data tensor */
};

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-STRUCT-ALGORITHMS__NEURAL_NETWORKS__LAYERS__MAXIMUM_POOLING3D__PARAMETER"></a>
 * \brief Parameters for the maximum 3D pooling layer
 *
 * \snippet neural_networks/layers/pooling3d/maximum_pooling3d_layer_types.h Parameter source code
 */
/* [Parameter source code] */
struct Parameter: public layers::pooling3d::Parameter
{
    /**
     * Constructs the parameters of 3D pooling layer
     * \param[in] firstIndex        Index of the first of three dimensions on which the pooling is performed
     * \param[in] secondIndex       Index of the second of three dimensions on which the pooling is performed
     * \param[in] thirdIndex        Index of the third of three dimensions on which the pooling is performed
     * \param[in] firstKernelSize   Size of the first dimension of 3D subtensor for which the maximum element is selected
     * \param[in] secondKernelSize  Size of the second dimension of 3D subtensor for which the maximum element is selected
     * \param[in] thirdKernelSize   Size of the third dimension of 3D subtensor for which the maximum element is selected
     * \param[in] firstStride       Interval over the first dimension on which the pooling is performed
     * \param[in] secondStride      Interval over the second dimension on which the pooling is performed
     * \param[in] thirdStride       Interval over the third dimension on which the pooling is performed
     * \param[in] firstPadding      Number of data elements to implicitly add to the the first dimension
     *                              of the 3D subtensor on which the pooling is performed
     * \param[in] secondPadding     Number of data elements to implicitly add to the the second dimension
     *                              of the 3D subtensor on which the pooling is performed
     * \param[in] thirdPadding      Number of data elements to implicitly add to the the third dimension
     *                              of the 3D subtensor on which the pooling is performed
     */
    Parameter(size_t firstIndex, size_t secondIndex, size_t thirdIndex,
    size_t firstKernelSize = 2, size_t secondKernelSize = 2, size_t thirdKernelSize = 2,
              size_t firstStride = 2, size_t secondStride = 2, size_t thirdStride = 2,
              size_t firstPadding = 0, size_t secondPadding = 0, size_t thirdPadding = 0) :
        layers::pooling3d::Parameter(firstIndex, secondIndex, thirdIndex,
                                     firstKernelSize, secondKernelSize, thirdKernelSize,
                                     firstStride, secondStride, thirdStride,
                                     firstPadding, secondPadding, thirdPadding)
    {}
};
/* [Parameter source code] */

} // interface1
using interface1::Parameter;

} // namespace maximum_pooling3d
/** @} */
} // namespace layers
} // namespace neural_networks
} // namespace algorithm
} // namespace daal

#endif

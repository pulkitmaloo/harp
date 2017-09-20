/* file: ridge_regression_train_container.h */
/*******************************************************************************
* Copyright 2014-2017 Intel Corporation
* All Rights Reserved.
*
* If this  software was obtained  under the  Intel Simplified  Software License,
* the following terms apply:
*
* The source code,  information  and material  ("Material") contained  herein is
* owned by Intel Corporation or its  suppliers or licensors,  and  title to such
* Material remains with Intel  Corporation or its  suppliers or  licensors.  The
* Material  contains  proprietary  information  of  Intel or  its suppliers  and
* licensors.  The Material is protected by  worldwide copyright  laws and treaty
* provisions.  No part  of  the  Material   may  be  used,  copied,  reproduced,
* modified, published,  uploaded, posted, transmitted,  distributed or disclosed
* in any way without Intel's prior express written permission.  No license under
* any patent,  copyright or other  intellectual property rights  in the Material
* is granted to  or  conferred  upon  you,  either   expressly,  by implication,
* inducement,  estoppel  or  otherwise.  Any  license   under such  intellectual
* property rights must be express and approved by Intel in writing.
*
* Unless otherwise agreed by Intel in writing,  you may not remove or alter this
* notice or  any  other  notice   embedded  in  Materials  by  Intel  or Intel's
* suppliers or licensors in any way.
*
*
* If this  software  was obtained  under the  Apache License,  Version  2.0 (the
* "License"), the following terms apply:
*
* You may  not use this  file except  in compliance  with  the License.  You may
* obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*
* Unless  required  by   applicable  law  or  agreed  to  in  writing,  software
* distributed under the License  is distributed  on an  "AS IS"  BASIS,  WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
* See the   License  for the   specific  language   governing   permissions  and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Implementation of ridge regression container.
//--
*/

#ifndef __RIDGE_REGRESSION_TRAIN_CONTAINER_H__
#define __RIDGE_REGRESSION_TRAIN_CONTAINER_H__

#include "kernel.h"
#include "data_management/data/numeric_table.h"
#include "services/daal_shared_ptr.h"
#include "ridge_regression_training_batch.h"
#include "ridge_regression_training_online.h"
#include "ridge_regression_training_distributed.h"
#include "ridge_regression_train_kernel.h"

namespace daal
{
namespace algorithms
{
namespace ridge_regression
{
namespace training
{

/**
 *  \brief Initialize list of ridge regression kernels with implementations for supported architectures
 */
template <typename algorithmFpType, training::Method method, CpuType cpu>
BatchContainer<algorithmFpType, method, cpu>::BatchContainer(daal::services::Environment::env *daalEnv)
{
    __DAAL_INITIALIZE_KERNELS(internal::RidgeRegressionTrainBatchKernel, algorithmFpType, method);
}

template <typename algorithmFpType, training::Method method, CpuType cpu>
BatchContainer<algorithmFpType, method, cpu>::~BatchContainer()
{
    __DAAL_DEINITIALIZE_KERNELS();
}

/**
 *  \brief Choose appropriate kernel to calculate ridge regression model.
 */
template <typename algorithmFpType, training::Method method, CpuType cpu>
services::Status BatchContainer<algorithmFpType, method, cpu>::compute()
{
    Input * const input = static_cast<Input *>(_in);
    Result * const result = static_cast<Result *>(_res);

    NumericTable *x = input->get(data).get();
    NumericTable *y = input->get(dependentVariables).get();

    ridge_regression::Model *r = result->get(model).get();

    daal::algorithms::Parameter * const par = _par;
    daal::services::Environment::env & env = *_env;

    __DAAL_CALL_KERNEL(env, internal::RidgeRegressionTrainBatchKernel, __DAAL_KERNEL_ARGUMENTS(algorithmFpType, method),    \
            compute, x, y, r, par);
}

/**
 *  \brief Initialize list of ridge regression kernels with implementations for supported architectures
 */
template <typename algorithmfptype, training::Method method, CpuType cpu>
OnlineContainer<algorithmfptype, method, cpu>::OnlineContainer(daal::services::Environment::env * daalEnv)
{
    __DAAL_INITIALIZE_KERNELS(internal::RidgeRegressionTrainOnlineKernel, algorithmfptype, method);
}

template <typename algorithmfptype, training::Method method, CpuType cpu>
OnlineContainer<algorithmfptype, method, cpu>::~OnlineContainer()
{
    __DAAL_DEINITIALIZE_KERNELS();
}

/**
 *  \brief Choose appropriate kernel to calculate ridge regression model.
 */
template <typename algorithmfptype, training::Method method, CpuType cpu>
services::Status OnlineContainer<algorithmfptype, method, cpu>::compute()
{
    Input * const input = static_cast<Input *>(_in);
    PartialResult * const partialResult = static_cast<PartialResult *>(_pres);

    NumericTable *x = input->get(data).get();
    NumericTable *y = input->get(dependentVariables).get();

    ridge_regression::Model *partialModel = partialResult->get(training::partialModel).get();

    daal::algorithms::Parameter * const par = _par;
    daal::services::Environment::env & env = *_env;

    __DAAL_CALL_KERNEL(env, internal::RidgeRegressionTrainOnlineKernel, __DAAL_KERNEL_ARGUMENTS(algorithmfptype, method),   \
            compute, x, y, partialModel, par);
}

/**
 *  \brief Choose appropriate kernel to calculate ridge regression model.
 */
template <typename algorithmfptype, training::Method method, CpuType cpu>
services::Status OnlineContainer<algorithmfptype, method, cpu>::finalizeCompute()
{
    PartialResult * const partialResult = static_cast<PartialResult *>(_pres);
    Result * const result = static_cast<Result *>(_res);

    ridge_regression::Model *partialModel = partialResult->get(training::partialModel).get();
    ridge_regression::Model *model = result->get(training::model).get();

    daal::algorithms::Parameter * const par = _par;
    daal::services::Environment::env & env = *_env;

    __DAAL_CALL_KERNEL(env, internal::RidgeRegressionTrainOnlineKernel, __DAAL_KERNEL_ARGUMENTS(algorithmfptype, method),   \
            finalizeCompute, partialModel, model, par);
}

/**
 *  \brief Initialize list of ridge regression kernels with implementations for supported architectures
 */
template <typename algorithmFpType, training::Method method, CpuType cpu>
DistributedContainer<step2Master, algorithmFpType, method, cpu>::DistributedContainer(daal::services::Environment::env * daalEnv)
{
    __DAAL_INITIALIZE_KERNELS(internal::RidgeRegressionTrainDistributedKernel, algorithmFpType, method);
}

template <typename algorithmFpType, training::Method method, CpuType cpu>
DistributedContainer<step2Master, algorithmFpType, method, cpu>::~DistributedContainer()
{
    __DAAL_DEINITIALIZE_KERNELS();
}

/**
 *  \brief Choose appropriate kernel to calculate ridge regression model.
 */
template <typename algorithmFpType, training::Method method, CpuType cpu>
services::Status DistributedContainer<step2Master, algorithmFpType, method, cpu>::compute()
{
    DistributedInput<step2Master> * const input = static_cast<DistributedInput<step2Master> *>(_in);
    PartialResult * const partialResult = static_cast<PartialResult *>(_pres);

    data_management::DataCollection * const collection
        = static_cast<data_management::DataCollection* >(input->get(partialModels).get());
    const size_t n = collection->size();

    daal::algorithms::Model ** const localModels = new daal::algorithms::Model*[n];
    for(size_t i = 0; i < n; ++i)
    {
        localModels[i] = static_cast<daal::algorithms::Model *>((*collection)[i].get());
    }

    daal::algorithms::Model * const partialModel = static_cast<daal::algorithms::Model *>(partialResult->get(training::partialModel).get());

    daal::algorithms::Parameter * const par = _par;
    daal::services::Environment::env & env = *_env;

    services::Status s = __DAAL_CALL_KERNEL_STATUS(env, internal::RidgeRegressionTrainDistributedKernel, __DAAL_KERNEL_ARGUMENTS(algorithmFpType, method),  \
            compute, n, localModels, partialModel, par);

    collection->clear();
    delete [] localModels;

    return s;
}

/**
 *  \brief Choose appropriate kernel to calculate ridge regression model.
 */
template <typename algorithmFpType, training::Method method, CpuType cpu>
services::Status DistributedContainer<step2Master, algorithmFpType, method, cpu>::finalizeCompute()
{
    PartialResult * const partialResult = static_cast<PartialResult *>(_pres);
    Result * const result = static_cast<Result *>(_res);

    ridge_regression::Model *partialModel = partialResult->get(training::partialModel).get();
    ridge_regression::Model *model = result->get(training::model).get();

    daal::algorithms::Parameter * const par = _par;
    daal::services::Environment::env & env = *_env;

    __DAAL_CALL_KERNEL(env, internal::RidgeRegressionTrainDistributedKernel, __DAAL_KERNEL_ARGUMENTS(algorithmFpType, method),  \
            finalizeCompute, partialModel, model, par);
}

} // namespace training
} // namespace ridge_regression
} // namespace algorithms
} // namespace daal

#endif
/*
 * Copyright 2009-2017 Alibaba Cloud All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <fstream>
#include <mutex>
#include <alibabacloud/oss/OssError.h>
#include <alibabacloud/oss/OssRequest.h>
#include "utils/Utils.h"

namespace AlibabaCloud
{
namespace OSS
{
    class ResumableBaseWorker
    {
    public:
        ResumableBaseWorker(uint64_t objectSize, uint64_t partSize);
        ResumableBaseWorker(const std::string& filePath, uint64_t partSize);

    protected:
        int validate(OssError& err);
        void determinePartSize();
        virtual const std::string getRecordPath() = 0;
        virtual int loadRecord() = 0;
        virtual int prepare(OssError& err) = 0;
        virtual int validateRecord() = 0;
        
        bool hasRecord_;
        std::string recordPath_;
        std::mutex lock_;
        uint64_t objectSize_;
        uint64_t consumedSize_;
        uint64_t partSize_;
    };
}
}
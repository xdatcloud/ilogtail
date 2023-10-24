/*
 * Copyright 2023 iLogtail Authors
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

#include <cstdint>
#include <string>

#include "json/json.h"

#include "common/LogstoreFeedbackKey.h"
#include "logger/Logger.h"
#include "models/PipelineEventGroup.h"
#include "monitor/LogtailAlarm.h"
#include "monitor/LogFileProfiler.h"
#include "pipeline/GlobalConfig.h"

namespace logtail {

class Pipeline;
class FlusherSLS;

// for compatiblity with shennong profile
struct ProcessProfile {
    int readBytes = 0;
    int skipBytes = 0;
    int feedLines = 0;
    int splitLines = 0;
    int parseFailures = 0;
    int regexMatchFailures = 0;
    int parseTimeFailures = 0;
    int historyFailures = 0;
    int logGroupSize = 0;

    void Reset() { memset(this, 0, sizeof(ProcessProfile)); }
};

class PipelineContext {
public:
    PipelineContext() {}
    PipelineContext(const PipelineContext&) = delete;
    PipelineContext(PipelineContext&&) = delete;
    PipelineContext operator=(const PipelineContext&) = delete;
    PipelineContext operator=(PipelineContext&&) = delete;

    const std::string& GetConfigName() const { return mConfigName; }
    void SetConfigName(const std::string& configName) { mConfigName = configName; }
    uint32_t GetCreateTime() const { return mCreateTime; }
    void SetCreateTime(uint32_t time) { mCreateTime = time; }
    const GlobalConfig& GetGlobalConfig() const { return mGlobalConfig; }
    bool InitGlobalConfig(const Json::Value& config, Json::Value& nonNativeParams) {
        return mGlobalConfig.Init(config, mConfigName, nonNativeParams);
    }
    const Pipeline& GetPipeline() const { return *mPipeline; }
    Pipeline& GetPipeline() { return *mPipeline; }
    void SetPipeline(Pipeline& pipeline) { mPipeline = &pipeline; }

    const std::string& GetProjectName() const;
    const std::string& GetLogstoreName() const;
    const std::string& GetRegion() const;
    LogstoreFeedBackKey GetLogstoreKey() const;
    const FlusherSLS* GetSLSInfo() const { return mSLSInfo; }
    void SetSLSInfo(const FlusherSLS* flusherSLS) { mSLSInfo = flusherSLS; }
    bool IsFirstProcessorJson() const { return mIsFirstProcessorJson; }
    void SetIsFirstProcessorJsonFlag(bool flag) { mIsFirstProcessorJson = flag; }

    // 过渡使用
    void SetProjectName(const std::string& projectName) { mProjectName = projectName; }
    void SetLogstoreName(const std::string& logstoreName) { mLogstoreName = logstoreName; }
    void SetRegion(const std::string& region) { mRegion = region; }

    ProcessProfile& GetProcessProfile() { return mProcessProfile; }
    // LogFileProfiler& GetProfiler() { return *mProfiler; }
    const Logger::logger& GetLogger() const { return mLogger; }
    LogtailAlarm& GetAlarm() const { return *mAlarm; };

private:
    static const std::string sEmptyString;

    std::string mConfigName;
    uint32_t mCreateTime;
    GlobalConfig mGlobalConfig;
    Pipeline* mPipeline = nullptr;

    const FlusherSLS* mSLSInfo = nullptr;
    bool mIsFirstProcessorJson = false;

    ProcessProfile mProcessProfile;
    // LogFileProfiler* mProfiler = LogFileProfiler::GetInstance();
    Logger::logger mLogger = sLogger;
    LogtailAlarm* mAlarm = LogtailAlarm::GetInstance();

    // 过渡使用
    std::string mProjectName, mLogstoreName, mRegion;
};

} // namespace logtail

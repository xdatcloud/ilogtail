// Copyright 2023 iLogtail Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <memory>

#include "unittest/plugin/PluginMock.h"
#include "plugin/instance/InputInstance.h"
#include "unittest/Unittest.h"

using namespace std;

namespace logtail {

class InputInstanceUnittest : public testing::Test {
public:
    void TestName() const;
    void TestInit() const;
    void TestStart() const;
    void TestStop() const;
};

void InputInstanceUnittest::TestName() const {
    unique_ptr<InputInstance> input = unique_ptr<InputInstance>(new InputInstance(new InputMock(), {"0", "0", "1"}));
    APSARA_TEST_EQUAL(InputMock::sName, input->Name());
}

void InputInstanceUnittest::TestInit() const {
    unique_ptr<InputInstance> input = unique_ptr<InputInstance>(new InputInstance(new InputMock(), {"0", "0", "1"}));
    Json::Value config, opt;
    PipelineContext context;
    APSARA_TEST_TRUE(input->Init(config, context, opt));
    APSARA_TEST_EQUAL(&context, &input->GetPlugin()->GetContext());
}

void InputInstanceUnittest::TestStart() const {
    unique_ptr<InputInstance> input = unique_ptr<InputInstance>(new InputInstance(new InputMock(), {"0", "0", "1"}));
    APSARA_TEST_TRUE(input->Start());
}

void InputInstanceUnittest::TestStop() const {
    unique_ptr<InputInstance> input = unique_ptr<InputInstance>(new InputInstance(new InputMock(), {"0", "0", "1"}));
    APSARA_TEST_TRUE(input->Stop(true));
}

UNIT_TEST_CASE(InputInstanceUnittest, TestName)
UNIT_TEST_CASE(InputInstanceUnittest, TestInit)
UNIT_TEST_CASE(InputInstanceUnittest, TestStart)
UNIT_TEST_CASE(InputInstanceUnittest, TestStop)

} // namespace logtail

UNIT_TEST_MAIN

/**
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "core/Processor.h"
#include "core/logging/LoggerConfiguration.h"

namespace org {
namespace apache {
namespace nifi {
namespace minifi {
namespace processors {

class PutDataframe : public core::Processor {
 public:
  static constexpr char const* ProcessorName = "PutDataframe";

  // Supported Properties
  static core::Property DestinationDataframe;

  // Supported Relationships
  static const core::Relationship Success;

  explicit PutDataframe(const std::string& name, const utils::Identifier& uuid = utils::Identifier()) :
      Processor(name, uuid),
      logger_(logging::LoggerFactory<PutDataframe>::getLogger()) {}

  virtual ~PutDataframe() = default;

 public:
  bool supportsDynamicProperties() override {
    return true;
  }
  /**
   * Function that's executed when the processor is scheduled.
   * @param context process context.
   * @param sessionFactory process session factory that is used when creating
   * ProcessSession objects.
   */
  void onSchedule(core::ProcessContext* context, core::ProcessSessionFactory* /* sessionFactory */) override;
  /**
   * Execution trigger for the RetryFlowFile Processor
   * @param context processor context
   * @param session processor session reference.
   */
  void onTrigger(core::ProcessContext* context, core::ProcessSession* session) override;

  // Initialize, overwrite by NiFi RetryFlowFile
  void initialize() override;

 private:

  std::string destination_dataframe_;

  std::shared_ptr<logging::Logger> logger_{logging::LoggerFactory<PutDataframe>::getLogger()};
};

REGISTER_RESOURCE(PutDataframe, "Places the contents of the incoming flowfile into the configured GPU dataframe."); // NOLINT

}  // namespace processors
}  // namespace minifi
}  // namespace nifi
}  // namespace apache
}  // namespace org

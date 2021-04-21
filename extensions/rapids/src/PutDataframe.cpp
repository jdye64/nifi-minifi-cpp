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

#include "PutDataframe.h"

#include <algorithm>
#include <limits>

#include "core/PropertyValidation.h"
#include "utils/ProcessorConfigUtils.h"
#include "utils/gsl.h"

namespace org {
namespace apache {
namespace nifi {
namespace minifi {
namespace processors {

core::Property PutDataframe::DestinationDataframe(core::PropertyBuilder::createProperty("Destination Dataframe")
  ->withDescription("Name of the existing dataframe that the flowfile contents should be written to")
  ->withDefaultValue("unknown", core::StandardValidators::get().NON_BLANK_VALIDATOR)
  ->supportsExpressionLanguage(true)
  ->isRequired(true)
  ->build());

const core::Relationship PutDataframe::Success("success", "Incoming flowfile has been written to destination dataframe");

void PutDataframe::initialize() {
  setSupportedProperties({
    DestinationDataframe,
  });
  setSupportedRelationships({
    Success,
  });
}

void PutDataframe::onSchedule(core::ProcessContext* context, core::ProcessSessionFactory* /* sessionFactory */) {
  gsl_Expects(context);

  // Required properties
  destination_dataframe_   = utils::getRequiredPropertyOrThrow(context, DestinationDataframe.getName());
}

void PutDataframe::onTrigger(core::ProcessContext* /* context */, core::ProcessSession* session) {
  std::unique_lock<std::mutex> lock(do_not_call_on_trigger_concurrently_);
  logger_->log_debug("PutDataframe onTrigger");
}

}  // namespace processors
}  // namespace minifi
}  // namespace nifi
}  // namespace apache
}  // namespace org

/*
 *
 * Copyright 2016 gRPC authors.
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
 *
 */

#ifndef GRPC_TEST_CPP_UTIL_CONFIG_GRPC_CLI_H
#define GRPC_TEST_CPP_UTIL_CONFIG_GRPC_CLI_H

#include <grpcpp/impl/codegen/config_protobuf.h>

#ifndef GRPC_CUSTOM_DYNAMICMESSAGEFACTORY
#include <google/protobuf/dynamic_message.h>
#define GRPC_CUSTOM_DYNAMICMESSAGEFACTORY \
  ::google::protobuf_inworld::DynamicMessageFactory
#endif

#ifndef GRPC_CUSTOM_DESCRIPTORPOOLDATABASE
#include <google/protobuf/descriptor.h>
#define GRPC_CUSTOM_DESCRIPTORPOOLDATABASE \
  ::google::protobuf_inworld::DescriptorPoolDatabase
#define GRPC_CUSTOM_MERGEDDESCRIPTORDATABASE \
  ::google::protobuf_inworld::MergedDescriptorDatabase
#endif

#ifndef GRPC_CUSTOM_TEXTFORMAT
#include <google/protobuf/text_format.h>
#define GRPC_CUSTOM_TEXTFORMAT ::google::protobuf_inworld::TextFormat
#endif

#ifndef GRPC_CUSTOM_DISKSOURCETREE
#include <google/protobuf/compiler/importer.h>
#define GRPC_CUSTOM_DISKSOURCETREE ::google::protobuf_inworld::compiler::DiskSourceTree
#define GRPC_CUSTOM_IMPORTER ::google::protobuf_inworld::compiler::Importer
#define GRPC_CUSTOM_MULTIFILEERRORCOLLECTOR \
  ::google::protobuf_inworld::compiler::MultiFileErrorCollector
#endif

namespace grpc {
namespace protobuf_inworld {

typedef GRPC_CUSTOM_DYNAMICMESSAGEFACTORY DynamicMessageFactory;

typedef GRPC_CUSTOM_DESCRIPTORPOOLDATABASE DescriptorPoolDatabase;
typedef GRPC_CUSTOM_MERGEDDESCRIPTORDATABASE MergedDescriptorDatabase;

typedef GRPC_CUSTOM_TEXTFORMAT TextFormat;

namespace compiler {
typedef GRPC_CUSTOM_DISKSOURCETREE DiskSourceTree;
typedef GRPC_CUSTOM_IMPORTER Importer;
typedef GRPC_CUSTOM_MULTIFILEERRORCOLLECTOR MultiFileErrorCollector;
}  // namespace compiler

}  // namespace protobuf_inworld
}  // namespace grpc

#endif  // GRPC_TEST_CPP_UTIL_CONFIG_GRPC_CLI_H

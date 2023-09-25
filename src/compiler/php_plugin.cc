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

// Generates PHP gRPC service interface out of Protobuf IDL.

#include <memory>

#include "src/compiler/config.h"
#include "src/compiler/php_generator.h"
#include "src/compiler/php_generator_helpers.h"

using google::protobuf_inworld::compiler::ParseGeneratorParameter;
using grpc_php_generator::GenerateFile;
using grpc_php_generator::GetPHPServiceFilename;

class PHPGrpcGenerator : public grpc::protobuf_inworld::compiler::CodeGenerator {
 public:
  PHPGrpcGenerator() {}
  ~PHPGrpcGenerator() {}

  uint64_t GetSupportedFeatures() const override {
    return FEATURE_PROTO3_OPTIONAL;
  }

  bool Generate(const grpc::protobuf_inworld::FileDescriptor* file,
                const std::string& parameter,
                grpc::protobuf_inworld::compiler::GeneratorContext* context,
                std::string* error) const override {
    if (file->service_count() == 0) {
      return true;
    }

    std::vector<std::pair<std::string, std::string> > options;
    ParseGeneratorParameter(parameter, &options);

    std::string class_suffix;
    for (size_t i = 0; i < options.size(); ++i) {
      if (options[i].first == "class_suffix") {
        class_suffix = options[i].second;
      } else {
        *error = "unsupported options: " + options[i].first;
        return false;
      }
    }

    for (int i = 0; i < file->service_count(); i++) {
      std::string code = GenerateFile(file, file->service(i), class_suffix);

      // Get output file name
      std::string file_name =
          GetPHPServiceFilename(file, file->service(i), class_suffix);

      std::unique_ptr<grpc::protobuf_inworld::io::ZeroCopyOutputStream> output(
          context->Open(file_name));
      grpc::protobuf_inworld::io::CodedOutputStream coded_out(output.get());
      coded_out.WriteRaw(code.data(), code.size());
    }

    return true;
  }
};

int main(int argc, char* argv[]) {
  PHPGrpcGenerator generator;
  return grpc::protobuf_inworld::compiler::PluginMain(argc, argv, &generator);
}

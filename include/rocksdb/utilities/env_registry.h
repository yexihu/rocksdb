// Copyright (c) 2016-present, Facebook, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.

#pragma once

#ifndef ROCKSDB_LITE

#include <functional>
#include <memory>
#include <string>

#include "rocksdb/env.h"

namespace rocksdb {

// Returns a new Env when called with a URI string.
typedef std::function<std::unique_ptr<Env>(const std::string&)> EnvFactoryFunc;

// Creates a new Env using the registered factory function corresponding to a
// prefix of uri. If no prefixes match, returns nullptr. If multiple prefixes
// match, the factory function used is unspecified.
std::unique_ptr<Env> NewEnvFromUri(const std::string& uri);

// To register an Env factory function, initialize an EnvRegistrar object with
// static storage duration. For example:
//
//   static EnvRegistrar hdfs_reg("hdfs://", &CreateHdfsEnv);
//
// Then, calling NewEnvFromUri("hdfs://some_path") will use CreateHdfsEnv to
// make a new Env.
class EnvRegistrar {
 public:
  explicit EnvRegistrar(std::string uri_prefix, EnvFactoryFunc env_factory);
};

}  // namespace rocksdb
#endif  // ROCKSDB_LITE

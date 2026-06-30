// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

// Author: kenton@google.com (Kenton Varda)

#include "google/protobuf/stubs/common.h"

#include <gtest/gtest.h>

#include <vector>

#include "absl/log/absl_log.h"
#include "absl/strings/ascii.h"
#include "absl/strings/substitute.h"
#include "google/protobuf/stubs/callback.h"
#include "google/protobuf/testing/googletest.h"

namespace google {
namespace protobuf {
namespace {

// TODO:  More tests.

#ifdef PACKAGE_VERSION  // only defined when using automake, not MSVC

TEST(VersionTest, VersionMatchesConfig) {
  // Verify that the version string specified in config.h matches the one
  // in common.h.  The config.h version is a string which may have a suffix
  // like "beta" or "rc1", so we remove that.
  std::string version = PACKAGE_VERSION;
  int pos = 0;
  while (pos < version.size() &&
         (absl::ascii_isdigit(version[pos]) || version[pos] == '.')) {
    ++pos;
  }
  version.erase(pos);

  EXPECT_EQ(version, internal::VersionString(GOOGLE_PROTOBUF_VERSION));
}

#endif  // PACKAGE_VERSION

TEST(CommonTest, IntMinMaxConstants) {
  // kint32min was declared incorrectly in the first release of protobufs.
  // Ugh.
  EXPECT_LT(kint32min, kint32max);
  EXPECT_EQ(static_cast<uint32>(kint32min), static_cast<uint32>(kint32max) + 1);
  EXPECT_LT(kint64min, kint64max);
  EXPECT_EQ(static_cast<uint64>(kint64min), static_cast<uint64>(kint64max) + 1);
  EXPECT_EQ(0, kuint32max + 1);
  EXPECT_EQ(0, kuint64max + 1);
}

}  // anonymous namespace
}  // namespace protobuf
}  // namespace google

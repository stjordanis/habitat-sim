// Copyright (c) Facebook, Inc. and its affiliates.
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#ifndef ESP_CORE_CONFIGURATION_H_
#define ESP_CORE_CONFIGURATION_H_

#include <Corrade/Utility/Configuration.h>
#include <Magnum/Magnum.h>
#include <Magnum/Math/ConfigurationValue.h>
#include <string>

#include "esp/core/esp.h"

namespace esp {
namespace core {

class Configuration {
 public:
  // virtual destructor set to that pybind11 recognizes attributes inheritance
  // from configuration to be polymorphic
  virtual ~Configuration() = default;

  template <typename T>
  bool set(const std::string& key, const T& value) {
    return cfg.setValue(key, value);
  }
  bool setBool(const std::string& key, bool value) { return set(key, value); }
  bool setFloat(const std::string& key, float value) { return set(key, value); }
  bool setDouble(const std::string& key, double value) {
    return set(key, value);
  }
  bool setInt(const std::string& key, int value) { return set(key, value); }
  bool setString(const std::string& key, std::string value) {
    return set(key, value);
  }
  bool setVec3(const std::string& key, const Magnum::Vector3& value) {
    return set(key, value);
  }

  bool setQuat(const std::string& key, const Magnum::Quaternion& value) {
    return set(key, value);
  }

  template <typename T>
  T get(const std::string& key) const {
    return cfg.value<T>(key);
  }
  bool getBool(const std::string& key) const { return get<bool>(key); }
  float getFloat(const std::string& key) const { return get<float>(key); }
  double getDouble(const std::string& key) const { return get<double>(key); }
  int getInt(const std::string& key) const { return get<int>(key); }
  std::string getString(const std::string& key) const {
    return get<std::string>(key);
  }
  Magnum::Vector3 getVec3(const std::string& key) const {
    return get<Magnum::Vector3>(key);
  }
  Magnum::Quaternion getQuat(const std::string& key) const {
    return get<Magnum::Quaternion>(key);
  }

  /**@brief Add a string to a group and return the resulting group size. */
  int addStringToGroup(const std::string& key, const std::string& value) {
    cfg.addValue(key, value);
    return cfg.valueCount(key);
  }

  /**@brief Collect and return strings in a key group. */
  std::vector<std::string> getStringGroup(const std::string& key) const {
    std::vector<std::string> strings;
    for (size_t v = 0; v < cfg.valueCount(key); ++v) {
      strings.push_back(cfg.value<std::string>(key, v));
    }
    return strings;
  }

  bool hasValue(const std::string& key) const { return cfg.hasValue(key); }

  bool removeValue(const std::string& key) { return cfg.removeValue(key); }

 protected:
  Corrade::Utility::ConfigurationGroup cfg;

  ESP_SMART_POINTERS(Configuration)
};

// Below uses std::variant; not yet available in clang c++17
/*
#include <std/variant>

class Configuration {
 public:
  Configuration() : values_() {}

  template <typename T>
  bool set(const std::string& key, const T& value) {
    bool didOverride = hasValue(key);
    values_[key] = value;
    return didOverride;
  }

  template <typename T>
  T get(const std::string& key) const {
    return boost::get<T>(values_.at(key));
  }

  bool hasValue(const std::string& key) {
    return values_.count(key) > 0;
  }

 protected:
  typedef boost::variant<bool, int, float, double, std::string> ConfigValue;
  std::map<std::string, ConfigValue> values_;

  ESP_SMART_POINTERS(Configuration)
};
*/

}  // namespace core
}  // namespace esp

#endif  // ESP_CORE_CONFIGURATION_H_

#pragma once

#include <string>

namespace dds_test_app {
class IPublisher {
public:
  
  virtual bool init(int rate, const std::string &topic_name,
                    const std::string &profile_name = "test-app-pub-profile") = 0;
  virtual void run() = 0;
  virtual ~IPublisher(){};
};
} // namespace dds_test_app

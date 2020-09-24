#pragma once

#include <string>

namespace dds_test_app
{
  class ITools
  {
  public:
    virtual bool init(const std::string &file_path, const std::string &profile_name, const std::string &pub_topic_name,
                      const std::string &sub_topic_name, size_t pub_rate = 1)
        = 0;
    virtual void run() = 0;
    virtual ~ITools()  = default;
  };
} // namespace dds_test_app

#pragma once

namespace dds_test_app
{
  class ISubscriber
  {
  public:
    virtual bool init(const std::string &topic_name, const std::string &profile_name = "test_app_sub_profile") = 0;
    virtual void run()                                                                                         = 0;
    virtual ~ISubscriber(){};
  };

} // namespace dds_test_app

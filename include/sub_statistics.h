#pragma once

#include <chrono>
#include <list>
#include <string>

namespace dds_test_app
{
  class SubStatistics
  {
  public:
    void                     reset();
    void                     receive();
    double                   get_fps();
    auto                     get_receive_count() const -> size_t;
    std::chrono::nanoseconds get_time_from_last_receive();

  private:
    size_t window;
    size_t receive_count;

    std::list<std::chrono::nanoseconds>   durations;
    std::chrono::nanoseconds              max_duration;
    std::chrono::nanoseconds              min_duration;
    std::chrono::steady_clock::time_point last_received_timepoint;
  };

} // namespace dds_test_app

#include "sub_statistics.h"

void dds_test_app::SubStatistics::reset()
{
  receive_count = 0;
  durations.clear();

  last_received_timepoint = std::chrono::steady_clock::now();

  max_duration = std::chrono::nanoseconds(0);
  min_duration = last_received_timepoint.time_since_epoch();
}

void dds_test_app::SubStatistics::receive()
{
  auto prev_last_received_timepoint = last_received_timepoint;
  last_received_timepoint           = std::chrono::steady_clock::now();
  auto new_duration                 = last_received_timepoint - prev_last_received_timepoint;
  durations.push_back(new_duration);
  receive_count++;
  if (new_duration > max_duration)
  {
    max_duration = new_duration;
  }
  if (new_duration < min_duration)
  {
    min_duration = new_duration;
  }
}

auto dds_test_app::SubStatistics::get_time_from_last_receive() -> std::chrono::nanoseconds
{
  return std::chrono::steady_clock::now() - last_received_timepoint;
}

auto dds_test_app::SubStatistics::get_receive_count() const -> size_t
{
  return receive_count;
}

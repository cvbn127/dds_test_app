// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file StringPubSubMain.cpp
 * This file acts as a main entry point to the application.
 *
 * This file was generated by the tool fastcdrgen.
 */


#include "StringPublisher.h"
#include "StringSubscriber.h"

#include "Odometry/OdometryPublisher.h"
#include "Odometry/OdometrySubscriber.h"

#include "OccupancyGrid/OccupancyGridPublisher.h"
#include "OccupancyGrid/OccupancyGridSubscriber.h"
#include "OccupancyGrid/OccupancyGridTools.h"

#include "Pose/PosePublisher.h"
#include "Pose/PoseSubscriber.h"

#include "Polygon/PolygonPublisher.h"
#include "Polygon/PolygonSubscriber.h"

#include "Image/ImagePublisher.h"
#include "Image/ImageSubscriber.h"
#include "Image/ImageTools.h"

#include "RTPRouteTask/RTPRouteTaskPublisher.h"
#include "RTPRouteTask/RTPRouteTaskSubscriber.h"
#include "RTPRouteTask/RTPRouteTaskTools.h"

// #include "PolygonArray/PolygonArrayPublisher.h"
// #include "PolygonArray/PolygonArraySubscriber.h"
// #include "PolygonArray/PolygonArrayTools.h"

#include "GoalInfo/GoalInfoPublisher.h"
#include "GoalInfo/GoalInfoSubscriber.h"
#include "GoalInfo/GoalInfoTools.h"

#include "GeoPoseStamped/GeoPoseStampedPublisher.h"
#include "GeoPoseStamped/GeoPoseStampedSubscriber.h"
#include "GeoPoseStamped/GeoPoseStampedTools.h"

#include <fastrtps/Domain.h>

using namespace eprosima;
using namespace eprosima::fastrtps;

int main(int argc, char** argv)
{
	int type = 0;

	if (argc >= 2)
	{
		if (strcmp(argv[1], "publisher") == 0)
		{
			type = 1;
		}
		else if (strcmp(argv[1], "subscriber") == 0)
		{
			type = 2;
		}
		if (strcmp(argv[1], "odometry_pub") == 0)
		{
			type = 3;
		}
		if (strcmp(argv[1], "odometry_sub") == 0)
		{
			type = 4;
		}
		if (strcmp(argv[1], "pose_pub") == 0)
		{
			type = 5;
		}
		if (strcmp(argv[1], "pose_sub") == 0)
		{
			type = 6;
		}
		if (strcmp(argv[1], "polygon_pub") == 0)
		{
			type = 7;
		}
		if (strcmp(argv[1], "polygon_sub") == 0)
		{
			type = 8;
		}
		if (strcmp(argv[1], "image_pub") == 0)
		{
			type = 9;
		}
		if (strcmp(argv[1], "image_sub") == 0)
		{
			type = 10;
		}
		if (strcmp(argv[1], "image_tools") == 0)
		{
			type = 11;
		}
		if (strcmp(argv[1], "occupancy_pub") == 0)
		{
			type = 12;
		}
		if (strcmp(argv[1], "occupancy_sub") == 0)
		{
			type = 13;
		}
		if (strcmp(argv[1], "occupancy_tools") == 0)
		{
			type = 14;
		}
		if (strcmp(argv[1], "route_task_pub") == 0)
		{
			type = 15;
		}
		if (strcmp(argv[1], "route_task_sub") == 0)
		{
			type = 16;
		}
		if (strcmp(argv[1], "route_task_tools") == 0)
		{
			type = 17;
		}
		// if (strcmp(argv[1], "polygon_array_pub") == 0)
		// {
		// 	type = 18;
		// }
		// if (strcmp(argv[1], "polygon_array_sub") == 0)
		// {
		// 	type = 19;
		// }
		// if (strcmp(argv[1], "polygon_array_tools") == 0)
		// {
		// 	type = 20;
		// }
		if (strcmp(argv[1], "goal_info_pub") == 0)
		{
			type = 21;
		}
		if (strcmp(argv[1], "goal_info_sub") == 0)
		{
			type = 22;
		}
		if (strcmp(argv[1], "goal_info_tools") == 0)
		{
			type = 23;
		}
		if (strcmp(argv[1], "geo_pose_pub") == 0)
		{
			type = 24;
		}
		if (strcmp(argv[1], "geo_pose_sub") == 0)
		{
			type = 25;
		}
		if (strcmp(argv[1], "geo_pose_tools") == 0)
		{
			type = 26;
		}
	}
	int num_bytes = 0;
	if (argc >= 4)
	{
		try
		{
			num_bytes = atoi(argv[3]);
		}
		catch(...)
		{
			num_bytes = 10;
		}
	};
	int rate = 1;
	if (argc == 3)
	{
		try 
		{
			rate = atoi(argv[2]);
		}
		catch(...)
		{
			rate = 1;
		}
	}

	if (type==0)
	{
		std::cout << "Error: Incorrect arguments." << std::endl;
        	std::cout << "Usage: " << std::endl << std::endl;
		std::cout << argv[0] << " publisher|subscriber" << std::endl << std::endl;
		return 0;
	}

	std::cout << "Starting " << std::endl;

	// Register the type being used

	switch(type)
	{
		case 1:
		{
			StringPublisher mypub;
			if (mypub.init(num_bytes, rate))
			{
				mypub.run();
			}
			break;
		}
		case 2:
		{
			StringSubscriber mysub;
			if (mysub.init())
			{
				mysub.run();
			}
			break;
		}
		case 3:
		{
			OdometryPublisher odom_pub;
			if (odom_pub.init(rate))
			{
				odom_pub.run();
			}
			break;
		}
		case 4:
		{
			OdometrySubscriber odom_sub;
			if (odom_sub.init())
			{
				odom_sub.run();
			}
			break;
		}
		case 5:
		{
			PosePublisher pose_pub;
			if (pose_pub.init(rate))
			{
				pose_pub.run();
			}
			break;
		}
		case 6:
		{
			PoseSubscriber pose_sub;
			if (pose_sub.init())
			{
				pose_sub.run();
			}
			break;
		}
		case 7:
		{
			PolygonPublisher polygon_pub;
			if (polygon_pub.init(rate))
			{
				polygon_pub.run();
			}
			break;
		}
		case 8:
		{
			PolygonSubscriber polygon_sub;
			if (polygon_sub.init())
			{
				polygon_sub.run();
			}
			break;
		}
		case 9:
		{
			ImagePublisher image_pub;
			if (image_pub.init(rate))
			{
				image_pub.run();
			}
			break;
		}
		case 10:
		{
			ImageSubscriber image_sub;
			if (image_sub.init())
			{
				image_sub.run();
			}
			break;
		}
		case 11:
		{
			ImageTools image_tools;
			std::string sub_topic = "image_test";
			std::string pub_topic = "image_pub";
			if (argc > 2)
			{
				sub_topic = argv[2];
			}
			if (argc > 3)
			{
				pub_topic = argv[3];
			}
			if (image_tools.init("/volumes/soss_config/default_fastrtps_profile.xml", "part_profile_name", sub_topic, pub_topic))
			{
				image_tools.run();
			}
			break;
		}
		case 12:
		{
			OccupancyGridPublisher occu_pub;
			if (occu_pub.init(rate))
			{
				occu_pub.run();
			}
			break;
		}
		case 13:
		{
			OccupancyGridSubscriber occu_sub;
			if (occu_sub.init())
			{
				occu_sub.run();
			}
			break;
		}
		case 14:
		{
			OccupancyGridTools occu_tools;
			if (occu_tools.init())
			{
				occu_tools.run();
			}
			break;
		}
		case 15:
		{
			RTPRouteTaskPublisher pub;
			if (pub.init(rate))
			{
				pub.run();
			}
			break;
		}
		case 16:
		{
			RTPRouteTaskSubscriber sub;
			if (sub.init())
			{
				sub.run();
			}
			break;
		}
		case 17:
		{
			RTPRouteTaskTools tools;
			std::string sub_topic = "rtp_route_task_test";
			std::string pub_topic = "rtp_route_task_pub";
			if (argc > 2)
			{
				sub_topic = argv[2];
			}
			if (argc > 3)
			{
				pub_topic = argv[3];
			}
			if (tools.init("/volumes/soss_config/default_fastrtps_profile.xml", "part_profile_name", sub_topic, pub_topic))
			{
				tools.run();
			}
			break;
		}
		case 18:
		{
			// PolygonArrayPublisher pub;
			// if (pub.init(rate))
			// {
			// 	pub.run();
			// }
			break;
		}
		case 19:
		{
			// PolygonArraySubscriber sub;
			// if (sub.init())
			// {
			// 	sub.run();
			// }
			break;
		}
		case 20:
		{
			// PolygonArrayTools tools;
			// if (tools.init())
			// {
			// 	tools.run();
			// }
			break;
		}
		case 21:
		{
			GoalInfoPublisher pub;
			if (pub.init(rate))
			{
				pub.run();
			}
			break;
		}
		case 22:
		{
			GoalInfoSubscriber sub;
			if (sub.init())
			{
				sub.run();
			}
			break;
		}
		case 23:
		{
			GoalInfoTools tools;
			if (tools.init("/volumes/soss_config/default_fastrtps_profile.xml", "part_profile_name"))
			{
				tools.run();
			}
			break;
		}
                case 24:
		{
			GeoPoseStampedPublisher pub;
			if (pub.init(rate))
			{
				pub.run();
			}
			break;
		}
		case 25:
		{
			GeoPoseStampedSubscriber sub;
			if (sub.init("/atlans_geopose"))
			{
				sub.run();
			}
			break;
		}
		case 26:
		{
      std::string sub_topic = "geopose_test";
			std::string pub_topic = "geopose_pub";
			if (argc > 2)
			{
				sub_topic = argv[2];
			}
			if (argc > 3)
			{
				pub_topic = argv[3];
			}
			GeoPoseStampedTools tools;
			if (tools.init("/volumes/soss_config/default_fastrtps_profile.xml", "part_profile_name", sub_topic, pub_topic))
			{
				tools.run();
			}
			break;
		}
	}

	return 0;
}

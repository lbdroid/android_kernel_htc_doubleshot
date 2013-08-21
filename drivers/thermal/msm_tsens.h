/* Copyright (c) 2013, Emmanuel Utomi. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/thermal.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/workqueue.h>
#include <linux/io.h>
#include <mach/msm_iomap.h>
#include <linux/pm.h>
#include <linux/msm_tsens.h>
#include <mach/msm_iomap.h>
#include <mach/socinfo.h>

enum tsens_trip_type {
	TSENS_TRIP_STAGE3 = 0,
	TSENS_TRIP_STAGE2,
	TSENS_TRIP_STAGE1,
	TSENS_TRIP_STAGE0,
	TSENS_TRIP_NUM,
};

struct tsens_tm_device_sensor {
	struct thermal_zone_device	*tz_dev;
	enum thermal_device_mode	mode;
	unsigned int			sensor_num;
	struct work_struct		work;
	int				offset;
	int				calib_data;
	int				calib_data_backup;
};

struct tsens_tm_device {
	bool				prev_reading_avail;
	int				slope_mul_tsens_factor;
	int				tsens_factor;
	uint32_t			tsens_num_sensor;
	int offset;
	struct work_struct work;
	enum platform_type		hw_type;
	struct tsens_tm_device_sensor	sensor[0];
	uint32_t pm_tsens_thr_data;
};

//added
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/rtc.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>
/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

rtc_alarm_callback handle (const struct device *dev, uint16_t id, void *user_data){


printk("Successfully reached the handler..\n");

return 0;
}
int main(void)
{
	const struct device *const dev = DEVICE_DT_GET_ONE(ambiq_am1805);

	if (!device_is_ready(dev)) {
		return 0;
	}

        uint16_t mask = 0x5F;
	uint8_t err;
	struct rtc_time time = {
	.tm_sec = 1,
	.tm_min = 10,
	.tm_hour = 2,
	.tm_mday = 29,
	.tm_mon  = 6,
	.tm_year = 23,
	.tm_wday = 1,
	};
	
	/*setting time*/
	err = rtc_set_time(dev, &time);
	
	rtc_set_calibration(dev, 100);
	time.tm_min = 11;
	
	err = rtc_alarm_set_time(dev, 0, mask, &time);
	rtc_alarm_set_callback(dev, 0,(rtc_alarm_callback) NULL, NULL);
	
	
	while (1) {

	 rtc_get_time(dev, &time);

	 rtc_alarm_get_time(dev, 0, &mask, &time);

	 k_busy_wait(1000); 
	
	}
}

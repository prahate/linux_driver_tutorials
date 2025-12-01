#include <linux/module.h>
#include <linux/init.h>
#include <linux/hrtimer.h>
#include <linux/jiffies.h>
#include <linux/ktime.h>

static struct hrtimer my_hrtimer;  // custom hrtimer
u64 start_t; // to store start time
#define TIMER_INTERVAL 50


// hrtimer_restart callback part of hrtimer struct
static enum hrtimer_restart hrtimer_restart_handler(struct hrtimer *timer) {
	u64 now_t = get_jiffies_64();  // get current64bit jiffies value non-atomic
	pr_info("now_t - start_t = %u\n", jiffies_to_msecs(now_t - start_t));
	return HRTIMER_NORESTART;
	// to restart the timer use hrtimer_forward_now API with HRTIMER_RESTART as return value
	// hrtimer_forward_now(timer, ms_to_ktime(TIMER_INTERVAL));
	//return HRTIMER_RESTART;
}

static int __init my_init(void)
{
    printk("Hello Kernel!\n");
    // init hrtimer
    hrtimer_init(&my_hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    my_hrtimer.function = &hrtimer_restart_handler;
    // save start value
    start_t = get_jiffies_64();
    hrtimer_start(&my_hrtimer, ms_to_ktime(TIMER_INTERVAL), HRTIMER_MODE_REL);
    return 0;
}

static void __exit my_exit(void)
{
    hrtimer_cancel(&my_hrtimer);
    printk("GoodBye Kernel !!!\n");
}

module_init(my_init);
module_exit(my_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Prathamesh Rahate <patyarahate@gmail.com>");
MODULE_DESCRIPTION("Better Hello world module");

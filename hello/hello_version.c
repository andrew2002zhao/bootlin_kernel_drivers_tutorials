// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/utsname.h>
#include <linux/timekeeping.h>

/* Add your code here */

MODULE_LICENSE("GPL");

time64_t startTime;
time64_t endTime;
//__init is a macro and this memory segment is discarded once done executing
static int __init my_module_init(void)
{
	printk(KERN_INFO"hello %s kernel version %s\n", init_uts_ns.name.machine, init_uts_ns.name.release);
	startTime = ktime_get_seconds();
	return 0;
}

static void __exit my_module_exit(void)
{
	endTime = ktime_get_seconds();
	time64_t elapsedTime = endTime - startTime;
	printk(KERN_INFO"goodbye, time elapsed %lld second(s)\n", elapsedTime);
}

//this is a macro that tells the kernel where the entry point is
module_init(my_module_init);
//this is a macro that tells the kernel where the exit point is or when the module is unloaded what function to run
module_exit(my_module_exit);

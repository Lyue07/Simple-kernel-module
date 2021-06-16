#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/random.h> 
int init_module(void)
{
	int k;
	get_random_bytes(&k, sizeof(k));
	printk(KERN_INFO "Hello world 1.\n");

	printk(KERN_INFO "BITE %d\n", k);
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye world 1.\n");
}

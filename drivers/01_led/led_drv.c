#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/poll.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <asm/uaccess.h>
#include <asm/io.h>


// 1. 驱动程序想要访问硬件必须ioremap


static int major;
static struct class *led_class;


/* register */
// SW_MUX_CTL Register Address: 229_0000h base + 14h offset = 229_0014h
// 101 : ALT5 — Select mux mode: ALT5 mux port, GPIO5_IO03 of instance - gpio
static volatile unsigned int *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3;
// GPIO5_GDIR 20A_C004
static volatile unsigned int *GPIO5_GDIR;
// GPIO5_DR 20A_C000
static volatile unsigned int *GPIO5_DR;

static int led_open(struct inode *inode, struct file *filp)
{
	/* enable gpio */
	/* set gpio alt */
	*IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 &= ~0x0f;
	*IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 |= 0x05;
	/* configure gpio as output */
	*GPIO5_GDIR |= (1<<3);
	return 0;
}


static ssize_t led_write(struct file *filp, const char __user *buf,
			 size_t count, loff_t *ppos)
{	
	char val;
	int ret;
	/* copy_from_user: get data from app */
	ret = copy_from_user(&val, buf, 1);
	/* to_set_gpio_register: out 0/1 */
	if (val) {
		/* set gpio to let led on */
		*GPIO5_DR &= ~(1<<3);
	} else {
		/* set gpio to let led off */
		*GPIO5_DR |= (1<<3);
	}
	return 1;
}



// file operstion
static struct file_operations led_fops = {
	.owner		= THIS_MODULE,
	.write		= led_write,
	.open		= led_open,
};

/* 入口函数 */

static int __init led_init(void)
{
	printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	// 注册设备
	major = register_chrdev(0, "yankai_led", &led_fops);	

	/* 映射寄存器 */
	IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = ioremap(0x02290000 + 0x14, 4);
	GPIO5_GDIR = ioremap(0x020AC000 + 0x04, 4);
	GPIO5_DR = ioremap(0x020AC000, 4);
	
	led_class = class_create(THIS_MODULE, "yankailed");
	/* create /dev/yk_led0 */
	device_create(led_class, NULL, MKDEV(major, 0), NULL, "yk_led%d", 0);  
	
	
	return 0;
}


static void __exit led_exit(void)
{
	iounmap(IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3);
	iounmap(GPIO5_GDIR);
	iounmap(GPIO5_DR);

	device_destroy(led_class, MKDEV(major, 0));
	class_destroy(led_class);
	
	unregister_chrdev(major, "yankai_led");
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");


#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <asm/uaccess.h>
#include <linux/errno.h>
#include "meter_dev.h"
#include "meter_fops.h"

int fops_open(struct inode *, struct file *);
int fops_release(struct inode *, struct file *);
ssize_t fops_read(struct file *, char __user *, size_t count, loff_t *f_pos);
long fops_ioctl(struct file *, unsigned int cmd, unsigned long arg);

const struct file_operations default_fops = 
{
	.owner = THIS_MODULE,
	.open = fops_open,	
	.release = fops_release,
	.unlocked_ioctl = fops_ioctl,
	.read = fops_read,
	.write = NULL
};

int fops_init(meter_dev_t * dev)
{
        int result;

        cdev_init(&(dev->cdev), &default_fops);

        result = cdev_add(&(dev->cdev), dev->dev_id, 1);

        if (result)
        {
                printk(KERN_NOTICE "Error adding a meter device");
                return result;
        }
        return 0;
}

void fops_exit(meter_dev_t * dev)
{
	cdev_del(&(dev->cdev));
}




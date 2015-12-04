#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <asm/uaccess.h>
#include <linux/errno.h>
#include "meter_dev.h"
#include "meter_fops.h"
#include "meter_app.h"

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

long fops_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	long retval = 0;

	if(_IOC_TYPE(cmd) != METER_MAGIC_NUMBER)
		return -ENOTTY;
	if(_IOC_DIR(cmd) & _IOC_READ)
		retval = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	if(retval)
		return -EFAULT;

	if(_IOC_DIR(cmd) & _IOC_WRITE)
		retval = !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	if(retval)
		return -EFAULT;

	//TODO: handle the FOPS commands

	return 0;
}

int fops_release(struct inode *inode, struct file *filp)
{
	return 0;
}


int fops_open(struct inode *inode, struct file *filp)
{
	filp->private_data = NULL;

	if(MAJOR(dev_id) == imajor(inode))
	{
		/* Verify that we have a valid device and set the private data */
		unsigned int minor = iminor(inode);
		if(minor < NUM_METERS)
		{
			filp->private_data = devices_in_ram[minor];
		}
	}
	
	if(filp->private_data == NULL)
		return -ENODEV;

	return 0;
}

ssize_t fops_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	meter_dev_t * dev = filp->private_data;

	if(dev == NULL)
		return -ENODEV;

	//TODO: Read from the meter

	return 0;
}

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




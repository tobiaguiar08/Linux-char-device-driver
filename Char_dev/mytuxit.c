/*
 * Linux Device Driver
 * 
 * ENSICAEN training template
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 or 3 of the License, or (at your option) any later version.
 */


#include <linux/module.h>
#include <linux/cdev.h>  
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/wait.h> 
#include <linux/slab.h>

#define LOCAL_BUF_SIZE 512

 static DECLARE_WAIT_QUEUE_HEAD(wq);
 //static int flag = 0;
 dev_t dev_num;
 struct cdev my_dev;
 char my_buff[LOCAL_BUF_SIZE];
 const char kernel_buffer[LOCAL_BUF_SIZE] = "read method call\n";
 int my_module_is_open = 0;


 int my_module_open(struct inode *pInode, struct file *pFile) {
	my_module_is_open++;
	
		 if((pFile->private_data = kmalloc(LOCAL_BUF_SIZE , GFP_KERNEL)) == 0){
	            printk(KERN_INFO "Cannot allocate memory in kernel\n");
	            return -1;
	     } 
	     
	printk (KERN_INFO "Opening kernel \n" );
	 
	return 0;
}
 int my_module_release(struct inode *pInode, struct file *pFile) {
	// indicate that future calls to open() will succeed
	my_module_is_open--;
	printk (KERN_INFO "Closing kernel \n" );
	kfree(pFile->private_data);	
	return 0;
}
 ssize_t my_module_read(struct file *fp, char __user *buffer, size_t len, loff_t *offset) {
 	loff_t available = LOCAL_BUF_SIZE - *offset;
	if (len > available) len = available;
	
	/*
	printk(KERN_INFO "Sleeping...");
	wait_event_interruptible(wq, flag != 0);
	flag = 0;
	*/
	if(copy_to_user (buffer, fp->private_data + *offset, len) < 0) {
		printk(KERN_ERR "Error in copy_to_user");
		return -1;
	}
	//copy_to_user (buffer, kernel_buffer + *offset, len);
	printk(KERN_DEBUG "mytuxit: red offset:%d len:%s", *offset, len);
	*offset += len;
	return len;	
 }

 ssize_t my_module_write(struct file *fp, const char *buf, size_t count, loff_t *ppos) {
 	size_t real, num;
	real = min((size_t)LOCAL_BUF_SIZE, count);
	if (real) {
		/*
 		printk(KERN_INFO "Waiking up!\n");
		copy_from_user(my_buff, buf, real);
		flag = 1;
 		wake_up_interruptible(&wq);
 		*/
 		if(copy_from_user(fp->private_data, buf, real) < 0) {
 			printk(KERN_ERR "Error in copy_from_user");
			return -1;
 		}
		
	}
	//num = real;
	printk(KERN_DEBUG "mytuxit: wrote %lu/%lu chars %s\n", real, count, my_buff);
	return real;
 }


 static struct file_operations my_module_fops = {
	owner: THIS_MODULE,
	open: my_module_open,
	read: my_module_read,
	release: my_module_release,
	write : my_module_write
 };


static int func_init(void)
{
	// init & register character driver's file operations
	cdev_init (&my_dev, &my_module_fops);
	my_dev.owner =  THIS_MODULE;
	my_dev.ops = &my_module_fops;
	int err, rc;
	err = alloc_chrdev_region(&dev_num, 0, 1, "my_ldd");
	if (err) return err;
	rc = cdev_add (&my_dev, dev_num, 1); 
 	if (rc) {
 		unregister_chrdev_region(dev_num, 1);
		printk(KERN_INFO "my_module: unable to add cdev struct.\n");
		return rc;
	} /*endif*/
 	printk(KERN_INFO "mytuxit init: (%d,%d)\n",MAJOR(dev_num), MINOR(dev_num));
  	return 0; // Non-zero return means that the module couldn't be loaded.
}

static void func_exit(void)
{
  
  cdev_del (&my_dev); 
  unregister_chrdev_region(dev_num, 1);
  printk(KERN_INFO "mytuxit exit\n");
}

module_init(func_init);
module_exit(func_exit);
MODULE_LICENSE("GPL");


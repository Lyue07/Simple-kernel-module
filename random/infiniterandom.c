#include "infiniterandom.h"

static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
};

static char *alphabet = "test";
module_param(alphabet, charp, 0000);

int init_module(void)
{
    Major = register_chrdev(0, DEVICE_NAME, &fops);

    if (Major < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", Major);
        return Major;
    }

    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);

    return SUCCESS;
}

void cleanup_module(void)
{
    unregister_chrdev(Major, DEVICE_NAME);
}

static int device_open(struct inode *inode, struct file *filp)
{  
    try_module_get(THIS_MODULE);
    return SUCCESS;
}

static int device_release(struct inode *inode, struct file *filp)
{
    module_put(THIS_MODULE);
    return SUCCESS;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
    int rand;
    int bytes_read = 0;
    int len = my_strlen(alphabet);
    
    get_random_bytes(&rand, sizeof(rand));
    rand = rand % len;
    if (rand < 0)
        rand *= -1;
    if (rand == len)
        rand--;
    sprintf(msg, "%c", *(alphabet + rand));
    msg_Ptr = msg;

    if (*msg_Ptr == 0)
        return 0;

    while (length && *msg_Ptr) {
        put_user(*(msg_Ptr++), buffer++);
        length--;
        bytes_read++;
    }

    return bytes_read;
}

static ssize_t device_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
    printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
    return -EINVAL;
}

size_t my_strlen(const char *s)
{
    int len = 0;
    while (*s != '\0')
    {
        len++;
        s++;
    }
    return len;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SALLIOT Mathieu RIBEIRO Luis REIS Dylan");
MODULE_DESCRIPTION("Random Module");


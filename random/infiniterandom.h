#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/random.h>
#include <asm/uaccess.h>

int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
size_t my_strlen(const char *s);

#define SUCCESS 0
#define DEVICE_NAME "infinitrandom"
#define BUF_LEN 80

static int Major;
static char msg[BUF_LEN];
static char *msg_Ptr;

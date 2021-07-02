# Simple-kernel-module


go in random directory
make
sudo insmod ./random.ko
sudo dmesg
sudo mknod c Major 0
cat /dev/infiniterandom
sudo rmmod infiniterandom
sudo rm /dev/infiniterandom

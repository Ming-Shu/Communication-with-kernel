# Communication-with-kernel
How can kernel code and user-space code communicate with each other?

1. Syscall: 
  In Linux kernel each system call is assigned a unique syscall number. Like open() -> __NR_open,close() -> __NR_exit,read() -> __NR_read.

2. IOCTL: 
  There are already predefined ictl number in the kernel. So by using these number you can interact with kernel space. e.g. ioctl(/dev/i2c-0,I2C_SMBUS,address);

3. Sysfs/procfs: 
  You can communicate with the kernel through sysfs as well proc fs. (Have a look into /sys/* folder).

4. Netlink Socket: 
  Through netlink socket you can pass the message from kernel space to user space. e.g socket(), bind(), sendmsg().


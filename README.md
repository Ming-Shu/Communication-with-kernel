# Communication-with-kernel
How can kernel code and user-space code communicate with each other?

1. Syscall: In Linux kernel each system call is assigned a unique syscall number. 

2. IOCTL: There are already predefined ictl number in the kernel. So by using these number you can interact with kernel space. 

3. Sysfs/procfs: You can communicate with the kernel through sysfs as well proc fs. 

4. Netlink Socket: Through netlink socket you can pass the message from kernel space to user space.

------------------------------------------------------------------------------------------------------------------------------------------
About Netlink Socket:

It provides a full-duplex communication link between the two by way of standard socket APIs for user-space processes and a special kernel API for kernel modules. 

                      _____________________________________________________
                     | socket(AF_NETLINK,SOCK_DGRAM,NETLINK_KOBJECT_UEVENT)|
                     |_____________________________________________________|
Userspace                                     |
----------------------------------------------|------------------------------------
Kernelspace                                   |
                     _________________________|______________________________
                    |                   netlink_create()                     |
                    |________________________________________________________|

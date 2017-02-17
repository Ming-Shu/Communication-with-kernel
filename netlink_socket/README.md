# How to use Netlink Sockets
Netlink socket uses the address family AF_NETLINK, as compared to AF_INET used by TCP/IP socket. 

------------------------------------------------------------------------------------------------------------------------------------------
How can kernel code and user-space code  with each other?

                         _____________________________________________________
                        | socket(AF_NETLINK,SOCK_DGRAM,NETLINK_KOBJECT_UEVENT)|
                        |_____________________________________________________|
        User space                                |    
        ------------------------------------------|-----------------------------------------------------------------------------
        Kernel                                    |    
                        __________________________|___________________________
                       |                   netlink_create()                   |
                       |______________________________________________________|
                                                  |
                        __________________________|___________________________         _____________________________
                       |                   __netlink_create()                 |<------|  __netlink_kernel_create()  |
                       |______________________________________________________|       |_____________________________|
                                                                                      nlk->flags|=NETLINK_KERNEL_SOCKET  

 
            

Step:
 1. include  netlink.h
 
 2. create netlink socket(netlink family) 
 


e.g.
    hotplug_detect.c
        
   When a USB drive is plugged in and kernel has detected,then hotplug mechanism through sysfs via the
   "uevent" files. Every time a device is added or removed, the kernel sends a uevent to notify udev of the change.

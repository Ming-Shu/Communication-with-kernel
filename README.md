# Communication-with-kernel
How can kernel code and user-space code communicate with each other?

1. Syscall: In Linux kernel each system call is assigned a unique syscall number. 

2. IOCTL: There are already predefined ictl number in the kernel. So by using these number you can interact with kernel space. 

3. Sysfs/procfs: You can communicate with the kernel through sysfs as well proc fs. 

4. Netlink Socket: Through netlink socket you can pass the message from kernel space to user space.

------------------------------------------------------------------------------------------------------------------------------------------
About Netlink Socket:

It provides a full-duplex communication link between the two by way of standard socket APIs for user-space processes and a special kernel API for kernel modules. 

                                         _______________________________________________________
                                        | socket(AF_NETLINK,SOCK_RAM|SOCK_CLOEXEC,NETLINK_ROUTE)|
                                        |              Userspace Netlink socket                 |
                                        |_______________________________________________________|
                            User space                                              |    
                           ---------------------------------------------------------|-----------------------------
                            Kernel                                                  |    
                                                                      ______________|__________
                                                                     |  netlink_create()       |                
                                                                     |_________________________|
                                                                                    |
                               ___________________________            ______________|__________
                              |  netlink_kernel_create()  |          | __netlink_create()      |
                              |  Kernel Netlink socket    |--------->| sk_alloc()              |
                              |___________________________|          | sock_init_data(sock,sk) |
                                                                     |        .....            |
                                                                     | ________________________|
                                                                                      
Netlink socketes can be created in kernel or in userspace;


userspace netlink socket:                 
                         sockets is created by the socket(),it is headled by the netlink_create().
                          
kernel netlink socket:   
                      sockets is created by the netlink_kernel_create(),it is headled by the __netlink_kernel_create(),and it sets the NETLINK_KERNEL_SOCKET flag.
                         
Eventually both methods call __netlink_create() to allocate a socket in common way it.

Reference:
          http://www.linuxjournal.com/article/7356?page=0,0
            

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <unistd.h>
#include <fcntl.h>

#define UEVENT_BUF_SIZE 1024

int create_hotplug_sock(void)
{
	struct sockaddr_nl snl_addr;
	int sock_fd;
	const int buffersize = 8 * 1024;/*buffer size is 8K*/
	
	if((sock_fd = socket(PF_NETLINK, SOCK_RAW,NETLINK_KOBJECT_UEVENT)) < 0)
	{
		printf("opening socket failed:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	/* set receive buffersize */
	setsockopt(sock_fd, SOL_SOCKET,SO_RCVBUFFORCE, &buffersize, sizeof(buffersize));
 
	bzero(&snl_addr,sizeof(snl_addr));
	snl_addr.nl_family=AF_NETLINK;
	snl_addr.nl_pid = getpid(); //0 both is ok
	snl_addr.nl_groups = 1;//standard output as multicast
	
	if(bind(sock_fd,(struct sockaddr *)&snl_addr,sizeof(snl_addr))==-1)
	{
		printf("bind error:%s\n",strerror(errno));
		close(sock_fd);
		exit(EXIT_FAILURE);
	}
	
	return sock_fd;
}

int main(int argc, char* argv[])
{
	int sock_fd = create_hotplug_sock();
	char msg_buf[UEVENT_BUF_SIZE*2] = {0};/* Netlink message buffer */ 
	int msg_len;
	int i;		 	

	while(1) {
		memset(msg_buf, 0 ,sizeof(msg_buf));
		msg_len = recv(sock_fd,msg_buf, sizeof(msg_buf), 0);
		if(msg_len<0)
			printf("receive error\n");
		/* %s in format specifier tells printf to look for a string. 
   		And printf found it,but it stops printing after seeing the first \0.*/
		for(i=0;i<msg_len;i++)
			if(*(msg_buf+i)=='\0')
				msg_buf[i]='\n';
		printf("received:%d,bytes\n%s\n",msg_len,msg_buf);
	}             

	return 0;
}

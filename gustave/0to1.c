#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAXRCVLEN 300

int main()
{
	char buffer[MAXRCVLEN + 1]; // +1 so we can add null terminator
	int mysocket;
	struct sockaddr_in dest; 

	char *address = "178.79.134.250"; // vortex.labs.overthewire.org
	int port_num = 5842;

	mysocket = socket(AF_INET, SOCK_STREAM, 0);

	memset(&dest, 0, sizeof(dest));                /* zero out the struct */
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(address); /* set destination IP address*/
	dest.sin_port = htons(port_num);                /* set destination port number */

	connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr));
		
	int len = 0;
	do
	{
		len += recv(mysocket, buffer+len, MAXRCVLEN, 0);
	} while(len < 16);

	unsigned int *ints = calloc(4,sizeof(unsigned int));
	unsigned int sum;
	memcpy(ints,buffer,16);

	int num = 1;
	if(*(char *)&num == 1) //Litle Endian
	{
		sum = ints[0] + ints[1] + ints[2] + ints[3];
	}
	else //Big Endian
	{
		int i;
		for(i = 0; i < 4; i++)
		{
			ints[i] = htonl(ints[i]);
		}
		sum = htonl((ints[0] + ints[1] + ints[2] + ints[3]));
	}

	memcpy(buffer,&sum, sizeof(unsigned int));
	send(mysocket, buffer, sizeof(unsigned int), 0);

	memset(buffer, 0, MAXRCVLEN+1);
	len = recv(mysocket, buffer, MAXRCVLEN, 0);
	buffer[len] = '\0'; // We have to null terminate the received data ourselves

	printf("%s\n", buffer);
	close(mysocket);
	return EXIT_SUCCESS;
}

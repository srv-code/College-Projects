/* To calculate gross and net salary calculations on the server as per the client’s input. */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>	//
#include <sys/socket.h>	//
#include <netinet/in.h>
#include <unistd.h> //close()

#define DEBUG 1


struct sal {
	float salary, da, tax, net, gross;
};


int main(void) {
	struct sockaddr_in selfAddress, serverAddress;
	const int flags = 0;
	int socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	serverAddress.sin_family = AF_INET;	//IP family
	serverAddress.sin_port = htons(5300);	//serverPort
	serverAddress.sin_addr.s_addr = htonl(2130706433); //127.0.0.1

	selfAddress.sin_family = AF_INET;	//IP family
	selfAddress.sin_port = htons(5350);	//clientPort
	selfAddress.sin_addr.s_addr = htonl(2130706433); //127.0.0.1

	bind(socketfd, (struct sockaddr*) &selfAddress, sizeof(struct sockaddr));

	struct sal sal1;
	printf("Salary : ");
	scanf("%f", &sal1.salary);
	printf("DA : ");
	scanf("%f", &sal1.da);

	unsigned int bufSize = sizeof(struct sal);
	unsigned int serverAddressSize = sizeof(serverAddress);
		
	sendto(socketfd, &sal1, bufSize, flags, (struct sockaddr*) &serverAddress, serverAddressSize);

	recvfrom(socketfd, &sal1, bufSize, flags, (struct sockaddr*) &serverAddress, &serverAddressSize);
	
	printf("Tax : %f\n", sal1.tax);
	printf("Net : %f\n", sal1.net);
	printf("Gross : %f\n", sal1.gross);

	close(socketfd);
	return 0;
}

#include <unistd.h>
#include<stdio.h>	//printf
#include<string.h>	//strlen
#include<sys/socket.h>	//socket
#include<arpa/inet.h>	//inet_addr
#include<pthread.h>
int sock;

void init()
{

	struct sockaddr_in server;
		
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 23456 );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return ;
	}
	
	puts("Connected\n");


}

void *send_co(void *vargp)
{
	char message[]= "nidhi"; 
        
	
	
	
	//keep communicating with server
	while(1)
	{
		printf("Enter message : ");
		//scanf("%s" , message);
		//message[5] = "nidhi";
		//Send some data
		if( send(sock , message , strlen(message) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		

           sleep(2);
         }
}
int main(int argc , char *argv[])
{
	
        init();
  	pthread_t t1;
        pthread_create(&t1,NULL,send_co,NULL);
         
        char server_reply[2000];
	
	
	
	//keep communicating with server
	while(1)
	{
		
		
		//Receive a reply from the server
		if( recv(sock , server_reply , 2000 , 0) < 0)
		{
			puts("recv failed");
			break;
		}
		
		puts("Server reply :");
		puts(server_reply);
	}
	
	close(sock);
	return 0;
}

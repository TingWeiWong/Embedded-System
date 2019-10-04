/* A simple client program to interact with the myServer.c program on the Raspberry.
myClient.c
The port number used in 8083.
This code is compiled and run on the Macbook laptop as follows:


    g++ -o myClient myClient.c 
    ./myClient

Addapted from https://www.youtube.com/watch?v=LtXEMwSG5-8&t=1404s

*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

void error(char *msg) {
    perror(msg);
    exit(0);
}

// void sendData( int sockfd, int x ) {
//   int n;

//   char buffer[32];
//   sprintf( buffer, "%d\n", x );
//   if ( (n = write( sockfd, buffer, strlen(buffer) ) ) < 0 )
//       error( const_cast<char *>( "ERROR writing to socket") );
//   buffer[n] = '\0';
// }

void sendArray(int network_socket, int unsorted[]){
  char buffer[32];
  int write_status;
  sprintf(buffer,"%d\n", *unsorted);

  write_status = write(network_socket, buffer, strlen(buffer));

  // if (write_status == -1){
  //   error(const_cast<char *> ("Error sending data!"));
  // }
  buffer[write_status] = '\0';
}


int getArray(int network_socket){
  char buffer[32];
  int read_status;

  read_status = read(network_socket,buffer,31);
  // if (read_status == -1){
  //   error (const_cast<char *> ("Error reading data!"));
  // }
  buffer[read_status] = '\0';
  return atoi(buffer);
}

int getInt(int network_socket){
  char buffer[32];
  int read_status;

  read_status = read(network_socket,buffer,31);
  // if (read_status == -1){
  //   error (const_cast<char *> ("Error reading data!"));
  // }
  buffer[read_status] = '\0';
  return atoi(buffer);
}

void sendInt(int network_socket, int data){
  char buffer[32];
  int write_status;
  sprintf(buffer,"%d\n", data);

  write_status = write(network_socket, buffer, strlen(buffer));

  // if (write_status == -1){
  //   error(const_cast<char *> ("Error sending data!"));
  // }
  buffer[write_status] = '\0';
}



// int getData( int sockfd ) {
//   char buffer[32];
//   int n;

//   if ( (n = read(sockfd,buffer,31) ) < 0 )
//        error( const_cast<char *>( "ERROR reading from socket") );
//   buffer[n] = '\0';
//   return atoi( buffer );
// }

int main(int argc, char *argv[])
{

    // Create socket
    int network_socket = socket(AF_INET,SOCK_STREAM,0);
    int portno = 8083;

    // Assign address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(portno);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //Check connection 

    int connect_result = connect(network_socket, (struct sockaddr *)& server_address, sizeof(server_address));

    if (connect_result == -1){
      printf("Error connecting to server\n");
    }

    char server_response[256];

    recv(network_socket, &server_response,sizeof(server_response),0);

    int test;

    test = 3;

    sendInt(network_socket,test);

    int data;

    data = getInt(network_socket);

    printf("%s\n", server_response);

    printf("Data = %d\n", data);

    // int n;

    // sendInt(network_socket, 10);

    // int result;

    // result = getInt(network_socket);


    // sorted = getArray(network_socket);

    // printf("%d -> %d \n", *unsorted, *sorted);


    close(network_socket);
    return 0;

}



//     char serverIp[] = "169.254.0.2";
//     char buffer[256];
//     int data;

//     if (argc < 3) {
//       // error( const_cast<char *>( "usage myClient2 hostname port\n" ) );
//       printf( "contacting %s on port %d\n", serverIp, portno );
//       // exit(0);
//     }
//     if ( ( sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 )
//         error( const_cast<char *>( "ERROR opening socket") );

//     if ( ( server = gethostbyname( serverIp ) ) == NULL ) 
//         error( const_cast<char *>("ERROR, no such host\n") );
    
//     bzero( (char *) &serv_addr, sizeof(serv_addr));
//     serv_addr.sin_family = AF_INET;
//     bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
//     serv_addr.sin_port = htons(portno);
//     if ( connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
//         error( const_cast<char *>( "ERROR connecting") );

//     for ( n = 0; n < 10; n++ ) {
//       sendData( sockfd, n );
//       data = getData( sockfd );
//       printf("%d ->  %d\n",n, data );
//     }
//     sendData( sockfd, -2 );

//     close( sockfd );
//     return 0;
// }
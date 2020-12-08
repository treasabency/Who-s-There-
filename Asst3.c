#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>

#include <string.h>

//#define PORT 9012

char buffer[1024] = {0};

void clearbuff(){
    memset(buffer, 0, sizeof(buffer));
}

int main(int argc, char *argv[]){

    int server_fd, new_socket, valread;
    struct sockaddr_in socket_address;

    int opt = 1;
    int addrlen = sizeof(socket_address);

    char *knock, *quote1, *finish;
    //char *last = "Hello, anyone there?\n";

    //server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int port = atoi(argv[1]);
    if(port<5000 || port >65535){
        printf("ERROR: port is out of bounds\n");
        return EXIT_FAILURE;
    }

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0))==0){
 printf("Socket creation failed\n");
        return EXIT_FAILURE;
    }

    //attach socket to PORT 9012
    if( setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt) )){
        printf("Set Socket Opt failed\n");
        return EXIT_FAILURE;
    }


    memset(&socket_address, 0, addrlen);//fill with zero

    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;//attach any available prot
    //socket_address.sin_addr.s_addr = inet_addr("127.0.01");//set IP address
    socket_address.sin_port = htons( port ); //read the port

    //attach socket to PORT
    if(bind(server_fd, (struct sockaddr *) &socket_address, sizeof(socket_address))<0){
  printf("Bind error\n");
        return EXIT_FAILURE;
    }

    if(listen(server_fd, 3) < 0){
        printf("listen failed\n");
        return EXIT_FAILURE;
    }

    //accpet message from client
    new_socket = accept(server_fd, (struct sockaddr *) &socket_address, (socklen_t *) &addrlen);

    if(new_socket < 0){
        printf("Acception error");
        return EXIT_FAILURE;
    }

    //read CLIENT AT HOME
    //valread = read(new_socket, buffer, 1024);
    //printf("%s\n", buffer);
  //send knock knock
    scanf("%s",&knock);
    // use the formatCheck1 here
    send(new_socket, knock, strlen(knock), 0);
    //printf("Joke sent.\n");
    clearbuff();

    int i =1;

    //read and print respond1
    // use formatCheck1 here
    valread = read(new_socket, buffer, 1024);
    printf("%d. %s\n",i, buffer);

    // use formatCheck2 here
    send(new_socket, quote1, strlen(quote1), 0);

    i++;
   clearbuff();

    //formatCheck3 here with quote1
    valread = read(new_socket, buffer, 1024);
    printf("%d. %s\n",i, buffer);
    send(new_socket, finish, strlen(finish), 0);

    clearbuff();

    i++;
    valread = read(new_socket, buffer, 1024);
    printf("%d. %s\n",i, buffer);

    //close server
    close(server_fd);

    return 0;
}

bool formatCheck1(char *test, int line, char *format) {
 char *token1 = strtok(test, "|");
 if(strcmp(token1,"REG") ==0) {
        char *token2 = strtok(NULL,"|");
        char *token3 = strtok(NULL,"|");
        size = strlen(token3);
        if(atoi(token2) == size) {
                if(strcmp(token3, format)==0) {
                        return true;
                }
                else {
                        printf("M%dCT - message %d content was not correct",line, line);
                        return false;    }
        }
        else {
                printf("M%dLN - message %d length value was incorrect",line, line);
                return false;       }
 }
 else if(strcmp(token1,"ERR") ==0) {
        char *error = strtok(NULL,"|");
        printf("%s\n", error); }
 else {
 printf("M%dFT - message %d format was broken",line, line);
 return false;
 }
}


bool formatCheck2(char *test, int line) {
 char *token1 = strtok(test, "|");
 if(strcmp(token1,"REG") ==0) {
        char *token2 = strtok(NULL,"|");
        char *token3 = strtok(NULL,"|");
        size = strlen(token3);
        if(atoi(token2) == size) {
                if(token3[size-1]=='.') {
                        return true;
                }
                else {
                        printf("M%dCT - message %d content was not correct",line, line);
                        return false;    }
    }
        else {
                printf("M%dLN - message %d length value was incorrect",line, line);
                return false;       }
 }
 else if(strcmp(token1,"ERR") ==0) {
        char *error = strtok(NULL,"|");
        printf("%s\n", error); }
 else {
 printf("M%dFT - message %d format was broken",line, line);
 return false;
 }
}

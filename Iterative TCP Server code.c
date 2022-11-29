
#include        <sys/socket.h>  
#include        <netinet/in.h>  
#include        <arpa/inet.h>
#include        <netinet/in.h>
#include        <stdio.h>
#include        <string.h>
#include        <stdlib.h>
#include        <errno.h>
#include        <unistd.h> 
#include        <libgen.h>
#include        <pthread.h>
#include        <limits.h>
#include        <sys/time.h>
#include        <ctype.h>
#include        <math.h>

//struct
struct converter{
char input_number[100],output_number[100];
char from_base,to_base;
};








//Power Function
int Power_function(int base,int exp){
  if(exp==0)
    return 1;
  else
    return Power_function(base,exp-1)*base;
}





//Binary To Decimal Function
void Binary_To_Decimal(struct converter *convert1){
  long long input = atoi(convert1->input_number),i=0;
  long long dec[16];
  long long output=0;
  while(i < strlen(convert1->input_number)){
    dec[i] = input % 10;
    input/=10;
    output+=dec[i] * Power_function(2,i);
    i++;
  }
  sprintf(convert1->output_number,"%llu",output);
}





//Decimal To Binary Function
void Decimal_To_Binary(struct converter *convert2){
  long long input = atoi(convert2->input_number), i = 1;
  long long bin=0;
  long long remainder;
  long long output=0;
  while(input != 0){
    remainder = input %2;
    input = input / 2;
    bin += remainder*i;
    i*=10;
  }
  sprintf(convert2->output_number,"%lld",bin);
}





//Hexadecimal To Decimal Function
void Hexadecimal_To_Decimal(struct converter *convert3){
  long long a[10];
  long long output=0;
  int length=strlen(convert3->input_number);
  for(int i = 0 ; i < length ; i++){
    if (convert3->input_number[i] == 'A' || convert3->input_number[i] == 'a')
      a[i] = 10;
    if (convert3->input_number[i] == 'B' || convert3->input_number[i] == 'b')
      a[i] = 11;
    if (convert3->input_number[i] == 'C' || convert3->input_number[i] == 'c')
      a[i] = 12;
    if (convert3->input_number[i] == 'D' || convert3->input_number[i] == 'd')
      a[i] = 13;
    if (convert3->input_number[i] == 'E' || convert3->input_number[i] == 'e')
      a[i] = 14;
    if (convert3->input_number[i] == 'F' || convert3->input_number[i] == 'f')
      a[i] = 15;
    if (convert3->input_number[i] >= '0' && convert3->input_number[i] <= '9')
      a[i] = convert3->input_number[i] - '0' ;
  }
  int x = length;
  for(int i = 0 ; i < x ; i++){
    output+=a[i] * Power_function(16,--length);
  }
  sprintf(convert3->output_number,"%lld",output);
  
}



      
//Decimal To Hexadecimal Function
void Decimal_To_Hexadecimal(struct converter *convert4)
{
  char temp[500]; int t = 0;
  int i = 0,length = strlen(convert4->output_number);
  long long input = atoi(convert4->input_number);
  while(input != 0){
    int t = 0;
    t = input % 16;
    if (t < 10){
      convert4->output_number[i] = t + '0';
    }
    else {
      convert4->output_number[i] = t + '7';
    }
    input/=16;
    t = 0;
    i++;
  }
  for(int k = i-1 ; k>=0 ; k--)
    temp[t++] = convert4->output_number[k];
  strcpy(convert4->output_number,temp);
  
}
//Hexadecimal to binary function
void Hexadecimal_To_Binary(struct converter *convert6){
   Hexadecimal_To_Decimal(convert6);
  long long input = atoi(convert6->output_number), i = 1;
  long long bin=0;
  long long remainder;
  long long output=0;
  while(input != 0){
    remainder = input %2;
    input = input / 2;
    bin += remainder*i;
    i*=10;
  }
  sprintf(convert6->output_number,"%lld",bin);
}




//Binary to hexadecimal function
void Binary_To_Hexadecimal(struct converter *convert5)
{
  //BINARY TO DEC
   char temp[500]; int t = 0;
  long long input = atoi(convert5->input_number),i=0;
  long long dec[100];
  long long output=0;
  while(i < strlen(convert5->input_number))
  {
    dec[i] = input % 10;
    input/=10;
    output+=dec[i] * Power_function(2,i);
    i++;
  }
  //DEC TO HEX
  i = 0;
  while(output!= 0){
    int t = 0;
    t = output % 16;
    if (t < 10){
      convert5->output_number[i] = t + '0';
    }
    else {
      convert5->output_number[i] = t + '7';
    }
    output/=16;
    t = 0;
    i++;
  }
  
   for(int k = i-1 ; k>=0 ; k--)
    temp[t++] = convert5->output_number[k];
  strcpy(convert5->output_number,temp);
}




//////////
//////////
//////////
//////////
//////////
//////////
//////////
//////////

int main(int argc, char ** argv) 
{
  if (argc != 2)
  {
     printf("Please enter the port number\n.");
        exit(0);
  }

  else
    {
    char buff[8000];
   int sockfd;//to create socket
   int newsockfd;//to accept connection
   struct sockaddr_in serverAddress;//server receive on this address
   struct sockaddr_in clientAddress;//server sends to client on this address
    char buffer[8000];
    char *token; 
    struct converter attempt;
   int n;
   socklen_t clientAddressLength;
  token = malloc(sizeof(char)*8000);
      int checkerr;
      char welcoming[500] = "welcome to the server\n";
      char availableconv[500] = "available conversions (3la m7md)\n";

 //create socket
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 //initialize the socket addresses
if (sockfd < 0) {perror("socket() error"); close(sockfd); exit(-1);} //error checks socket creations
  
 memset(&serverAddress,0,sizeof(serverAddress));
 serverAddress.sin_family=AF_INET;
 serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
 serverAddress.sin_port=htons(atoi(argv[1]));

 //bind the socket with the server address and port
 checkerr = bind(sockfd,(struct sockaddr *)&serverAddress, sizeof(serverAddress));
  if (checkerr < 0)
  {
    perror("bind error \n");
    close(sockfd);
    exit(-1);
  }
 //listen for connection from client
 checkerr =listen(sockfd,5);
      if(checkerr < 0)
      {
        perror("listening error");
        close(sockfd);
        exit(-1);
      }



      
 for (;;)
  {
   // printf("\n*****server waiting for new client connection:*****\n");
    clientAddressLength = sizeof(clientAddress);
    newsockfd = accept(sockfd, (struct sockaddr*)&clientAddress, &clientAddressLength);
    if (newsockfd < 0)
    {
      perror("accept error\n");
      close(sockfd);
      close(newsockfd);
      exit(-1);
    }
  //    printf("*******server has accepted a request******\n");
    //acceptance successful -->
    checkerr = send(newsockfd, welcoming, sizeof(welcoming),0); //send welcome message
      if (checkerr< 0 )
          {
            perror("send error\n");
            close(sockfd);
            exit(-1);
          }

      printf("client IP: %s, PORT: %d\n\n",inet_ntop(AF_INET,&clientAddress.sin_addr,buff,sizeof(buff)),ntohs(clientAddress.sin_port));
    
      while (1) //while to receive messages from user
        {
          
          checkerr = recv(newsockfd, buffer, sizeof(buffer), 0);
          if (checkerr < 0)
          {
            perror("recv error\n");
            close(sockfd);
            exit(-1);
          }

          if(strcmp(buffer,"done") != 0 )
          {
            strcpy(token,buffer);
            strcpy(attempt.input_number, strsep(&token,":"));
            strcpy(&attempt.from_base, strsep(&token,":"));
            strcpy(&attempt.to_base, token);
              printf("received request is: %s:%c:%c\n",attempt.input_number, attempt.from_base, attempt.to_base);
            //func
             if((attempt.from_base == 'h' || attempt.from_base == 'H')&&(attempt.to_base == 'B'||attempt.to_base == 'b'))
    Hexadecimal_To_Binary(&attempt);
  if((attempt.from_base == 'b' || attempt.from_base == 'B') && (attempt.to_base == 'D' || attempt.to_base == 'd'))
    Binary_To_Decimal(&attempt);
  else if((attempt.from_base == 'h' || attempt.from_base == 'H') && (attempt.to_base == 'D' || attempt.to_base == 'd'))
    Hexadecimal_To_Decimal(&attempt);
  else if (attempt.from_base == 'd' || attempt.from_base == 'D') {
    if (attempt.to_base == 'B' || attempt.to_base == 'b')
      Decimal_To_Binary(&attempt);
    else if(attempt.to_base == 'H' || attempt.to_base == 'h')
      Decimal_To_Hexadecimal(&attempt);
    }
  else if((attempt.from_base == 'b' || attempt.from_base == 'B')&&(attempt.to_base == 'H' || attempt.to_base == 'h'))
    Binary_To_Hexadecimal(&attempt);

            checkerr = send(newsockfd, attempt.output_number, sizeof(attempt.output_number), 0);
            if (checkerr < 0)
            {
              perror("send error\n");
              close(sockfd);
              close(newsockfd);
              exit(-1);
            }
  
          }
          else
          {
            close(newsockfd);
            break;
          }
          memset(buffer, '\0', strlen(buffer));
          memset(attempt.input_number, '\0', strlen(attempt.input_number));
          memset(&attempt.to_base,'\0',strlen(&attempt.to_base));  
          memset(&attempt.from_base, '\0', strlen(&attempt.from_base));
          memset(attempt.input_number,'\0',strlen(attempt.input_number));
        //  memset(token,'\0',strlen(token));
        } 
      close(sockfd);
      break; 

  }




      
}
  return 0;
}


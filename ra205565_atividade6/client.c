#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
  initscr();
  raw();				         /* Line buffering disabled	*/
  keypad(stdscr, TRUE);	 /* We get F1, F2 etc..		*/
  noecho();			         /* Don't echo() while we do getch */
  curs_set(0);           /* Do not display cursor */
  cbreak();

  int socket_fd;
  struct sockaddr_in target;
  int c;
  int resposta;
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  printf("Socket criado\n");

  target.sin_family = AF_INET;
  target.sin_port = htons(3001);
  inet_aton("127.0.0.1", &(target.sin_addr));
  printf("Tentando conectar\n");
  if (connect(socket_fd, (struct sockaddr*)&target, sizeof(target)) != 0) {
    printf("Problemas na conexao\n");
    return 0;
  }
  printf("Conectei ao servidor\n");

  while(1){
   c = getch();
   if (c!=ERR){
	send(socket_fd, &(c), sizeof(int), 0);
	printf("Escrevi mensagem de ping!\r\n");
	printf("Resposta:\r\n%d\r\n", c);
	printf("grande dia");
   }
   else c = 0;

  }
/*
c = getch();
    if (c!=ERR) (*keybuffer) = c;
    else (*keybuffer) = 0;
    std::this_thread::sleep_for (std::chrono::milliseconds(10));
*/
  endwin();
  close(socket_fd);
  return 0;
}


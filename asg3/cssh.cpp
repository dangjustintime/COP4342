#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <sys/wait.h>

static const char prompt[] = "cssh> ";
static const char sep[] = " \t\n\r";

int main() {
  std::fstream file;
  int argc = 0;
  int proc_id;
  int fd;
  char buf[100];
  char * argv[10];
  char * line;
  char * arg;
  int tty = open("/dev/tty", O_RDWR);
  
  if (tty == -1) {
    fprintf(stderr, "can't open /dev/tty\n");
    exit(EXIT_FAILURE);
  }

  while(1) {
    argc = 0;
    line = readline(prompt);

    // tokenize line into array of strings
    for (arg = strtok(line, sep); arg && argc < 10; arg = strtok(NULL, sep)) {
      argv[argc++] = arg;
    }
    argv[argc] = NULL;

    // print tokens
    for (int i = 0; i < argc; i++) {
      printf("arg[%d] = %s\n", i, argv[i]);
    }
   
    // clear
    if (strcmp(argv[0], "clear") == 0) {
      for (int i = 0; i < 100; i++) {
        std::cout << std::endl;
      }
    // pwd
    } else if (strcmp(argv[0], "pwd") == 0) {
      std::cout << get_current_dir_name() << std::endl; 
    // ls
    } else if (strcmp(argv[0], "ls") == 0) {
      if ((proc_id = fork()) == 0) {
        execle("/bin/ls", "ls", (char *) 0);
        exit(EXIT_FAILURE);
      }
      wait(NULL);
    // echo
    } else if (strcmp(argv[0], "echo") == 0) {
      if ((proc_id = fork()) == 0) {
        execv("/bin/echo", argv);
        exit(EXIT_FAILURE);
      }
      wait(NULL);
    // cd
    } else if (strcmp(argv[0], "cd") == 0) {
      std::cout << "cd" << std::endl;
      chdir(argv[1]);
    // other programs
    } else if (strcmp(argv[0], "") != 0 && argc == 1) {
      if ((proc_id = fork()) == 0) {
        execvp(argv[0], argv);
        exit(EXIT_FAILURE);
      }
      wait(NULL);
    // redirection
    } else if (argc == 3 && strcmp(argv[1], "<") == 0) {
      if ((proc_id = fork()) == 0) {
        execvp(argv[2], argv);
        fd = open(argv[2], O_RDONLY);
        dup2(fd, 1);
        close(fd);
        exit(EXIT_FAILURE);
      }
      wait(NULL);
    } else if (argc == 3 && strcmp(argv[1], ">") == 0) {
      if ((proc_id = fork()) == 0) {
        execvp(argv[0], argv);
        fd = open(argv[0], O_RDONLY);
        dup2(fd, 1);
        close(fd);
        exit(EXIT_FAILURE);
      }
      wait(NULL);
    }
    // clear array
    for (int i = 0; i < argc; i++) {
      argv[i] = '\0';
    }

    // exit
    if (strcmp(line, "exit") == 0) {
      // execlp("chdir", "cd", (char *) 0);
      std::cout << "Exiting cssh....." << std::endl;
      break;
    }
  }
  close(tty);
  exit(EXIT_SUCCESS);
}

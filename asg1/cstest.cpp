#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>

void usage() {
	fprintf(stderr, "Usage: cstest EXPRESSION\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	int Nflag, ch;
	Nflag = 0;
	struct stat buff;
	struct stat buff2;
	double diff;
	int exitCode;
	while(1) {
		while((ch = getopt(argc, argv, "+Ndefrwxnz:?")) != -1) {
			switch(ch) {
				//negate EXPRESSION
				case 'N':
					Nflag = 1;
					break;
				//FILE exists and is a directory
				case 'd':
					stat(argv[optind], &buff);
					if(S_ISDIR(buff.st_mode) != 0) {
						exitCode = 0;
						if(Nflag) {
							exitCode = 1;
							Nflag = 0;
						}
					} else {	
						exitCode = 1;	
						if(Nflag) {
							exitCode = 0;
							Nflag = 0;
						}
					}
					break;
				//FILE exists
				case 'e':
					if(stat(argv[optind], &buff) == -1) {
						exitCode = 1;
						if(Nflag) {
							exitCode = 0;	
							Nflag = 0;
						}
					} else {
						exitCode = 0;
						if(Nflag) {
							exitCode = 1;	
							Nflag = 0;
						}
					}
					break;
				//FILE exists and is a regular file
				case 'f':
					stat(argv[optind], &buff);
					if(S_ISREG(buff.st_mode) != 0) {
						exitCode = 0;
						if(Nflag) {
							exitCode = 1;	
							Nflag = 0;
						}
					} else {
						exitCode = 1;	
						if(Nflag) {
							exitCode = 0;
							Nflag = 0;
						}
					}
					break;
				//FILE exists read permission is granted
				case 'r':
					stat(argv[optind], &buff);
					if(buff.st_mode & S_IREAD) {
						exitCode = 0;	
						if(Nflag) {
							exitCode = 1;
							Nflag = 0;
						}
					} else {
						exitCode = 1;
						if(Nflag) {
							exitCode = 0;
							Nflag = 0;
						}
					}
					break;
				//FILE exists write permission is granted
				case 'w':
					stat(argv[optind], &buff);
					if(buff.st_mode & S_IWRITE) {
						exitCode = 0;
						if(Nflag) {
							exitCode = 1;
							Nflag = 0;
						}
					} else {
						exitCode = 1;
						if(Nflag) {
							exitCode = 0;
							Nflag = 0;
						}
					}
					break;
				//FILE exists execute permission is granted
				case 'x':			
					stat(argv[optind], &buff);
					if(buff.st_mode & S_IEXEC) {
						exitCode = 0;
						if(Nflag) {
							exitCode = 1;
							Nflag = 0;
						}
					} else {	
						exitCode = 1;
						if(Nflag) {
							exitCode = 0;
							Nflag = 0;
						}
					}
					break;
				//FILE1 -n FILE2
				//FILE1 is newer (modification date) than FILE2
				case 'n':
					stat(argv[optind - 1], &buff);
					stat(argv[optind], &buff2);
					diff = difftime(buff.st_mtime,buff2.st_mtime);
					if(diff > 0) {	
						exitCode = 0;
						if(Nflag) {
							exitCode = 1;
							Nflag = 0;
						}
					} else {						
						exitCode = 1;
						if(Nflag) {
							exitCode = 0;
							Nflag = 0;
						}
					}
					break;
				//VALUE is "0" or an empty string
				case 'z':
					if(strcmp(optarg, "") == 0 || strcmp(optarg,"0") == 0) {
						exitCode = 0;	
						if(Nflag) {
							exitCode = 1;
							Nflag = 0;
						}
					} else {
						exitCode = 1;
						if(Nflag) {
							exitCode = 0;
							Nflag = 0;
						}
					}
					break;
				case ':':
					fprintf(stderr, "option -%c requires an argument", optopt);
					usage();
					break;
				case '?':
					break;
				default:
					fprintf(stderr, "unrecognized option -%c\n", optopt);
					usage();
			}
		}
		if(optind >= argc) break;
		++optind;
	}
	exit(exitCode);
	return 0;
}

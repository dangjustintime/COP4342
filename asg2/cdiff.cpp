#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <list>
#include <vector>
#include <fstream>

//the output of the utility is to be written/redirected to the file instead
//of standard output.
void optO(char * file1, char * file2) {
	std::fstream f1;
	std::fstream f2;
	std::ofstream outfile;
	std::vector<std::string> buf1;
	std::vector<std::string> buf2;
	std::list<std::string> changes1;
	std::list<std::string> changes2;
	char line1[100];
	char line2[100];

	f1.open("file1", std::fstream::in | std::fstream::out | std::fstream::app);
	f2.open("file2", std::fstream::in | std::fstream::out | std::fstream::app);
	outfile.open("file");

	while(!f1.eof() && !f2.eof()) {
		if(!f1.eof()) {
			f1.getline(line1, 100);
			buf1.push_back(line1);
		}
		if(!f2.eof()) {
			f2.getline(line2, 100);
			buf2.push_back(line2);
		}
	}
	//close file
	f1.close();
	f2.close();
		
	//check change
	for(unsigned int i = 0; i < buf1.size(); i++) {
		if(i < buf2.size()) {
			//check change
			if(buf1[i].compare(buf2[i]) != 0) {
				changes1.push_back(buf1[i]);
				changes2.push_back(buf2[i]);
			} else {
				outfile << "CHANGES" << std::endl;
				while(!changes1.empty()) {
					outfile << "< " << changes1.front() << std::endl;
					changes1.pop_front();
				}
				outfile << "---" << std::endl;
				while(!changes2.empty()) {
					outfile << "< " << changes2.front() << std::endl;
					changes2.pop_front();
				}
			}
			if(changes1.front() == changes2.back()) {
				changes2.pop_back();
				outfile << "ADD" << std::endl;
				while(!changes2.empty()) {
					outfile << "> " << changes2.front() << std::endl;
					changes2.pop_front();
				}
				changes1.pop_front();
			} else if(changes1.back() == changes2.front()) {
				changes1.pop_back();
				outfile << "DELETE" << std::endl;
				while(!changes1.empty()) {
					outfile << "< " << changes1.front() << std::endl;
					changes1.pop_front();
				}
			}
		} else {
			changes1.push_back(buf1[i]);
		}
	}
	if(!changes1.empty()) {
		outfile << "DELETE" << std::endl;
		do {
			outfile << "< " << changes1.front() << std::endl;
			changes1.pop_front();
		} while(!changes1.empty());
	}
	if(!changes2.empty()) {
		outfile << "ADD" << std::endl;
		do {
			outfile << "> " << changes2.front() << std::endl;
			changes2.pop_front();
		} while(!changes2.empty());
	}
	
	outfile.close();
}

//delete the least recently modified file in
//case the two provided files are identical.
void optD(char * file1, char * file2) {
	std::fstream f1;
	std::fstream f2;
	std::vector<std::string> buf1;
	std::vector<std::string> buf2;
	char line1[100];
	char line2[100];
	bool issame = true;
	struct stat statbuf1;
	struct stat statbuf2;

	f1.open("file1", std::fstream::in | std::fstream::out | std::fstream::app);
	f2.open("file2", std::fstream::in | std::fstream::out | std::fstream::app);

	while(!f1.eof() && !f2.eof()) {
		if(!f1.eof()) {
			f1.getline(line1, 100);
			buf1.push_back(line1);
		}
		if(!f2.eof()) {
			f2.getline(line2, 100);
			buf2.push_back(line2);
		}
	}
	//close file
	f1.close();
	f2.close();
	if(buf1.size() == buf2.size()) {
		for(unsigned int i = 0; i < buf1.size(); i++) {
			if(buf1[i] != buf2[i]) issame = false;
		}
	} else {
		issame = false;
	}
	if(issame) {
		stat(file1, &statbuf1);
		stat(file2, &statbuf2);
		if(statbuf1.st_mtime < statbuf2.st_mtime) {
			unlink(file1);	
		} else {
			unlink(file2);
		}
		
		exit(EXIT_SUCCESS);
	} else {
		exit(EXIT_FAILURE);
	} 
}

int main(int argc, char * argv[]) {
	int opt;
	char * file1;
	char * file2;

	while((opt = getopt(argc, argv, "do")) != -1) {
		switch(opt) {
			case 'd':
				file1 = argv[optind];
				optind++;
				file2 = argv[optind];
				optD(file1, file2);
				break;
			
			case 'o':
				file1 = argv[optind];
				optind++;
				file2 = argv[optind];
				optO(file1, file2);
				break;
			default:
				break;
		}
	}
	return 0;
}

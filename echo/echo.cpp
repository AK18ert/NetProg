#include <boost/program_options.hpp>
#include <arpa/inet.h>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;
namespace po = boost::program_options;




int main(int argc, char** argv){
	
	
	
	try {
		if(argc == 1) {
            cout << desc << endl;
            return 0;
        }
		
		int s = socket(AF_INET, SOCK_STREAM, 0); 
		if (s==-1){
			throw std::system_error(errno, std::generic_category(), "Ошибка создания сокета");
		}
		unique_ptr<sockaddr_in>  * self_addr = (new sockaddr_in);
		s_addr->sin_family = AF_INET; 
		s_addr->sin_port = htons(port); 
		s_addr->sin_addr.s_addr = INADDR_ANY; 
		
		rc = bind(s,(const sockaddr*) self_addr,sizeof(sockaddr_in));
		if (rc==-1){
			throw std::system_error(errno, std::generic_category(), "Ошибка создания сокета");
		}
		rb = listen(server_socket, 5);
        if(rb == -1) {
            throw std::system_error(errno, std::generic_category(), "Ошибка при прослушивании сокета");
        }
		
		
		
		
		
		
	}
	
	
	
	return 0;
}
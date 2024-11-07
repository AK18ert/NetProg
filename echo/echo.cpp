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
	
	po::options_description desc("Options");
    desc.add_options()("help,h", "Вывести справку")("port,p", po::value<int>()->default_value(7777), "Порт для сервера");


	po::variables_map vm;
	
	try {
				
		if(argc == 1) {
            cout << desc << endl;
            return 0;
        }
		
		po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
		
		if(vm.count("help")) {
            cout << desc << endl;
            return 0;
        }
		
		int port = vm["port"].as<int>();
		if (!(port > 0 && port <= 65535)){
			cerr << "Ошибка: некорректный порт: " << port << ". Порт должен быть в диапазоне 1-65535." << endl;
            return 1;
		}
		
		int s = socket(AF_INET, SOCK_STREAM, 0); 
		if (s==-1){
			throw std::system_error(errno, std::generic_category(), "Ошибка создания сокета");
		}
        unique_ptr<sockaddr_in> server_addr(new sockaddr_in);
		server_addr->sin_family = AF_INET; 
		server_addr->sin_port = htons(port); 
		server_addr->sin_addr.s_addr = INADDR_ANY; 
		
		int rc = bind(s, ((sockaddr*)server_addr.get()) ,sizeof(sockaddr_in));
		if (rc==-1){
			throw std::system_error(errno, std::generic_category(), "Ошибка создания сокета");
		}
		rc = listen(s, 5);
        if(rc == -1) {
            throw std::system_error(errno, std::generic_category(), "Ошибка при прослушивании сокета");
        }
		
		
		
		
		while (true){
			sockaddr_in client_addr;
            socklen_t len = sizeof(client_addr);
			
			int new_sock = accept(s, (sockaddr*)&client_addr, &len);
            if(new_sock == -1) {
                throw std::system_error(errno, std::generic_category(), "Ошибка при принятии соединения");
            }
			
			int lenth = 1024;                              
            std::unique_ptr<char[]> buf(new char[lenth]);  
            int rc = recv(new_sock, buf.get(), lenth, 0); 

            if(rc < 0) {
                throw std::system_error(errno, std::generic_category(), "Ошибка получения данных");
            } else if(rc == 0) {
                close(new_sock);
                return 0;
            }
			
			std::string res(buf.get(), rc);
			
			if(rc == lenth) {                         
                int tail_size;                          
                ioctl(new_sock, FIONREAD, &tail_size); 

                if(tail_size > 0) {         
                    if(tail_size > lenth) { 
                        buf = std::unique_ptr<char[]>(new char[tail_size]);
                    }
                    rc = recv(new_sock, buf.get(), tail_size, 0); 
                    if(rc < 0) {
                        throw std::system_error(errno, std::generic_category(), "Ошибка получения остаточных данных");
                    }
                    res.append(buf.get(), rc); 
                }
            }
			
			int sent_bytes = send(new_sock, res.c_str(), res.size(), 0);
			
            if(sent_bytes < 0) {
                throw std::system_error(errno, std::generic_category(), "Ошибка отправки данных");
            }
			
			close(s);
			
		}
		
	} catch(const std::system_error& e) {
		cerr << "Ошибка" << endl;
	}

	return 0;
}
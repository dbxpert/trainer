#ifndef EXECUTOR_TRAINER_SERVER_H_
#define EXECUTOR_TRAINER_SERVER_H_

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <string>
#include "message.h"

class Server {
	public:
		Server();
		~Server(); 

		void Run();

	private:
		void Listen();
		Message Receive();
		void Send(std::string msg);
		void Process(std::vector<std::string> args);

		const static unsigned int BUF_SIZE = 1024;

		bool running_;
		int socket_fd_;
		int accepted_fd_;
		socklen_t size_;

		struct sockaddr_in host_addr_;
		struct sockaddr_in client_addr_;

		char buffer_[BUF_SIZE];
};

#endif /* EXECUTOR_TRAINER_SERVER_H_ */

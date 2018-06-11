#include "Connection.h"
#include "../Constants.h"
#include <iostream>
#include <sys/socket.h>

Connection::Connection(int connection) {
        socket = connection;
}

void Connection::start() {
        std::cout << "Connection established; the file descriptor for this connection is " << socket << std::endl;
        // continuous loop for listening
        char buffer[Constants::HEADER_LENGTH];
        double data;

        while (true) {
                int status = recv(socket, &data, sizeof(data), 0);
                // no input received
                if (status == 0) {
                        continue;
                }
                // connection timed-out
                if (status == -1) {
                        std::cout << "Connection disconnected for file descriptor " << socket << std::endl;
                        return;
                }
                std::cout << data << std::endl;
        }
}

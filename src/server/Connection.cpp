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
        char buffer[HEADER_LENGTH];

        while (true) {
                // no input received
                if (recv(socket, buffer, HEADER_LENGTH, 0) == 0) {
                        continue;
                }
                // connection timed-out
                if (recv(socket, buffer, HEADER_LENGTH, 0) == -1) {
                        std::cout << "Connection disconnected for file descriptor " << socket << std::endl;
                        return;
                }
                std::cout << buffer << std::endl;
        }
}

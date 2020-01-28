#ifndef EX4_CONNECTIONMANAGER_H
#define EX4_CONNECTIONMANAGER_H

#include <iostream>
#include <string.h>
#include <stdexcept>
#include <sys/socket.h>
#include <cerrno>
#include <unistd.h>
#include <arpa/inet.h>
#include <system_error>
#include <string>

#define END_READ '\0'
#define TIMEOUT -2

using namespace std;
namespace connection_manager {

    struct Socket {

        int socketFD;

        Socket() {
            socketFD = socket(AF_INET, SOCK_STREAM, 0);
            if (socketFD < 0) {
                throw system_error(error_code(errno, generic_category()), "Error: cannot open socket.");
            }
        }

        Socket(int newSocketFD) {
            this->socketFD = newSocketFD;
        }

        int getSocketFD() {
            return this->socketFD;
        }

        void timeOutSetting(int seconds, int useconds = 0) {
            timeval timeout;
            timeout.tv_sec = seconds;
            timeout.tv_usec = useconds;

            // set time to timeout.
            if (-1 == setsockopt(socketFD, SOL_SOCKET, SO_RCVTIMEO,
                                 (char *) &timeout, sizeof(timeout))) {
                throw system_error(error_code(errno, generic_category()), "Error: cannot set timeout.");
            }
        }

        void close() {
            if (::close(socketFD) < 0) {
                throw system_error(error_code(errno, generic_category()), "Error: cannot close socket.");
            }
        }
    };

    class timeout_error : public runtime_error {
    public:
        timeout_error(const char *err) : runtime_error(err) {}
    };
}


#endif //EX4_CONNECTIONMANAGER_H

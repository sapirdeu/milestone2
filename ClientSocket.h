#ifndef EX4_CLIENTSOCKET_H
#define EX4_CLIENTSOCKET_H

#include "ConnectionManager.h"

using namespace connection_manager;

class ClientSocket {
    Socket cSocket;
public:

    // ctor
    ClientSocket(Socket sock) : cSocket(sock) {}

    int getSocketFD() {
        return this->cSocket.getSocketFD();
    }

    // the method sets timeout
    void timeOutSetting(int seconds, int useconds = 0) {
        cSocket.timeOutSetting(seconds, useconds);
    }

    // the method reads from the buffer
    string read(int size) {
        char *buff = new char[size + 1];
        int byteRead = ::read(cSocket.socketFD, buff, size);

        if (byteRead < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                throw timeout_error("Error: read timeout.");
            }
            throw system_error(error_code(errno, generic_category()), "Error: cannot read from socket.");
        }

        buff[byteRead] = END_READ;
        string data = string(buff);
        delete[] buff;

        return data;
    }

    // the method writes to the buffer
    void write(string toWrite) {
        const char *toWriteChars = toWrite.c_str();

        int size = strlen(toWriteChars);
        int byteWritten = ::write(cSocket.socketFD, toWriteChars, size);
        if (byteWritten < 0) {
            perror("Error: cannot write to socket.");
            exit(1);
        }
    }

    void close() {
        cSocket.close();
    }
};

#endif //EX4_CLIENTSOCKET_H

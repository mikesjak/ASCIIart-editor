
#include "CKeyHandler.hpp"

int CKeyHandler::kbhit() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, nullptr, nullptr, &tv) > 0;
}

int CKeyHandler::getch() {
    int r;
    unsigned char c;
    if ((r = int(read(0, &c, sizeof(c)))) < 0) {
        return r;
    } else {
        return c;
    }
}
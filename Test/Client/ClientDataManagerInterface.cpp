
// Service qui créer un socket UNIX avec le serveur et passe les argument;

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char* argv[])
{
    struct sockaddr_un addr;
    int fd;

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        std::cerr << "Error: socket" << std::endl;
        return 1;
    }

    std::cout << "Starting client" << std::endl;

    memset(&addr, 0, sizeof(addr));

    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "/tmp/dm_interface", sizeof(addr.sun_path) - 1);

    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
        std::cerr << "Error: connect" << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        std::cout << "write : " << argv[i] << std::endl;
        if (write(fd, argv[i], strlen(argv[i]) + 1) == -1)
        {
            std::cerr << "Error: write" << std::endl;
            return 1;
        }
    }

    return 0;
}

// serveur qui attend des connections avec des sockets UNIX et qui affiche les arguments reçus;

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>

int main()
{
    struct sockaddr_un addr;
    int fd, cfd;
    socklen_t len;
    char buf[100];

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        std::cerr << "Error: socket" << std::endl;
        return 1;
    }
    std::cout << "Starting server" << std::endl;

    memset(&addr, 0, sizeof(addr));

    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "/tmp/dm_interface", sizeof(addr.sun_path) - 1);

    if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
        std::cerr << "Error: bind" << std::endl;
        return 1;
    }

    while (1)
    {
        if (listen(fd, 5) == -1)
        {
            std::cerr << "Error: listen" << std::endl;
            return 1;
        }

        if ((cfd = accept(fd, (struct sockaddr*)&addr, &len)) == -1)
        {
            std::cerr << "Error: accept" << std::endl;
            return 1;
        }
        std::cout << "Connection receive" << std::endl;
        ssize_t n = 0;

        // tant que la connection est ouverte, on lit les données reçues
        do
        {
            n = recv(cfd, &buf, sizeof(buf), 0);
            if (n == -1)
            {
                std::cerr << "Error: read" << std::endl;
                return 1;
            }
            else if (n == 0)
            {
                std::cout << "Client disconnected" << std::endl;
                break;
            }
            std::cout << "read : " << buf << std::endl;

            // On remet à zéro le buffer pour éviter d'afficher des données résiduelles
            memset(buf, 0, sizeof(buf));
        } while (n > 0);
    }

    return 0;
}
#include <SFML/Network.hpp>
#include <iostream>

int main()
{
    // Create a listener socket and make it wait for new
    // connections on port 55001
    sf::TcpListener listener;
    listener.listen(55001);
    // Endless loop that waits for new connections
    bool running = true;
    while (running)
    {
        sf::TcpSocket client;
        if (listener.accept(client) == sf::Socket::Done)
        {
            // A new client just connected!
            std::cout << "New connection received from " << client.getRemoteAddress() << std::endl;
            // doSomethingWith(client);
        }
    }
}
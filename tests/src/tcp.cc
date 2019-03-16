#include <SFML/Network.hpp>
#include <list>
#include <iostream>
#include <string>
#include <array>
#include <vector>

struct Argparse
{
    std::string path;
    std::vector<std::string> args;
};

Argparse parse(int argc, char* argv[])
{
    Argparse argparse;
    if(argc)
    {
        argparse.path = std::string(argv[0]);
        if(argc > 1)
        {
            // argparse.args = std::array<std::string,(size_t)(argc-1)>;
            
            for(size_t i(1); i < argc; i++)
            {
                argparse.args.push_back(std::string(argv[i]));
            }
        }
    }
    return argparse;
}

int main(int argc, char* argv[])
{   
    // Argparse argparse = parse(argc,argv);
    // std::cout << argparse.path << std::endl;
    // for(auto i: argparse.args)
    //     std::cout << i << std::endl;
    // return 0;

    // Create a socket to listen to new connections
    sf::TcpListener listener;
    if(argc > 1)
        listener.listen(std::stoi(std::string(argv[1])));
    else
        listener.listen(55001);
        
    // Create a list to store the future clients
    std::list<sf::TcpSocket*> clients;
    // Create a selector
    sf::SocketSelector selector;
    // Add the listener to the selector
    selector.add(listener);
    // Endless loop that waits for new connections
    bool running = true;
    while (running)
    {
        // Make the selector wait for data on any socket
        if (selector.wait())
        {
            // Test the listener
            if (selector.isReady(listener))
            {
                // The listener is ready: there is a pending connection
                sf::TcpSocket* client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Done)
                {
                    std::cout << "New connection received from(1) " << client->getRemoteAddress() << std::endl;
                    // Add the new client to the clients list
                    clients.push_back(client);
                    // Add the new client to the selector so that we will
                    // be notified when he sends something
                    selector.add(*client);
                }
                else
                {
                    // Error, we won't get a new connection, delete the socket
                    delete client;
                }
            }
            else
            {
                // The listener socket is not ready, test all other sockets (the clients)
                for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
                {
                    sf::TcpSocket& client = **it;
                    client.setBlocking(false);
                    if (selector.isReady(client))
                    {   
                        std::cout << "New connection received from(2) " << client.getRemoteAddress() << std::endl;
                        // The client has sent some data, we can receive it
                        sf::Packet packet;
                        if (client.receive(packet) == sf::Socket::Done)
                        {
                            std::cout << packet << std::endl;
                            sf::Packet message;
                            message << "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
                            client.send(message);
                            std::cout << "envoyé?" << std::endl;
                        }
                        std::cout << "après l envoie" << std::endl;
                    }
                }
                std::cout << "après la boucle for" << std::endl;
            }
            // std::cout << "après le if" << std::endl;
        }
    }
}
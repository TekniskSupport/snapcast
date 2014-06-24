//
//  Weather update client in C++
//  Connects SUB socket to tcp://localhost:5556
//  Collects weather updates and finds avg temp in zipcode
//
//  Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
//
#include <zmq.hpp>
#include <iostream>
#include <sstream>

int main (int argc, char *argv[])
{
    zmq::context_t context (1);

    //  Socket to talk to server
//    std::cout << "Collecting updates from weather server…\n" << std::endl;
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://192.168.0.2:123458");
    //  Subscribe to zipcode, default is NYC, 10001
    const char* filter = "";
    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));

    //  Process 100 updates
    int update_nbr;
    long total_temp = 0;
    const size_t size(1024);
    char msg[size];
//    for (update_nbr = 0; update_nbr < 100; update_nbr++) {
    while (1)
    {
        zmq::message_t update;
        subscriber.recv(&update);
//        std::cerr << "received\n";
//        std::istringstream iss(static_cast<char*>(update.data()));
//        iss >> zipcode >> relhumidity;
        memcpy(&msg[0], update.data(), size);
//        std::cout << "update\n";
        for (size_t n=0; n<size; ++n)
            std::cout << msg[n] << std::flush;
//        std::cout << std::flush;
//        std::cerr << "flushed\n";
    }
    return 0;
}

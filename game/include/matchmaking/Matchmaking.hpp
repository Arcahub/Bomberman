/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Matchmaking
*/

#ifndef MATCHMAKING_HPP_
#define MATCHMAKING_HPP_

#include <string>

#define MATCHMAKING_SERVER_URL "http://localhost:57468"

struct ServerData {
    std::string ip;
    unsigned int port;
};

class Matchmaking {
public:
    static std::string
    RegisterServer(const std::string& ip, unsigned short port);
    static void UnRegisterServer(const std::string& id);
    static ServerData GetBestFitServer();

protected:
private:
};

#endif /* !MATCHMAKING_HPP_ */

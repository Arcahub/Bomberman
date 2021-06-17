/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Matchmaking
*/

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "matchmaking/Matchmaking.hpp"
#include "network/Http.hpp"

ServerData Matchmaking::GetBestFitServer()
{
    http::Request regreq(std::string(MATCHMAKING_SERVER_URL) + "/api/Lobby/");
    auto response = regreq.send("OPTIONS");
    std::string strret
        = std::string({ response.body.begin(), response.body.end() });
    auto parsed_data = nlohmann::json::parse(strret);
    ServerData ret;

    ret.ip = parsed_data["ip"];
    ret.port = parsed_data["port"];
    std::cout << "[Matchmaking Server] Found server, ip=" << ret.ip
              << " port=" << ret.port << std::endl;
    return ret;
}

std::string
Matchmaking::RegisterServer(const std::string& ip, unsigned short port)
{
    http::Request regreq(std::string(MATCHMAKING_SERVER_URL) + "/api/Lobby/");
    nlohmann::json data = { { "Ip", ip },
                            { "Port", port },
                            { "LobbyState", 0 },
                            { "PlayerCount", 1 } };
    std::string raw_data = data.dump();
    auto response
        = regreq.send("PUT", raw_data, { "Content-Type: application/json" });
    std::string strret
        = std::string({ response.body.begin(), response.body.end() });
    auto parsed_data = nlohmann::json::parse(strret);

    std::cout << "[Matchmaking Server] Registered server with id "
              << parsed_data["id"] << std::endl;
    return parsed_data["id"];
}

void Matchmaking::UnRegisterServer(const std::string& id)
{
    http::Request regreq(
        std::string(MATCHMAKING_SERVER_URL) + "/api/Lobby/" + id);
    auto response = regreq.send("DELETE");
    std::string strret
        = std::string({ response.body.begin(), response.body.end() });

    std::cout << "[Matchmaking Server] Unregistered server." << std::endl;
}

#ifndef __IRCBOT_HPP_INCLUDED
#define __IRCBOT_HPP_INCLUDED

#include <unistd.h>
#include <memory>
#include <ctime>
#include "socket.hpp"
#include "handlermanager.hpp"
#include "handlers/handlers.hpp"
#include "util.hpp"
#include "irc_types.hpp"

class IRCBot
{
    private:
    Socket ircsocket;
    HandlerManager hmn;
    size_t timeout_threshold = 600;
    time_t server_idle_since;
    void RegisterHandlers();

    public:
    std::string nick;
    irc::line_t line;

    struct
    {
        std::string host;
        size_t port;
    } netinfo;

    std::map<std::string, std::unique_ptr<irc::channel_t> > channels;
    std::vector<std::string> autojoin_channels;

    IRCBot(std::string _host, size_t _port, std::string _nickname, std::vector<std::string> channels);
    virtual ~IRCBot();
    irc::line_t Process(std::string line);
    void Nick(std::string nickname);
    void Register();
    void Ping(std::string str);
    void Pong(std::string str);
    void Join(std::string channel);
    void Part(std::string channel, std::string part_message = "");
    void Quit(std::string quit_message = "");
    void Say(std::string destination, std::string message);
    void Notice(std::string destination, std::string message);
    void Mode(std::string destination, std::string mode);
    void Quote(std::string message);
    void Tick();

    bool IsAlive() const;
};

#endif

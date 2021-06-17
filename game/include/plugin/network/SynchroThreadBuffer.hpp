#ifndef THREADSYNCHROBUFFER_HPP_
#define THREADSYNCHROBUFFER_HPP_

#include "Packet.hpp"
#include "concurrent/ConcurrentQueue.hpp"
#include "concurrent/SynchroRinger.hpp"

class SynchroThreadBuffer {
public:
    SynchroThreadBuffer() = default;
    ~SynchroThreadBuffer() = default;

    ConcurrentQueue<Packet> incoming_packets;

    ConcurrentQueue<Packet> outgoing_packets_lp;
    SynchroRinger outgoing_lp_sync_ringer;

    ConcurrentQueue<Packet> outgoing_packets_hp;
    SynchroRinger outgoing_hp_sync_ringer;

protected:
private:
};

#endif /* !THREADSYNCHROBUFFER_HPP_ */

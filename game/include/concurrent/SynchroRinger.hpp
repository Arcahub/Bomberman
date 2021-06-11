/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** SynchroRinger
*/

#ifndef SYNCHRORINGER_HPP_
#define SYNCHRORINGER_HPP_

#include <condition_variable>
#include <functional>
#include <mutex>

class SynchroRinger {
public:
    SynchroRinger();
    ~SynchroRinger();

    SynchroRinger(const SynchroRinger&) = delete;
    SynchroRinger(SynchroRinger&&) = delete;

    void ring();
    void waitForOrder();
    void waitForOrder(std::function<bool()> predicate);

    std::mutex& getUnderlyingMutex();

protected:
private:
    std::mutex m_mut;
    std::condition_variable m_cv;
};

#endif /* !SYNCHRORINGER_HPP_ */

/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** SynchroRinger
*/

#include "concurrent/SynchroRinger.hpp"
#include <functional>

SynchroRinger::SynchroRinger()
{
}

SynchroRinger::~SynchroRinger()
{
}

void SynchroRinger::waitForOrder()
{
    std::unique_lock<std::mutex> lk(this->m_mut);

    // Using wait without a predicate shouldn't be a problem, we don't care
    // about spurious wakeups.
    m_cv.wait(lk);
}

void SynchroRinger::waitForOrder(std::function<bool()> predicate)
{
    std::unique_lock<std::mutex> lk(this->m_mut);

    m_cv.wait(lk, predicate);
}

void SynchroRinger::ring()
{
    std::unique_lock<std::mutex> lk(this->m_mut);

    m_cv.notify_all();
}

std::mutex& SynchroRinger::getUnderlyingMutex()
{
    return this->m_mut;
}

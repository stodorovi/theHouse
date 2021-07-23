#include "Timer.h"

namespace house {

    Timer::Timer(uint32_t targetTime)
    : m_startTime{0}, m_targetTime{targetTime},
    m_started{false}, m_finished{true}
    {}

    void Timer::start() noexcept {
        m_started   = true;
        m_startTime = SDL_GetTicks();
    };

    void Timer::reset() noexcept {
        start();
        m_finished = false;
    }

    bool Timer::started() const noexcept { return m_started; }

    bool Timer::finished() noexcept {
        if (!m_finished && m_started) {
            auto elapsedTime = SDL_GetTicks() - m_startTime;
            if (elapsedTime >= m_targetTime) {
                m_finished = true;
                m_started  = false;
                return m_finished;
            }
            return false;
        }
        
        return m_finished;
    }

} // namespace house
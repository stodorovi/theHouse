#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"

namespace house {

    class Timer {
        private:
         uint32_t m_startTime;
         uint32_t m_targetTime;

         bool m_started;
         bool m_finished;

        public:
         /**
          * @param tagetTime Target time in miliseconds.
         */
         Timer(uint32_t targetTime);
         void start() noexcept;
         void reset() noexcept;

         bool started() const noexcept;
         bool finished() noexcept;
    };

} // namespace house

#endif // TIMER_H
#ifndef GAME_EXCEPTION_H
#define GAME_EXCEPTION_H

#include <exception>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include <iomanip>

namespace house {

    class GameException : public std::exception {
        private:
         std::string m_message;

        public:
         GameException(const std::string &message);

         const char* what() const noexcept;
         void writeToLog() const;
    };
    
} // namespace house

#endif // !GAME_EXCEPTION_H
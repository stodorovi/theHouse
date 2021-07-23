#include "GameException.h"

namespace house {
    
    GameException::GameException(const std::string &message)
    : std::exception(), m_message{message}
    {}

    const char* GameException::what() const noexcept {
        return m_message.c_str();
    }

    void GameException::writeToLog() const {
        const char *logPath = "log.txt";

        time_t now = time(0);
        std::tm tmBuf;
        localtime_s(&tmBuf, &now);
        std::stringstream  timeString;
        timeString << std::put_time(&tmBuf, "%d %b %Y, %H:%M:%S");

        std::ofstream logFile(logPath, std::ios_base::app);
        logFile << "[" << timeString.str() << "] - " << m_message << "\n";
        logFile.close();
    }

} // namespace house
#ifndef GAME_MISSION_H
#define GAME_MISSION_H

#include <functional>
#include <string>

namespace house {

    class Mission {
        private:
         std::string m_missionTitle;
         std::string m_missionDescription;

         std::function<bool ()> m_task;
         std::function<void ()> m_completionFunction;
         bool m_completed;

        public:
         Mission(const std::string &missionTitle,
                 std::function<bool ()> completionCondition,
                 std::function<void ()> onCompletionFunction,
                 const std::string &description = "");

         const std::string& getTitle() const noexcept;
         const std::string& getDescription() const noexcept;

         bool checkIfCompleted();
         bool isCompleted() const noexcept;
         void onComplete();
    };
    
} // namespace house

#endif // !GAME_MISSION_H
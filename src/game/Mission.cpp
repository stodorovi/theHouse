#include "Mission.h"

namespace house {
    
    Mission::Mission(const std::string &missionTitle,
                     std::function<bool ()> completionCondition,
                     std::function<void ()> onCompletionFunction,
                     const std::string &description)
    : m_missionTitle{missionTitle}, m_missionDescription{description},
    m_task{completionCondition}, m_completionFunction{ onCompletionFunction},
    m_completed{false}
    {}

    const std::string& Mission::getTitle() const noexcept {
        return m_missionTitle;
    }

    const std::string& Mission::getDescription() const noexcept {
        return m_missionDescription;
    }

    bool Mission::checkIfCompleted() {
        if (m_completed) {
            return m_completed;
        }
        else {
            bool completionState = m_task();
            if (completionState) {
                m_completed = completionState;
            }
        }
        
        return m_completed;
    }

    bool Mission::isCompleted() const noexcept {
        return m_completed;
    }

    void Mission::onComplete() {
        m_completionFunction();
    }

} // namespace house
#pragma once

#include <memory>
#include <optional>
#include "Indicator.hpp"
#include "Logger.hpp"

class AbstractState {
    public:
        AbstractState() {}
        /**
         * @brief Run the actions of this state and updates the indicator, eventually transitioning to the next one.
         * 
         * @param indicator 
         * 
         * @return std::unique_ptr<AbstractState> The next state to enter.
         */
        std::unique_ptr<AbstractState> run(Indicator &indicator) {
            indicator.update(this->indicatorColor());
            return std::move(this->doStateActions());
        }
        
        virtual ~AbstractState() {};

    protected:
        /**
         * @brief Each state is associated with an indicator color.
         * Implementations of this function simply return the associated color. 
         * 
         * @return IndicatorColor 
         */
        virtual inline IndicatorColorRGBW indicatorColor() const = 0;

        /**
         * @brief Implementing classes put their behaviour in here.
         * This function shall not block, instead returning control to the caller.
         * 
         * @return std::optional<std::unique_ptr<AbstractState>> 
         * If there is no state change then the optional will have no value.
         * On a state change the optional will be filled with the next state.
         */
        virtual std::unique_ptr<AbstractState> doStateActions() = 0;
};
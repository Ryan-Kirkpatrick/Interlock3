#include "AbstractState.hpp"

class WaitingState : public AbstractState {
    using AbstractState::AbstractState;
    protected:
        std::unique_ptr<AbstractState> doStateActions() override;
        inline IndicatorColorRGBW indicatorColor() const override;
};
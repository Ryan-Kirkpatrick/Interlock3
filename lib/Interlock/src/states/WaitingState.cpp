#include "WaitingState.hpp"


std::unique_ptr<AbstractState> WaitingState::doStateActions() {
    
}

inline IndicatorColorRGBW WaitingState::indicatorColor() const override {
    return IndicatorColors::BLUE;
}

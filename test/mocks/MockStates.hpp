#pragma once

#include "AbstractState.hpp"


class MockStateNoStateChange : public AbstractState {
    using AbstractState::AbstractState;

    inline IndicatorColorRGBW indicatorColor() const override {
        return IndicatorColors::RED;
    }

    std::unique_ptr<AbstractState> doStateActions() override {
        return  std::make_unique<MockStateNoStateChange>(MockStateNoStateChange(cardChecker, logger));
    }
};

class MockStateChangeState : public AbstractState {
    using AbstractState::AbstractState;

    inline IndicatorColorRGBW indicatorColor() const override {
        return IndicatorColors::GREEN;
    }

    std::unique_ptr<AbstractState> doStateActions() override {
        return std::make_unique<MockStateNoStateChange>(MockStateNoStateChange(cardChecker, logger));
    }
};
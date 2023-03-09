#pragma once
#include <gtest/gtest.h>
#include "Indicator.hpp"
#include "mocks/MockStates.hpp"

TEST(InterlockState_test, STATE_UPDATES) {
    Indicator indicator(IndicatorColors::WHITE);
    std::unique_ptr<AbstractState> currentState;
    currentState = std::make_unique<MockStateChangeState>(MockStateChangeState());
    currentState = currentState->run(indicator);
    ASSERT_EQ(indicator._currentColor, IndicatorColors::GREEN);
    currentState = currentState->run(indicator);
    ASSERT_EQ(indicator._currentColor, IndicatorColors::RED);
    currentState = currentState->run(indicator);
    ASSERT_EQ(indicator._currentColor, IndicatorColors::RED);
}

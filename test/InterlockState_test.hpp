#pragma once
#include <gtest/gtest.h>
#include "Indicator.hpp"
#include "mocks/MockStates.hpp"

#define SUITE_NAME INDICATOR_TEST

TEST(SUITE_NAME, STATE_UPDATES) {
    Logger logger;
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

TEST(SUITE_NAME, EXTERNAL_HTTP_STATE_UPDATES) {
    
}

#pragma once

#include "UnitTesting/Testeable.h"
#include "UnitTesting/UnitTestingTypes.h"

#pragma region ITesteable
#define CLASS_A_TESTS_ENUM(DO) \
    DO(LTT_ADD_SIMPLE) \
    DO(LTT_ADD_MULTIPLE) \
    DO(LTT_ADD_ARRAY) \
    DO(LTT_REMOVE_SIMPLE) \
    DO(LTT_REMOVE_MULTIPLE) \
    DO(LTT_REMOVE_ARRAY)

MAKE_LOGGABLE_ENUM(CLASS_A_TESTS_ENUM, LightTagTest)
#pragma endregion

class LightTagsTests : public ITesteable<LightTagTest>
{
	bool RunTest(LightTagTest TestToRun) override;
};


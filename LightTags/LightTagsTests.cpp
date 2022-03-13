#include "LightTagsTests.h"
#include "LightTags.h"

bool LightTagsTests::RunTest(LightTagTest TestToRun)
{
	LightTagContainer tags = {};


	switch (TestToRun)
	{
		case LightTagTest::LTT_ADD_SIMPLE:
		{
			tags.add_tag(AT_STATE_B);
			return tags.has_all_tags(AT_STATE_A);
		}
// 		case ETesteableExampleTests::TEST_HEALTH:
// 		{
// 			return Health != 0;
// 		}
// 		case ETesteableExampleTests::TEST_MOVEMENT:
// 		{
// 			const int MaxSpeed = 10;
// 			const bool bExceedMaxSpeed = Movement > MaxSpeed;
// 
// 			if (bExceedMaxSpeed)
// 			{
// 				LastErrorStr.append("Exceed Max Speed!");
// 				return false;
// 			}
// 
// 			return true;
// 		}	
// 		case ETesteableExampleTests::TEST_SCORE:
// 		{
// 			return Score == 500;
// 		}

		default:
			break;
	}

	return true;
}


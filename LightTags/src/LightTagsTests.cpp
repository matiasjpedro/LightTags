#include "LightTagsTests.h"
#include "LightTags.h"

bool LightTagsTests::RunTest(LightTagTest TestToRun)
{
	LightTagContainer tags = {};


	switch (TestToRun)
	{
		case LightTagTest::LTT_ADD_SIMPLE:
		{
			tags.add(AT_STATE_Z);
			tags.add(AT_ACTION_Z);
			tags.add(AT_EXTRA_Z);
			return tags.has_all(AT_STATE_Z, AT_ACTION_Z, AT_EXTRA_Z);
		}
		case LightTagTest::LTT_ADD_MULTIPLE:
		{
			tags.add(AT_ACTION_A, AT_ACTION_Z);
			return tags.has_all(AT_ACTION_A, AT_ACTION_Z);
		}
		case LightTagTest::LTT_ADD_ARRAY:
		{
			constexpr LightTagHandle tags_arr[] = { AT_STATE_A, AT_STATE_Z };
			tags.add(tags_arr, COUNT_OF(tags_arr));
			return tags.has_all(tags_arr, COUNT_OF(tags_arr));
		}
		case LightTagTest::LTT_REMOVE_SIMPLE:
		{
			tags.add(AT_STATE_B);
			tags.remove(AT_STATE_B);
			return !tags.has_any(AT_STATE_B);
		}
		case LightTagTest::LTT_REMOVE_MULTIPLE:
		{
			tags.add(AT_STATE_A, AT_STATE_Z, AT_ACTION_A);
			tags.remove(AT_STATE_A, AT_STATE_Z, AT_ACTION_A);
			return !tags.has_any(AT_STATE_A, AT_STATE_Z, AT_ACTION_A);
		}
		case LightTagTest::LTT_REMOVE_ARRAY:
		{
			constexpr LightTagHandle tags_arr[] = { AT_ACTION_Z, AT_EXTRA_A };
			tags.add(tags_arr, COUNT_OF(tags_arr));
			tags.remove(tags_arr, COUNT_OF(tags_arr));
			return !tags.has_any(AT_ACTION_Z, AT_EXTRA_A);
		}

		default:
			break;
	}

	return true;
}


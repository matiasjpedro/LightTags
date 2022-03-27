#include "LightTagsTests.h"
#include "LightTags.h"

enum LightTag {
	LT_STATE_A = 0,
	LT_STATE_B,
	LT_STATE_C,
	LT_STATE_Z = 63,

	LT_ACTION_A = 64,
	LT_ACTION_B,
	LT_ACTION_C,
	LT_ACTION_Z = 127,

	LT_EXTRA_A = 128,
	LT_EXTRA_B,
	LT_EXTRA_C,
	LT_EXTRA_Z = 191,

	LT_COUNT
};

bool LightTagsTests::RunTest(LightTagTest TestToRun)
{
	TagContainer<LT_COUNT> tags = {};

	switch (TestToRun)
	{
		case LightTagTest::LTT_ADD_SIMPLE:
		{
			tags.add(LT_STATE_Z);
			tags.add(LT_ACTION_Z);
			tags.add(LT_EXTRA_Z);
			return tags.has_all(LT_STATE_Z, LT_ACTION_Z, LT_EXTRA_Z);
		}
		case LightTagTest::LTT_ADD_MULTIPLE:
		{
			tags.add(LT_ACTION_A, LT_ACTION_Z);
			return tags.has_all(LT_ACTION_A, LT_ACTION_Z);
		}
		case LightTagTest::LTT_ADD_ARRAY:
		{
			constexpr TagHandle tags_arr[] = { LT_STATE_A, LT_STATE_Z };
			tags.add(tags_arr, COUNT_OF(tags_arr));
			return tags.has_all(tags_arr, COUNT_OF(tags_arr));
		}
		case LightTagTest::LTT_REMOVE_SIMPLE:
		{
			tags.add(LT_STATE_B);
			tags.remove(LT_STATE_B);
			return !tags.has_any(LT_STATE_B);
		}
		case LightTagTest::LTT_REMOVE_MULTIPLE:
		{
			tags.add(LT_STATE_A, LT_STATE_Z, LT_ACTION_A);
			tags.remove(LT_STATE_A, LT_STATE_Z, LT_ACTION_A);
			return !tags.has_any(LT_STATE_A, LT_STATE_Z, LT_ACTION_A);
		}
		case LightTagTest::LTT_REMOVE_ARRAY:
		{
			constexpr TagHandle tags_arr[] = { LT_ACTION_Z, LT_EXTRA_A };
			tags.add(tags_arr, COUNT_OF(tags_arr));
			tags.remove(tags_arr, COUNT_OF(tags_arr));
			return !tags.has_any(LT_ACTION_Z, LT_EXTRA_A);
		}

		default:
			break;
	}

	return true;
}


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

bool LightTagsTests::RunTest(LightTagTest TestToRun){

	using namespace tags_utils;
	uint64_t my_tags[get_array_size(LT_COUNT)] = {};
	

	switch (TestToRun)
	{
		case LightTagTest::LTT_ADD_SIMPLE:
		{
			set(my_tags, LT_STATE_Z);
			return has(my_tags, LT_STATE_Z);
		}
		case LightTagTest::LTT_REMOVE_SIMPLE:
		{
			set(my_tags, LT_STATE_Z);
			remove(my_tags, LT_STATE_Z);
			return !has(my_tags, LT_STATE_Z);
		}
		case LightTagTest::LTT_ADD_MULTIPLE:
		{
			constexpr TagHandle tags_arr[] = { LT_STATE_A, LT_STATE_Z };
			set(my_tags, tags_arr, COUNT_OF(tags_arr));
			return has_all(my_tags, tags_arr, COUNT_OF(tags_arr));
		}
		case LightTagTest::LTT_REMOVE_MULTIPLE:
		{
			constexpr TagHandle tags_arr[] = { LT_STATE_A, LT_STATE_Z };
			set(my_tags, tags_arr, COUNT_OF(tags_arr));
			remove(my_tags, tags_arr, COUNT_OF(tags_arr));
			return !has_any(my_tags, tags_arr, COUNT_OF(tags_arr));
		}

		default:
			break;
	}

	return true;
}


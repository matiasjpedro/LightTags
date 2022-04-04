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

#if USE_TEMPLATE_VERSION
		case LightTagTest::LTT_ADD_SIMPLE:
		{
			set(my_tags, LT_STATE_Z);
			set(my_tags, LT_ACTION_Z);
			set(my_tags, LT_EXTRA_Z);
			return has_all(my_tags, LT_STATE_Z, LT_ACTION_Z, LT_EXTRA_Z);
		}
		case LightTagTest::LTT_ADD_MULTIPLE:
		{
			set(my_tags, LT_ACTION_A, LT_ACTION_Z);
			return has_all(my_tags, LT_ACTION_A, LT_ACTION_Z);
		}
		case LightTagTest::LTT_ADD_ARRAY:
		{
			constexpr TagHandle tags_arr[] = { LT_STATE_A, LT_STATE_Z };
			set(my_tags, tags_arr, COUNT_OF(tags_arr));
			return has_all(my_tags, tags_arr, COUNT_OF(tags_arr));
		}
		case LightTagTest::LTT_REMOVE_SIMPLE:
		{
			set(my_tags, LT_STATE_B);
			remove(my_tags, LT_STATE_B);
			return !has_any(my_tags, LT_STATE_B);
		}
		case LightTagTest::LTT_REMOVE_MULTIPLE:
		{
			set(my_tags, LT_STATE_A, LT_STATE_Z, LT_ACTION_A);
			remove(my_tags, LT_STATE_A, LT_STATE_Z, LT_ACTION_A);
			return !has_any(my_tags, LT_STATE_A, LT_STATE_Z, LT_ACTION_A);
		}
		case LightTagTest::LTT_REMOVE_ARRAY:
		{
			constexpr TagHandle tags_arr[] = { LT_ACTION_Z, LT_EXTRA_A };
			set(my_tags, tags_arr, COUNT_OF(tags_arr));
			remove(my_tags, tags_arr, COUNT_OF(tags_arr));
			return !has_any(my_tags, LT_ACTION_Z, LT_EXTRA_A);
		}

#else
		case LightTagTest::LTT_ADD_SIMPLE:
		{
			TAG_SET(my_tags, LT_STATE_Z);
			TAG_SET(my_tags, LT_ACTION_Z);
			TAG_SET(my_tags, LT_EXTRA_Z);
			return TAG_HAS_ALL_THREE(my_tags, LT_STATE_Z, LT_ACTION_Z, LT_EXTRA_Z);
		}
		case LightTagTest::LTT_ADD_MULTIPLE:
		{
			TAG_SET_TWO(my_tags, LT_ACTION_A, LT_ACTION_Z);
			return TAG_HAS_ALL_TWO(my_tags, LT_ACTION_A, LT_ACTION_Z);
		}
		case LightTagTest::LTT_ADD_ARRAY:
		{
			constexpr TagHandle tags_arr[] = { LT_STATE_A, LT_STATE_Z };
			TAG_SET_ARR(my_tags, tags_arr);
			return TAG_HAS_ALL_ARR(my_tags, tags_arr);
		}
		case LightTagTest::LTT_REMOVE_SIMPLE:
		{
			TAG_SET(my_tags, LT_STATE_B);
			TAG_REMOVE(my_tags, LT_STATE_B);
			return !TAG_HAS_ANY(my_tags, LT_STATE_B);
		}
		case LightTagTest::LTT_REMOVE_MULTIPLE:
		{
			TAG_SET_THREE(my_tags, LT_STATE_A, LT_STATE_Z, LT_ACTION_A);
			TAG_REMOVE_THREE(my_tags, LT_STATE_A, LT_STATE_Z, LT_ACTION_A);
			return !TAG_HAS_ANY_THREE(my_tags, LT_STATE_A, LT_STATE_Z, LT_ACTION_A);
		}
		case LightTagTest::LTT_REMOVE_ARRAY:
		{
			constexpr TagHandle tags_arr[] = { LT_ACTION_Z, LT_EXTRA_A };
			TAG_SET_ARR(my_tags, tags_arr);
			TAG_REMOVE_ARR(my_tags, tags_arr);
			return !TAG_HAS_ANY_TWO(my_tags, LT_ACTION_Z, LT_EXTRA_A);
		}

#endif

		default:
			break;
	}

	return true;
}


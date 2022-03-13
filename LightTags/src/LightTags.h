#pragma once

#include <stdint.h>
#include <initializer_list>

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

enum LightTag {
	AT_STATE_A = 0,
	AT_STATE_B,
	AT_STATE_C,
	AT_STATE_Z = 63,

	AT_ACTION_A = 64,
	AT_ACTION_B,
	AT_ACTION_C,
	AT_ACTION_Z = 127,

	AT_EXTRA_A = 128,
	AT_EXTRA_B,
	AT_EXTRA_C,
	AT_EXTRA_Z = 191,

	AT_COUNT
};

static constexpr unsigned tags_arr_num = 1 + ((AT_COUNT - 1) / 64);

struct LightTagHandle {
	unsigned tag_array_index;
	uint64_t tag_bit;

	constexpr LightTagHandle(const LightTag tag) : tag_array_index(get_tag_array_index(tag)), tag_bit(get_tag_bit(tag, tag_array_index)){}

	constexpr unsigned get_tag_array_index(const LightTag tag) {
		return tag / 64;
	}

	constexpr unsigned get_tag_bit(const LightTag tag, const unsigned tag_array_index) {
		const unsigned bit = tag - (tag_array_index * 64);
		return bit;
	}
};

struct LightTagContainer {
	
	LightTagContainer()
	{
		for (unsigned i = 0; i < tags_arr_num; i++)
		{
			tags[i] = { 0 };
		}
	}

	template <typename... Tags>
	void add(Tags... tags) {
		for (const auto tag : { tags... }) {
			add_internal(tag);
		}
	}

	bool add(const LightTagHandle* arr, size_t size) {
		bool retval = false;
		for (unsigned i = 0; i < size; i++) {
			add_internal(arr[i]);
		}

		return retval;
	}

	template <typename... Tags>
	void remove(Tags... tags) {
		for (const auto tag : { tags... }) {
			remove_internal(tag);
		}
	}

	bool remove(const LightTagHandle* arr, size_t size) {
		bool retval = false;
		for (unsigned i = 0; i < size; i++) {
			remove_internal(arr[i]);
		}

		return retval;
	}

	template <typename... Tags>
	bool has_all(Tags... tags) {
		bool retval = true;
		for (const auto tag : { tags... }) {
			retval &= is_set_internal(tag);
		}

		return retval;
	}

	bool has_all(const LightTagHandle* arr, size_t size) {
		bool retval = true;
		for (unsigned i = 0; i < size; i++) {
			retval &= is_set_internal(arr[i]);
		}

		return retval;
	}

	template <typename... Tags>
	bool has_any(Tags... tags) {
		bool retval = false;
		for (const auto tag : { tags... }) {
			retval |= is_set_internal(tag);
		}

		return retval;
	}

	bool has_any(const LightTagHandle* arr, size_t size) {
		bool retval = false;
		for (unsigned i = 0; i < size; i++) {
			retval |= is_set_internal(arr[i]); 
		}

		return retval;
	}

	private:

	uint64_t tags[tags_arr_num];

	void add_internal(const LightTagHandle tag_handle) {
		tags[tag_handle.tag_array_index] |= 1ULL << tag_handle.tag_bit;
	}

	void remove_internal(const LightTagHandle tag_handle) {
		tags[tag_handle.tag_array_index] &= ~(1ULL << tag_handle.tag_bit);
	}

	bool is_set_internal(const LightTagHandle tag_handle) {
		return (tags[tag_handle.tag_array_index] >> tag_handle.tag_bit) & 1U;
	}
};

#pragma once

#include <stdint.h>
#include <initializer_list>
#include <stdarg.h>

#define USE_TEMPLATE_VERSION 0
#define COUNT_OF(x) (unsigned)((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

struct TagHandle {
	unsigned tag_array_index;
	uint64_t tag_bit;

#if DEVELOPMENT 
	unsigned raw_tag;
#endif

	constexpr TagHandle(const unsigned tag) : 
		tag_array_index(get_tag_array_index(tag)), 
		tag_bit(get_tag_bit(tag, tag_array_index))
#if DEVELOPMENT
		, raw_tag(tag)
#endif
	{}

	constexpr unsigned get_tag_array_index(const unsigned tag) {
		return tag / 64;
	}

	constexpr unsigned get_tag_bit(const unsigned tag, const unsigned tag_array_index) {
		const unsigned bit = tag - (tag_array_index * 64);
		return bit;
	}
};

namespace tags_utils {

	constexpr unsigned get_array_size(unsigned max) {
		unsigned size = max / 64;
		if ((size * 64) < max)
			size++;
		return size;
	}

	void set_single(uint64_t source_arr[], const TagHandle tag_handle) {
		source_arr[tag_handle.tag_array_index] |= (1ULL << tag_handle.tag_bit);
	}

	void remove_single(uint64_t source_arr[], const TagHandle tag_handle) {
		source_arr[tag_handle.tag_array_index] &= ~(1ULL << tag_handle.tag_bit);
	}

	bool is_set_single(uint64_t source_arr[], const TagHandle tag_handle) {
		return source_arr[tag_handle.tag_array_index] & (1ULL << tag_handle.tag_bit);
	}

	void set(uint64_t source_arr[], const TagHandle* arr, unsigned arr_size) {
		for (unsigned i = 0; i < arr_size; i++) {
			set_single(source_arr, arr[i]);
		}
	}

	void remove(uint64_t source_arr[], const TagHandle* arr, unsigned arr_size) {
		for (unsigned i = 0; i < arr_size; i++) {
			remove_single(source_arr, arr[i]);
		}
	}

	bool has_all(uint64_t source_arr[], const TagHandle* arr, unsigned arr_size) {
		bool retval = true;
		for (unsigned i = 0; i < arr_size; i++) {
			retval &= is_set_single(source_arr, arr[i]);
		}

		return retval;
	}

	bool has_any(uint64_t source_arr[], const TagHandle* arr, unsigned arr_size) {
		bool retval = false;
		for (unsigned i = 0; i < arr_size; i++) {
			retval |= is_set_single(source_arr, arr[i]);
		}

		return retval;
	}

#if USE_TEMPLATE_VERSION

	template <typename... Tags>
	void set(uint64_t source_arr[], Tags... tags) {
		for (const auto tag : { tags... }) {
			set_single(source_arr, tag);
		}
	}

	template <typename... Tags>
	void remove(uint64_t source_arr[], Tags... tags) {
		for (const auto tag : { tags... }) {
			remove_single(source_arr, tag);
		}
	}

	template <typename... Tags>
	bool has_all(uint64_t source_arr[], Tags... tags) {
		bool retval = true;
		for (const auto tag : { tags... }) {
			retval &= is_set_single(source_arr, tag);
		}

		return retval;
	}

	template <typename... Tags>
	bool has_any(uint64_t source_arr[], Tags... tags) {
		bool retval = false;
		for (const auto tag : { tags... }) {
			retval |= is_set_single(source_arr, tag);
		}

		return retval;
	}

#else 

	void set(uint64_t arr[], int count, ...) {
		va_list argp;
		va_start(argp, count);
		for (int i = 0; i < count; ++i) {
			unsigned tag = va_arg(argp, unsigned);
			set_single(arr, tag);
		}
		va_end(argp);
	}

	void remove(uint64_t arr[], int count, ...) {
		va_list argp;
		va_start(argp, count);
		for (int i = 0; i < count; ++i) {
			unsigned tag = va_arg(argp, unsigned);
			remove_single(arr, tag);
		}
		va_end(argp);
	}

	bool has_all(uint64_t arr[], int count, ...) {
		bool retval = true;
		va_list argp;
		va_start(argp, count);
		for (int i = 0; i < count; ++i) {
			unsigned tag = va_arg(argp, unsigned);
			retval &= is_set_single(arr, tag);
		}
		va_end(argp);
		return retval;
	}

	bool has_any(uint64_t arr[], int count, ...) {
		bool retval = false;
		va_list argp;
		va_start(argp, count);
		for (int i = 0; i < count; ++i) {
			unsigned tag = va_arg(argp, unsigned);
			retval |= is_set_single(arr, tag);
		}
		va_end(argp);
		return retval;
	}

#endif
}

#if !USE_TEMPLATE_VERSION


#define TAG_SET(ARR, ARG1) tags_utils::set_single(ARR, ARG1)
#define TAG_SET_TWO(ARR, ARG1, ARG2) tags_utils::set(ARR, 2, ARG1, ARG2)
#define TAG_SET_THREE(ARR, ARG1, ARG2, ARG3) tags_utils::set(ARR, 3, ARG1, ARG2, ARG3)
#define TAG_SET_FOUR(ARR, ARG1, ARG2, ARG3, ARG4) tags_utils::set(ARR, 4, ARG1, ARG2, ARG3, ARG4)
#define TAG_SET_FIVE(ARR, ARG1, ARG2, ARG3, ARG4, ARG5) tags_utils::set(ARR, 5, ARG1, ARG2, ARG3, ARG4, ARG5)
#define TAG_SET_ARR(SRC_ARR, ARR_PTR, ARR_SIZE) tags_utils::set(SRC_ARR, ARR_PTR, ARR_SIZE)

#define TAG_REMOVE(ARR, ARG1) tags_utils::remove_single(ARR, ARG1)
#define TAG_REMOVE_TWO(ARR, ARG1, ARG2) tags_utils::remove(ARR, 2, ARG1, ARG2)
#define TAG_REMOVE_THREE(ARR, ARG1, ARG2, ARG3) tags_utils::remove(ARR, 3, ARG1, ARG2, ARG3)
#define TAG_REMOVE_FOUR(ARR, ARG1, ARG2, ARG3, ARG4) tags_utils::remove(ARR, 4, ARG1, ARG2, ARG3, ARG4)
#define TAG_REMOVE_FIVE(ARR, ARG1, ARG2, ARG3, ARG4, ARG5) tags_utils::remove(ARR, 5, ARG1, ARG2, ARG3, ARG4, ARG5)
#define TAG_REMOVE_ARR(SRC_ARR, ARR_PTR, ARR_SIZE) tags_utils::remove(SRC_ARR, ARR_PTR, ARR_SIZE)

#define TAG_HAS_ALL(ARR, ARG1) tags_utils::is_set_single(ARR, ARG1)
#define TAG_HAS_ALL_TWO(ARR, ARG1, ARG2) tags_utils::has_all(ARR, 2, ARG1, ARG2)
#define TAG_HAS_ALL_THREE(ARR, ARG1, ARG2, ARG3) tags_utils::has_all(ARR, 3, ARG1, ARG2, ARG3)
#define TAG_HAS_ALL_FOUR(ARR, ARG1, ARG2, ARG3, ARG4) tags_utils::has_all(ARR, 4, ARG1, ARG2, ARG3, ARG4)
#define TAG_HAS_ALL_FIVE(ARR, ARG1, ARG2, ARG3, ARG4, ARG5) tags_utils::has_all(ARR, 5, ARG1, ARG2, ARG3, ARG4, ARG5)
#define TAG_HAS_ALL_ARR(SRC_ARR, ARR_PTR, ARR_SIZE) tags_utils::has_all(SRC_ARR, ARR_PTR, ARR_SIZE)

#define TAG_HAS_ANY(ARR, ARG1) tags_utils::is_set_single(ARR, ARG1)
#define TAG_HAS_ANY_TWO(ARR, ARG1, ARG2) tags_utils::has_any(ARR, 2, ARG1, ARG2)
#define TAG_HAS_ANY_THREE(ARR, ARG1, ARG2, ARG3) tags_utils::has_any(ARR, 3, ARG1, ARG2, ARG3)
#define TAG_HAS_ANY_FOUR(ARR, ARG1, ARG2, ARG3, ARG4) tags_utils::has_any(ARR, 4, ARG1, ARG2, ARG3, ARG4)
#define TAG_HAS_ANY_FIVE(ARR, ARG1, ARG2, ARG3, ARG4, ARG5) tags_utils::has_any(ARR, 5, ARG1, ARG2, ARG3, ARG4, ARG5)
#define TAG_HAS_ANY_ARR(SRC_ARR, ARR_PTR, ARR_SIZE) tags_utils::has_any(SRC_ARR, ARR_PTR, ARR_SIZE)

#endif

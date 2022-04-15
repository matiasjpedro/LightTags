#pragma once

#include <stdint.h>
#include <initializer_list>

#define COUNT_OF(x) (unsigned)((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

struct TagHandle {
	unsigned tag_array_index;
	uint64_t tag_bit;

	constexpr TagHandle(const unsigned tag) : 
		tag_array_index(get_tag_array_index(tag)), 
		tag_bit(get_tag_bit(tag, tag_array_index))
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


	void set(uint64_t source_arr[], const TagHandle& tag_handle) {
		source_arr[tag_handle.tag_array_index] |= (1ULL << tag_handle.tag_bit);
	}

	void set(uint64_t source_arr[], const TagHandle* arr, const unsigned arr_size) {
		for (unsigned i = 0; i < arr_size; i++) {
			const TagHandle& tag_handle = arr[i];
			source_arr[tag_handle.tag_array_index] |= (1ULL << tag_handle.tag_bit);
		}
	}

	void remove(uint64_t source_arr[], const TagHandle& tag_handle) {
		source_arr[tag_handle.tag_array_index] &= ~(1ULL << tag_handle.tag_bit);
	}

	void remove(uint64_t source_arr[], const TagHandle* arr, const unsigned arr_size) {
		for (unsigned i = 0; i < arr_size; i++) {
			const TagHandle& tag_handle = arr[i];
			source_arr[tag_handle.tag_array_index] &= ~(1ULL << tag_handle.tag_bit);
		}
	}

	bool has(uint64_t source_arr[], const TagHandle& tag_handle) {
		return (source_arr[tag_handle.tag_array_index] & (1ULL << tag_handle.tag_bit));
	}

	bool has_all(uint64_t source_arr[], const TagHandle* arr, const unsigned arr_size) {
		bool retval = true;
		for (unsigned i = 0; i < arr_size; i++) {
			const TagHandle& tag_handle = arr[i];
			retval &= !!(source_arr[tag_handle.tag_array_index] & (1ULL << tag_handle.tag_bit));
		}

		return retval;
	}

	bool has_any(uint64_t source_arr[], const TagHandle* arr, const unsigned arr_size) {
		bool retval = false;
		for (unsigned i = 0; i < arr_size; i++) {
			const TagHandle& tag_handle = arr[i];
			retval |= !!(source_arr[tag_handle.tag_array_index] & (1ULL << tag_handle.tag_bit));
		}

		return retval;
	}
}
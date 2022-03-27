#pragma once

#include <stdint.h>
#include <initializer_list>

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

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

template <size_t COUNT>
struct TagContainer {
	
	TagContainer()
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

	void add(const TagHandle* arr, size_t size) {
		for (unsigned i = 0; i < size; i++) {
			add_internal(arr[i]);
		}
	}

	template <typename... Tags>
	void remove(Tags... tags) {
		for (const auto tag : { tags... }) {
			remove_internal(tag);
		}
	}

	void remove(const TagHandle* arr, size_t size) {
		for (unsigned i = 0; i < size; i++) {
			remove_internal(arr[i]);
		}
	}

	template <typename... Tags>
	bool has_all(Tags... tags) {
		bool retval = true;
		for (const auto tag : { tags... }) {
			retval &= is_set_internal(tag);
		}

		return retval;
	}

	bool has_all(const TagHandle* arr, size_t size) {
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

	bool has_any(const TagHandle* arr, size_t size) {
		bool retval = false;
		for (unsigned i = 0; i < size; i++) {
			retval |= is_set_internal(arr[i]); 
		}

		return retval;
	}

private:

	static constexpr unsigned tags_arr_num = 1 + ((COUNT - 1) / 64);
	uint64_t tags[tags_arr_num];

	void add_internal(const TagHandle tag_handle) {
		tags[tag_handle.tag_array_index] |= 1ULL << tag_handle.tag_bit;
	}

	void remove_internal(const TagHandle tag_handle) {
		tags[tag_handle.tag_array_index] &= ~(1ULL << tag_handle.tag_bit);
	}

	bool is_set_internal(const TagHandle tag_handle) {
		return (tags[tag_handle.tag_array_index] >> tag_handle.tag_bit) & 1U;
	}
};


// TODO: non-template version / global version
// void tag_add(uint64_t arr[], const LightTagHandle tag_handle) {
// 	arr[tag_handle.tag_array_index] |= (1ULL << tag_handle.tag_bit);
// }
// 
// void tag_remove(uint64_t arr[], const LightTagHandle tag_handle) {
// 	arr[tag_handle.tag_array_index] &= ~(1ULL << tag_handle.tag_bit);
// }
// 
// int tag_has(uint64_t arr[], const LightTagHandle tag_handle) {
// 	return arr[tag_handle.tag_array_index] & (1ULL << tag_handle.tag_bit);
// }
// 
// 
// // optional varargs implementations
// #include <stdarg.h>
// void tag_set_multiple(uint64_t arr[], int count, ...) {
// 	va_list argp;
// 	va_start(argp, arr);
// 	for (int i = 0; i < count; ++i) {
// 		unsigned tag = va_arg(argp, argp, unsigned);
// 		tag_add(arr, tag);
// 	}
// 	va_end(argp);
// }
// 
// #define TAG_SET(ARR, ARG1) tag_add(ARR, ARG1)
// #define TAG_SET(ARR, ARG1, ARG2) tag_set_multiple(ARR, 2, ARG1, ARG2)
// #define TAG_SET(ARR, ARG1, ARG2, ARG3) tag_set_multiple(ARR, 3, ARG1, ARG2, ARG3)
// #define TAG_SET(ARR, ARG1, ARG2, ARG3, ARG4) tag_set_multiple(ARR, 4, ARG1, ARG2, ARG3, ARG4)
// #define TAG_SET(ARR, ARG1, ARG2, ARG3, ARG4, ARG5) tag_set_multiple(ARR, 5, ARG1, ARG2, ARG3, ARG4, ARG5)

#pragma once
namespace mylib {
	template<typename Iterator>
	int get_intersection(Iterator src_cbegin, Iterator src_cend, Iterator dest_cbegin, Iterator dest_cend, Iterator outcome_container_begin)
	{
		int count = 0;
		while (src_cbegin != src_cend) {
			Iterator _cp_dest_cbegin = dest_cbegin;
			while (_cp_dest_cbegin != dest_cend) {
				if (*_cp_dest_cbegin == *src_cbegin) {
					*outcome_container_begin++ = *src_cbegin;
					count++;
				}
				_cp_dest_cbegin++;
			}
			src_cbegin++;
		}
		return count;
	}

	template<class Iterator,class T>
	void Merge_by_order(Iterator src_cbegin, Iterator src_cend,
		Iterator dest_cbegin, Iterator dest_cend, T& container) {
		while (dest_cbegin != dest_cend&&src_cbegin != src_cend) {
			if (*src_cbegin < *dest_cbegin) {
				container.push_back(*src_cbegin);
				src_cbegin++;
			}
			else {
				container.push_back(*dest_cbegin);
				dest_cbegin++;
			}
		}
		while (dest_cbegin != dest_cend)
			container.push_back(*dest_cbegin++);
		while (src_cbegin != src_cend)
			container.push_back(*src_cbegin++);
	}
}
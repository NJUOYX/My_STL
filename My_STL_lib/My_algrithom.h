#pragma once
template<class Iterator>
int get_intersection(Iterator src_cbegin,Iterator src_cend,Iterator dest_cbegin,Iterator dest_cend,Iterator outcome_container_begin)
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
/*
	Header file for undirected_pair container
    Copyright (C) 2015  Fabian Löschner

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef UNDIRECTEDPAIR
#define UNDIRECTEDPAIR

#include <stdexcept>

/**
 * @brief Undirected pair
 *
 * Pair whose comparison operators does not differentiate between pair(a,b) and pair(b,a).
 * Suitable as the edge id type for an undirected graph
 */
template <typename T>
class undirected_pair
{
public:
	T a;	/*!< Element a of the undirected pair */
	T b;	/*!< Element b of the undirected pair */

	//! Constructs an empty undirected pair
	undirected_pair() = default;
	//! Constructs an undirected pair with the specified objects as data
	undirected_pair(T a_in, T b_in) : a(a_in), b(b_in) {}

	//! Returns a reference to the other data element if compare is the same as one of the elements in the undirected pair
	T& other_element(const T& compare)
	{
		if(compare == a) return b;
		if(compare == b) return a;
        throw std::invalid_argument("");
	}
	//! Returns a const reference to the other data element if compare is the same as one of the elements in the undirected pair
    const T& other_element(const T& compare) const { if(compare == a) return b; if(compare == b) return a; throw std::invalid_argument(""); }

	//! Returns a reference to the smaller of the two elements in the undirected pair or element a
	T& smaller_element()
	{
		if(b < a) return b;
		return a;
	}
	//! Returns a const reference to the smaller of the two elements in the undirected pair or element a
	const T& smaller_element() const { if(b < a) return b; return a; }

	//! Returns a reference to the bigger of the two elements in the undirected pair or element b
	T& bigger_element()
	{
		if(a > b) return a;
		return b;
	}
	//! Returns a const reference to the bigger of the two elements in the undirected pair or element b
	const T& bigger_element() const { if(a > b) return a; return b; }

	//! Returns whether the two undirected pairs contain the same data elements
	inline bool operator==(const undirected_pair& rhs) const
	{
		return ((a == rhs.a) && (b == rhs.b))
			|| ((a == rhs.b) && (b == rhs.a));
	}
	//! Returns whether the two pairs contain different data elements
	inline bool operator!=(const undirected_pair& rhs) const {return !(*this == rhs);}

	//! Strict weak ordering for undirected pairs by the smallest element in the pairs
	inline bool operator<(const undirected_pair& rhs) const
	{
		if(smaller_element() < rhs.smaller_element()) return true;
		if(rhs.smaller_element() < smaller_element()) return false;
		if(bigger_element() < rhs.bigger_element()) return true;
		return false;
	}
	inline bool operator> (const undirected_pair& rhs) const {return rhs < *this;}
	inline bool operator<=(const undirected_pair& rhs) const {return !(*this > rhs);}
	inline bool operator>=(const undirected_pair& rhs) const {return !(*this < rhs);}
};

#endif //UNDIRECTEDPAIR
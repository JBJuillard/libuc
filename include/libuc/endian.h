/*
** endian.h
**
** Header file for endian subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/02 by Juillard Jean-Baptiste
** Updated: 2018/04/14 by Juillard Jean-Baptiste
**
** This file is a part free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 3, or
** (at your option) any later version.
**
** There is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; see the file LICENSE.  If not, write to
** the Free Software Foundation, Inc., 51 Franklin Street, Fifth
** Floor, Boston, MA 02110-1301, USA.
*/

#ifndef ENDIAN_H
# define ENDIAN_H						1

# ifndef __BYTE_ORDER
#  define _ENDIAN_H						ENDIAN_H
#  include <bits/endian.h>
# endif

# include <libuc/stdint.h>
# include <libuc/byteswap.h>

/*
** Definitions for byte order, according to significance of bytes,
** from low addresses to high addresses.  The value is what you get by
** putting '4' in the most significant byte, '3' in the second most
** significant byte, '2' in the second least significant byte, and '1'
** in the least significant byte, and then writing down one digit for
** each byte, starting with the byte at the lowest address at the left,
** and proceeding to the byte with the highest address at the right.
**
** __BIG_ENDIAN					4321	byte-swapped big-endian (ABCD)
** __LITTLE_ENDIAN				1234	byte-swapped little-endian (DCBA)
** __WORD_BIG_ENDIAN			2143	word-swapped big-endian (CDAB)
** __WORD_LITTLE_ENDIAN			3412	word-swapped little-endian (BADC)
*/
# define __BIG_ENDIAN					4321
# define __LITTLE_ENDIAN				1234
# define __WORD_BIG_ENDIAN				2143
# define __WORD_LITTLE_ENDIAN			3412

/*
** Definitions for FPU endianness
*/
# ifndef __FLOAT_WORD_ORDER
#  define __FLOAT_WORD_ORDER			__BYTE_ORDER
# endif

# ifdef __USE_MISC
#  define BYTE_ORDER					__BYTE_ORDER
#  define BIG_ENDIAN					__BIG_ENDIAN
#  define LITTLE_ENDIAN					__LITTLE_ENDIAN
#  define WORD_BIG_ENDIAN				__WORD_BIG_ENDIAN
#  define WORD_LITTLE_ENDIAN			__WORD_LITTLE_ENDIAN
#  define PDP_ENDIAN					__WORD_LITTLE_ENDIAN
# endif

# if	(__BYTE_ORDER == __BIG_ENDIAN)					/* 4321 */
#  define htobe16(x)					(x)
#  define htole16(x)					bswap_16(x)
#  define be16toh(x)					(x)
#  define le16toh(x)					bswap_16(x)
#  define htobe32(x)					(x)
#  define htole32(x)					bswap_32(x)
#  define be32toh(x)					(x)
#  define le32toh(x)					bswap_32(x)
#  define htobe64(x)					(x)
#  define htole64(x)					bswap_64(x)
#  define be64toh(x)					(x)
#  define le64toh(x)					bswap_64(x)
# elif	(__BYTE_ORDER == __LITTLE_ENDIAN)				/* 1234 */
#  define htobe16(x)					bswap_16(x)
#  define htole16(x)					(x)
#  define be16toh(x)					bswap_16(x)
#  define le16toh(x)					(x)
#  define htobe32(x)					bswap_32(x)
#  define htole32(x)					(x)
#  define be32toh(x)					bswap_32(x)
#  define le32toh(x)					(x)
#  define htobe64(x)					bswap_64(x)
#  define htole64(x)					(x)
#  define be64toh(x)					bswap_64(x)
#  define le64toh(x)					(x)
# elif	(__BYTE_ORDER == __WORD_BIG_ENDIAN)				/* 2143 */
#  define htobe16(x)					(x)
#  error "__WORD_BIG_ENDIAN not implemented."
# elif	(__BYTE_ORDER == __WORD_LITTLE_ENDIAN)			/* 3412 */
#  error "__WORD_LITTLE_ENDIAN not implemented."
# else
#  error "Unvalid value for __BYTE_ORDER macro."
# endif

#endif

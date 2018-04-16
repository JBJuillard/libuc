/*
** byteswap.h
**
** Header file for byteswap subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/02 by Juillard Jean-Baptiste
** Updated: 2018/04/02 by Juillard Jean-Baptiste
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

#ifndef BYTESWAP_H
# define BYTESWAP_H						1

# define __c_bswap_16(x)				((unsigned short int)				\
											((((x) & 0xff00) >> 8)			\
												| (((x) & 0x00ff) << 8)))

# define __c_bswap_32(x)				((unsigned int)							\
											((((x) & 0xff000000) >> 24)			\
												| (((x) & 0x00ff0000) >> 8)		\
												| (((x) & 0x0000ff00) << 8)		\
												| (((x) & 0x000000ff) << 24)))

# define __c_bswap_64(x)				((unsigned long long int)							\
											((((x) & 0xff00000000000000ull) >> 56)			\
												| (((x) & 0x00ff000000000000ull) >> 40)		\
												| (((x) & 0x0000ff0000000000ull) >> 24)		\
												| (((x) & 0x000000ff00000000ull) >> 8)		\
												| (((x) & 0x00000000ff000000ull) << 8)		\
												| (((x) & 0x0000000000ff0000ull) << 24)		\
												| (((x) & 0x000000000000ff00ull) << 40)		\
												| (((x) & 0x00000000000000ffull) << 56)))

# define __asm_bswap_16(x)				({	unsigned short int __v, __x = (x);	\
											__asm__(	"rorw $8, %w0"			\
														: "=r"(__v)				\
														: "0"(__x)				\
														: );					\
											__v;								\
										})

# if	(__WORDSIZE == 64)
#  define __asm_bswap_32(x)				({	unsigned int __v, __x = (x);	\
											__asm__(	"bswap %d0"			\
														: "=r"(__v)			\
														: "0"(__x)			\
														: );				\
											__v;							\
										})
#  define __asm_bswap_64(x)				({	unsigned long long int __v, __x = (x);	\
											__asm__(	"bswap %q0"					\
														: "=r"(__v)					\
														: "0"(__x)					\
														: );						\
											__v;									\
										})
# else /* (__WORDSIZE != 64) */
#  define __asm_bswap_32(x)				({	unsigned int __v, __x = (x);	\
											__asm__(	"rorw $8, %w0\n"	\
														"rorl $16, %d0\n"	\
														"rorw $8, %w0"		\
														: "=r"(__v)			\
														: "0"(__x)			\
														: "cc");			\
											__v;							\
										})
#  define __asm_bswap_64(x)				({	auto union									\
											{											\
												uint64_t	__ll;						\
												uint32_t	__l[2];						\
											}				__v, __x;					\
											__x.__ll = (x);								\
											__v.__l[0] = __asm_bswap_32(__x.__l[1]);	\
											__v.__l[1] = __asm_bswap_32(__x.__l[0]);	\
											__v.__ll;									\
										})
# endif

# define bswap_16(x)					__asm_bswap_16(x)
# define bswap_32(x)					__asm_bswap_32(x)
# define bswap_64(x)					__asm_bswap_64(x)

#endif

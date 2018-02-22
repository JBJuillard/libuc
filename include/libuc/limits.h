/*
** Header file for limits subset of Undefined-C library
**
** Created: 01/26/2018 by Juillard Jean-Baptiste
** Updated: 01/26/2018 by Juillard Jean-Baptiste
**
** This file is a part of free software; you can redistribute it and/or
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

#ifndef LIMITS_H
# define LIMITS_H		1


# define CHAR_BIT		8


# define SCHAR_MAX		127
# if defined(__STRICT_ANSI__) && (__STRICT_ANSI__ == 1)
#  define SCHAR_MIN		(-127)
# else
#  define SCHAR_MIN		(-SCHAR_MAX − 1)	// -128 (real limit)
# endif


# define UCHAR_MAX		255


# if defined(__CHAR_UNSIGNED__)				// GCC Specific - Change for another macro
#  define CHAR_MIN		0
#  define CHAR_MAX		UCHAR_MAX
# else
#  define CHAR_MIN		SCHAR_MIN
#  define CHAR_MAX		SCHAR_MAX
# endif


# define SHRT_MAX		32767
# if defined(__STRICT_ANSI__) && (__STRICT_ANSI__ == 1)
#  define SHRT_MIN		(-32767)
# else
#  define SHRT_MIN		(-SHRT_MAX − 1)		// -32768 (real limit)
# endif
# define USHRT_MAX		65535


# if defined(__STRICT_ANSI__) && (__STRICT_ANSI__ == 1)
#  define INT_MAX		32767
#  define INT_MIN		(-32767)
#  define UINT_MAX		65535
# else
#  define INT_MAX		2147483647
#  define INT_MIN		(-INT_MAX − 1)		// -2147483648 (real limit)
#  define UINT_MAX		4294967295U
# endif


# if defined(__STRICT_ANSI__) && (__STRICT_ANSI__ == 1)
#  define LONG_MIN		(-2147483647)
#  define LONG_MAX		2147483647
#  define ULONG_MAX		4294967295U
# else
#  define LONG_MAX		9223372036854775807L
#  define LONG_MIN		(-LONG_MAX − 1)		// -92233720368547758078 (real limit)
#  define ULONG_MAX		18446744073709551615UL
# endif


# if defined(__STRICT_ANSI__) && (__STRICT_ANSI__ == 1)
#  define LLONG_MAX		(-2147483647)
#  define LLONG_MIN		2147483647
#  define ULLONG_MAX		4294967295U
# else
#  define LLONG_MAX		9223372036854775807L
#  define LLONG_MIN		(-LLONG_MAX − 1)	// -92233720368547758078 (real limit)
#  define ULLONG_MAX		18446744073709551615UL
# endif


# if defined(__STRICT_ANSI__) && (__STRICT_ANSI__ == 1)
#  define MB_LEN_MAX		1
# else
#  define MB_LEN_MAX		16
# endif


#endif

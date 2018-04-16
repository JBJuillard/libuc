/*
** ieee.h
**
** Header file for ieee subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/21 by Juillard Jean-Baptiste
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

#ifndef IEEE_H
# define IEEE_H							1

# include <libuc/endian.h>

# if		!defined(__BYTE_ORDER)
#  error	"__BYTE_ORDER not defined."
# elif		!defined(__FLOAT_WORD_ORDER)
#  error	"__FLOAT_WORD_ORDER not defined."
# endif

# define IEEE754_FLOAT_BIAS				0x7F			/* Bias = 127 */
# define IEEE754_DOUBLE_BIAS			0x3FF			/* Bias = 1023 */
# define IEEE854_LDOUBLE_BIAS			0x3FFF			/* Bias = 16383 */

/* IEEE 754 single-precision format. */
struct									ieee754_float_s
{
# if	__BYTE_ORDER == __BIG_ENDIAN	/* Big endian. */
	unsigned int						negative:1;
	unsigned int						exponent:8;
	unsigned int						mantissa:23;
# elif	__BYTE_ORDER == __LITTLE_ENDIAN	/* Little endian. */
	unsigned int						mantissa:23;
	unsigned int						exponent:8;
	unsigned int						negative:1;
# endif
};

/* NaN IEEE 754 single-precision format. */
struct									ieee754_float_nan_s
{
# if	__BYTE_ORDER == __BIG_ENDIAN	/* Big endian. */
	unsigned int						negative:1;
	unsigned int						exponent:8;
	unsigned int						quiet_nan:1;
	unsigned int						mantissa:22;
# elif	__BYTE_ORDER == __LITTLE_ENDIAN	/* Little endian. */
	unsigned int						mantissa:22;
	unsigned int						quiet_nan:1;
	unsigned int						exponent:8;
	unsigned int						negative:1;
#endif
};

/* IEEE 754 single-precision union. */
typedef union							ieee754_float_u
{
	float								f;
	struct ieee754_float_s				ieee;
	struct ieee754_float_nan_s			ieee_nan;
}										ieee754_float_t;

/* IEEE 754 double-precision format. */
struct									ieee754_double_s
{
# if	__BYTE_ORDER == __BIG_ENDIAN	/* Big endian. */
	unsigned int						negative:1;
	unsigned int						exponent:11;
	unsigned int						mantissa0:20;
	unsigned int						mantissa1:32;
# elif	__BYTE_ORDER == __LITTLE_ENDIAN	/* Little endian. */
#  if	__FLOAT_WORD_ORDER == __BIG_ENDIAN
	unsigned int						mantissa0:20;
	unsigned int						exponent:11;
	unsigned int						negative:1;
	unsigned int						mantissa1:32;
#  else
	unsigned int						mantissa1:32;
	unsigned int						mantissa0:20;
	unsigned int						exponent:11;
	unsigned int						negative:1;
#  endif
# endif
};

/* NaN IEEE 754 double-precision format. */
struct									ieee754_double_nan_s
{
# if	__BYTE_ORDER == __BIG_ENDIAN	/* Big endian. */
	unsigned int						negative:1;
	unsigned int						exponent:11;
	unsigned int						quiet_nan:1;
	unsigned int						mantissa0:19;
	unsigned int						mantissa1:32;
# elif	__BYTE_ORDER == __LITTLE_ENDIAN	/* Little endian. */
#  if	__FLOAT_WORD_ORDER == __BIG_ENDIAN
	unsigned int						mantissa0:19;
	unsigned int						quiet_nan:1;
	unsigned int						exponent:11;
	unsigned int						negative:1;
	unsigned int						mantissa1:32;
#  else
	unsigned int						mantissa1:32;
	unsigned int						mantissa0:19;
	unsigned int						quiet_nan:1;
	unsigned int						exponent:11;
	unsigned int						negative:1;
#  endif
# endif
};

/* IEEE 754 double-precision union. */
typedef union							ieee754_double_u
{
	double								d;
	struct ieee754_double_t				ieee;
	struct ieee754_double_nan_t			ieee_nan;
}										ieee754_double_t;

/* IEEE 854 double-extended-precision format. */
struct									ieee_854_long_double_s
{
# if	__BYTE_ORDER == __BIG_ENDIAN	/* Big endian. */
	unsigned int						negative:1;
	unsigned int						exponent:15;
	unsigned int						empty:16;
	unsigned int						mantissa0:32;
	unsigned int						mantissa1:32;
# elif	__BYTE_ORDER == __LITTLE_ENDIAN	/* Little endian. */
#  if	__FLOAT_WORD_ORDER == __BIG_ENDIAN
	unsigned int						exponent:15;
	unsigned int						negative:1;
	unsigned int						empty:16;
	unsigned int						mantissa0:32;
	unsigned int						mantissa1:32;
#  else
	unsigned int						mantissa1:32;
	unsigned int						mantissa0:32;
	unsigned int						exponent:15;
	unsigned int						negative:1;
	unsigned int						empty:16;
#  endif
# endif
};

/* NaN IEEE 854 double-extended-precision format.  */
struct									ieee_854_long_double_nan_s
{
# if	__BYTE_ORDER == __BIG_ENDIAN	/* Big endian. */
	unsigned int						negative:1;
	unsigned int						exponent:15;
	unsigned int						empty:16;
	unsigned int						one:1;
	unsigned int						quiet_nan:1;
	unsigned int						mantissa0:30;
	unsigned int						mantissa1:32;
# elif	__BYTE_ORDER == __LITTLE_ENDIAN	/* Little endian. */
#  if	__FLOAT_WORD_ORDER == __BIG_ENDIAN
	unsigned int						exponent:15;
	unsigned int						negative:1;
	unsigned int						empty:16;
	unsigned int						mantissa0:30;
	unsigned int						quiet_nan:1;
	unsigned int						one:1;
	unsigned int						mantissa1:32;
#  else
	unsigned int						mantissa1:32;
	unsigned int						mantissa0:30;
	unsigned int						quiet_nan:1;
	unsigned int						one:1;
	unsigned int						exponent:15;
	unsigned int						negative:1;
	unsigned int						empty:16;
#  endif
# endif
};

/* IEEE 854 double-extended-precision union.  */
typedef union							ieee854_long_double_u
{
	long double							ld;
	struct ieee_854_long_double_s		ieee;
	struct ieee_854_long_double_nan_s	ieee_nan;
}										ieee854_long_double_t;

#endif

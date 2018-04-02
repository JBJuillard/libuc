/*
** math.h
**
** Header file for math subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/31 by Juillard Jean-Baptiste
** Updated: 2018/03/31 by Juillard Jean-Baptiste
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

#ifndef MATH_H
# define MATH_H						1

# include <float.h>

/*
** Type used by float_t and double_t
**
** FLT_EVAL_METHOD		float_t					double_t
** ===================================================================
** -1				    indeterminable			indeterminable
** 0					float					double
** 1					double					double
** 2					long double				long double
** other				implementation-defined	implementation-defined
*/
# if 	defined(FLT_EVAL_METHOD) && (FLT_EVAL_METHOD == 0)
typedef float		float_t;
typedef double		double_t;
# elif 	defined(FLT_EVAL_METHOD) && (FLT_EVAL_METHOD == 1)
typedef double		float_t;
typedef double		double_t;
# elif 	defined(FLT_EVAL_METHOD) && (FLT_EVAL_METHOD == 2)
typedef long double	float_t;
typedef long double	double_t;
# endif

/*
int fpclassify(real-floating x);
int isfinite(real-floating x);
int isgreater(real-floating x, real-floating y);
int isgreaterequal(real-floating x, real-floating y);
int isinf(real-floating x);
int isless(real-floating x, real-floating y);
int islessequal(real-floating x, real-floating y);
int islessgreater(real-floating x, real-floating y);
int isnan(real-floating x);
int isnormal(real-floating x);
int isunordered(real-floating x, real-floating y);
int signbit(real-floating x);
*/

# if	defined(__USE_MISC) || defined(__USE_XOPEN)
#  define M_E						2.7182818284590452354	/* e */
#  define M_LOG2E					1.4426950408889634074	/* log_2 e */
#  define M_LOG10E					0.43429448190325182765	/* log_10 e */
#  define M_LN2						0.69314718055994530942	/* log_e 2 */
#  define M_LN10					2.30258509299404568402	/* log_e 10 */
#  define M_PI						3.14159265358979323846	/* pi */
#  define M_PI_2					1.57079632679489661923	/* pi / 2 */
#  define M_PI_4					0.78539816339744830962	/* pi / 4 */
#  define M_1_PI					0.31830988618379067154	/* 1 / pi */
#  define M_2_PI					0.63661977236758134308	/* 2 / pi */
#  define M_2_SQRTPI				1.12837916709551257390	/* 2 / sqrt(pi) */
#  define M_SQRT2					1.41421356237309504880	/* sqrt(2) */
#  define M_SQRT1_2					0.70710678118654752440	/* 1 / sqrt(2) */
#  if	defined(__USE_GNU)
#   define M_El						2.718281828459045235360287471352662498L	/* e */
#   define M_LOG2El					1.442695040888963407359924681001892137L	/* log_2 e */
#   define M_LOG10El				0.434294481903251827651128918916605082L	/* log_10 e */
#   define M_LN2l					0.693147180559945309417232121458176568L	/* log_e 2 */
#   define M_LN10l					2.302585092994045684017991454684364208L	/* log_e 10 */
#   define M_PIl					3.141592653589793238462643383279502884L	/* pi */
#   define M_PI_2l					1.570796326794896619231321691639751442L	/* pi / 2 */
#   define M_PI_4l					0.785398163397448309615660845819875721L	/* pi / 4 */
#   define M_1_PIl					0.318309886183790671537767526745028724L	/* 1 / pi */
#   define M_2_PIl					0.636619772367581343075535053490057448L	/* 2 / pi */
#   define M_2_SQRTPIl				1.128379167095512573896158903121545172L	/* 2 / sqrt(pi) */
#   define M_SQRT2l					1.414213562373095048801688724209698079L	/* sqrt(2) */
#   define M_SQRT1_2l				0.707106781186547524400844362104849039L	/* 1 / sqrt(2) */
#  endif
# endif

#endif

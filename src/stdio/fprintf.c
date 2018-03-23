/*
** fprintf.c
**
** fprintf function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/02/24 by Juillard Jean-Baptiste
** Updated: 2018/03/14 by Juillard Jean-Baptiste
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

#define ARGUMENT_MAX			4096
#define CONVERTION_MAX			4095

#define TYPE_MASK				0c000FFFFFU
#define TYPE_CHAR				0x00000001U		/* type signed signed char */
#define TYPE_SHRT				0x00000002U		/* type signed signed short */
#define TYPE_INT				0x00000004U		/* type signed signed int */
#define TYPE_LONG				0x00000008U		/* type signed signed long */
#define TYPE_LLONG				0x00000010U		/* type signed signed long long */
#define TYPE_UCHAR				0x00000020U		/* type unsigned char */
#define TYPE_USHRT				0x00000040U		/* type unsigned short */
#define TYPE_UINT				0x00000080U		/* type unsigned int */
#define TYPE_ULONG				0x00000100U		/* type unsigned long */
#define TYPE_ULLONG				0x00000200U		/* type unsigned long long */
#define TYPE_FLOAT				0x00000400U		/* type float */
#define TYPE_DOUBLE				0x00000800U		/* type double */
#define TYPE_LDOUBLE			0x00001000U		/* type long double */
#define TYPE_AZT				0x00002000U		/* type array zero terminated */
#define TYPE_PTR				0x00004000U		/* type void pointer */
#define TYPE_NPTR				0x00008000U		/* type integer pointer (n) */
#define TYPE_ERROR				0x00010000U		/* type error (m) */

#define NOTATION_MASK			0xFFF00000U

#include <libuc/limits.h>
#include <stdlib.h>
#include <libuc/stdlst.h>

typedef struct		arg_s
{
	unsigned int	type;
	unsigned int	position;
	void			*value;
}					arg_t;

static char		*fprintf_get_int(va_list arg)
{
	register int	n;
	register size_t	i;
	register char	t[16];
	register char	*s;

	if (!arg)
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	errno = 0;
	n = va_arg(arg, int);
	i ^= i;
	while (i < 16)
		t[i++] = '\0';
	i = 14;
	while (n)
	{
		c = n % b;
}

static arg_t	fprintf_parse_arg(const char *fmt)
{
	register char	*tmp;
	register size_t	offset;

	if (!fmt)
	{
		errno = EINVAL;
		return ((arg_t *)(NULL));
	}
	errno = 0;
	if ((tmp = (char *)malloc(CONVERSION_MAX * sizeof(char))) == (char *)(NULL))
		return ((arg_t *)(NULL));
	offset ^= offset;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			if (*(fmt + 1) == '%')
			{
				*(tmp + offset++) = *fmt;
				fmt += 2;
			}
			else if (offset)
			{
				*(tmp + offset) = '\0';
				;
				offset ^= offset;
			}
		}
		else
			*(tmp + offset++) = *(fmt++);
	}
}

int				fprintf(int fd, const char *fmt, ...)
{
	register void		**arg;
	register va_list	aptr;
	register sclst		*str;

	if (fd < 0 || fd > USHRT_MAX || !fmt)
	{
		errno = EINVAL;
		return (0);
	}
	errno ^= errno;
	if ((arg = (void **)calloc(ARGUMENT_MAX, sizeof(void *))) == (void **)(NULL))
		return (0);
	str ^= str;
	va_start(aptr, fmt);
}

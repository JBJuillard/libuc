/*
** ut_ltostr.c
**
** Unit tests for ltostr function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/26 by Juillard Jean-Baptiste
** Updated: 2018/03/28 by Juillard Jean-Baptiste
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

#include <libuc/errno.h>
#include <libuc/stdlib.h>

typedef struct		test_s
{
	long int		i;
	char			*ret;
	int				error;
	
}					test_t;

int	ut_ltostr_interface(int N)
{
	int		i;
	int		err;
	char	*sret;
	size_t	offset;
	test_t	tdat[3] = {	{0, "0", 0},
						{-1, "-1", 0},
						{1, "1", 0} };

	err = 0xff;
	i = 0;
	N = N;
	while (i < 3)
	{
		errno = 0;
		sret = ltostr((tdat[i]).i, 10, 0);
		if ((!((tdat[i]).ret) && sret)
			|| errno != (tdat[i]).error)
			return (err);
		if (sret)
		{
			err--;
			offset ^= offset;
			while (*(sret + offset) || *(((tdat[i]).ret) + offset))
			{
				if (*(sret + offset) != *(((tdat[i]).ret) + offset))
					return (err);
				offset++;
			}
		}
		i++;
		err--;
	}
	return (0);
}

int	ut_ltostr_validity(int N)
{
	long int	i;
	char		*s;

	i = 0;
	while (i < N)
	{
		errno = 0;
		s = (char *)(NULL);
		if (!(s = ((char *)ltostr(i, 10, 0)))
			|| errno)
			return (i + 1);
		i++;
	}
	return (0);
}

int	ut_ltostr_memchk(int N)
{
	return (ut_ltostr_validity(N));
}

int	ut_ltostr_timeout(int N)
{
	return (ut_ltostr_validity(N));
}

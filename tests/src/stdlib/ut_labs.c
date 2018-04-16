/*
** ut_labs.c
**
** Unit tests for labs function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/23 by Juillard Jean-Baptiste
** Updated: 2018/04/04 by Juillard Jean-Baptiste
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
#include <libuc/limits.h>

typedef struct		err_s
{
	long long int	n;
	long long int	ret;
	int				err;
}					err_t;

int	ut_labs_interface(int N)
{
	long int	i;
	int			error;
	err_t		tdat[2] = {	{LONG_MIN, LONG_MIN, ERANGE},
							{LONG_MAX, LONG_MAX, 0}};

	error = 0xFF;
	i = 0;
	N =N;
	while (i < 2)
	{
		errno = 0;
		if ((long long int)labs((long int)((tdat[i]).n)) != (tdat[i]).ret
			|| errno != (tdat[i]).err)
			return (error);
		i++;
		error--;
	}
	return (0);
}

int	ut_labs_validity(int N)
{
	unsigned long int	i;

	i = 0;
	N = N;
	while (i <= LONG_MAX)
		if (i && labs(-i) != (long)(i))
			return ((int)(-i));
	if (labs(0))
		return (INT_MIN);
	i = 0;
	while ((long)(i) <= LONG_MAX)
		if (i && labs(i) != (long)(i))
			return ((int)(i));
	return (0);
}

int	ut_labs_memchk(int N)
{
	unsigned int	i;

	i = 0;
	while (i < (unsigned int)(N))
		labs(i++);
	return (0);
}

int	ut_labs_timeout(int N)
{
	return (ut_labs_memchk(N));
}

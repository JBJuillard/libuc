/*
** Header file for stdlib subset of Undefined-C library
**
** Created: 02/24/2018 by Juillard Jean-Baptiste
** Updated: 02/25/2018 by Juillard Jean-Baptiste
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

#ifndef STDLIB_H
# define STDLIB_H		1


# include		<libuc/stddef.h>


# define		EXIT_FAILURE			1
# define		EXIT_SUCCESS			0

# define		RAND_MAX			32767
# define		MB_CUR_MAX			((size_t)(4))


int			atoi(const char *nptr);
long			atol(const char *nptr);
long long		atoll(const char *nptr);
//double			atof(const char *nptr);
long int		strtol(const char *nptr, char **endptr, int base);
long long int		strtoll(const char *nptr, char **endptr, int base);
unsigned long int	strtoul(const char *nptr, char **endptr, int base);
unsigned long long int	strtoull(const char *nptr, char **endptr, int base);
//double			strtod(const char *nptr, char **endptr);
//float			strtof(const char *nptr, char **endptr);
//long double		strtold(const char *nptr, char **endptr);


int			rand(void);
//int			rand_r(unsigned int *seedp);
void			srand(unsigned int seed);


void			*bsearch(const void *key, const void *base, size_t nmemb,
					size_t size, int (*compar)(const void *, const void *));
void			qsort(void *base, size_t nmemb, size_t size,
				int (*compar)(const void *, const void *));


#endif

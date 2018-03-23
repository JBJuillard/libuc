/*
** stdlib.h
**
** Header file for stdlib subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/02/24 by Juillard Jean-Baptiste
** Updated: 2018/03/21 by Juillard Jean-Baptiste
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

#ifndef STDLIB_H
# define STDLIB_H		1

/*
** Define NULL macro, size_t and wchar_t types.
*/
# include <libuc/stddef.h>
/*
** Define the following macro:
**		WEXITSTATUS, WIFEXITED, WIFSIGNALED, WIFSTOPPED
**		WNOHANG, WSTOPSIG, WTERMSIG, WUNTRACED.
*/
# include <sys/wait.h>				/* Dev: A modifier après implantation du fichier d'en-tête <sys/wait.h> */


# define EXIT_FAILURE	1
# define EXIT_SUCCESS	0

# define RAND_MAX		32767
# define MB_CUR_MAX		((size_t)(4))

typedef struct			div_s
{
	int					quot;
	int					rem;
}						div_t;

typedef struct			ldiv_s
{
	long int			quot;
	long int			rem;
}						ldiv_t;

typedef struct			lldiv_s
{
	long long int		quot;
	long long int		rem;
}						lldiv_t;

int						abs(int n);
long int				labs(long int n);
# if	defined(_ISOC99_SOURCE) || (_POSIX_C_SOURCE >= 200112L)
long long int			llabs(long long int n);
# endif

div_t					div(int numer, int denom);
ldiv_t					ldiv(long numer, long denom);
lldiv_t					lldiv(long long numer, long long denom);

int						atoi(const char *nptr);
long int				atol(const char *nptr);
long long int			atoll(const char *nptr);
//double				atof(const char *nptr);

long int				strtol(const char *nptr, char **endptr, int base);
long long int			strtoll(const char *nptr, char **endptr, int base);
unsigned long int		strtoul(const char *nptr, char **endptr, int base);
unsigned long long int	strtoull(const char *nptr, char **endptr, int base);
//float					strtof(const char *nptr, char **endptr);
//double				strtod(const char *nptr, char **endptr);
//long double			strtold(const char *nptr, char **endptr);

char					*itoa(int n);
char					*utoa(unsigned int n);
char					*ltoa(long int n);
char					*ultoa(unsigned long int n);
char					*lltoa(long long int n);
char					*ulltoa(unsigned long long int n);
//char					*ftoa(float n);
//char					*dtoa(double n);
//char					*ldtoa(long double n);

char					*itostr(int n, int base, int upcasse);
char					*utostr(unsigned int n, int base, int upcasse);
char					*ltostr(long n, int base, int upcasse);
char					*ultostr(unsigned long n, int base, int upcasse);
char					*lltostr(long long n, int base, int upcasse);
char					*ulltostr(unsigned long long n, int base, int upcasse);
//char					*ftostr(float f, int base, int upcasse);
//char					*dtostr(double f, int base, int upcasse);
//char					*ldtostr(long double f, int base, int upcasse);

int						rand(void);
//int					rand_r(unsigned int *seedp);
void					srand(unsigned int seed);

//double					drand48(void);
//double					erand48(unsigned short xsubi[3]);
//long int				lrand48(void);
//long int				nrand48(unsigned short xsubi[3]);
//long int				mrand48(void);
//long int				jrand48(unsigned short xsubi[3]);
//void					srand48(long int seedval);
//unsigned short			*seed48(unsigned short seed16v[3]);
//void					lcong48(unsigned short param[7]);


void					*bsearch(const void *key, const void *base,
									size_t nmemb, size_t size,
									int (*compar)(const void *, const void *));
void					*bsearch_s(const void *key, const void *base,
									size_t nmemb, size_t size,
									int (*compar)(const void *, const void *));
void					qsort(void *base, size_t nmemb, size_t size,
								int (*compar)(const void *, const void *));
void					qsort_s(void *base, size_t nmemb, size_t size,
								int (*compar)(const void *, const void *));


#endif

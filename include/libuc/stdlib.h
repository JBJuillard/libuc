/*
** stdlib.h
**
** Header file for stdlib subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/02/24 by Juillard Jean-Baptiste
** Updated: 2018/03/27 by Juillard Jean-Baptiste
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
# include <sys/wait.h>

/*
** Define exit status code
*/
# define EXIT_FAILURE	1
# define EXIT_SUCCESS	0

/*
** Define RAND_MAX for rand(3) and srand(3)
*/
# define RAND_MAX		32767

/*
** Deifne maximum size of multi-bytes characters
*/
# define MB_CUR_MAX		((size_t)(4))


/*
** abs(3), labs(3), llabs(3).
*/
extern int abs(int n);
extern long int labs(long int n);
extern long long int llabs(long long int n);


/*
** div_t, ldiv_t, lldiv_t,
*/
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
/*
** div(3), ldiv(3), lldiv(3).
*/
extern div_t div(int numer, int denom);
extern ldiv_t ldiv(long int numer, long int denom);
extern lldiv_t lldiv(long long int numer, long long int denom);


/*
** atoi(3), atol(3), atoll(3),
** atou(3), atoul(3), atoull(3),
** atof(3).
*/
extern int atoi(const char *nptr);
extern unsigned int atou(const char *nptr);
extern long int atol(const char *nptr);
extern unsigned long int atoul(const char *nptr);
extern long long int atoll(const char *nptr);
extern unsigned long long int atoull(const char *nptr);
//extern double atof(const char *nptr);


/*
** itoa(3), utoa(3), ltoa(3),
** ultoa(3), lltoa(3), ulltoa(3),
** ftoa(3), dtoa(3), ldtoa(3).
*/
extern char *itoa(int n);
extern char *utoa(unsigned int n);
extern char *ltoa(long int n);
extern char *ultoa(unsigned long int n);
extern char *lltoa(long long int n);
extern char *ulltoa(unsigned long long int n);
//extern char *ftoa(float n);
//extern char *dtoa(double n);
//extern char *ldtoa(long double n);


/*
** strtol(3), strtoll(3), strtoul(3),
** strtoull(3), strtof(3), strtod(3),
** strtold(3).
*/
extern int strtoi(const char *nptr, char **endptr, int base);
extern long int strtol(const char *nptr, char **endptr, int base);
extern long long int strtoll(const char *nptr, char **endptr, int base);
extern unsigned int strtou(const char *nptr, char **endptr, int base);
extern unsigned long int strtoul(const char *nptr, char **endptr, int base);
extern unsigned long long int strtoull(const char *nptr, char **endptr, int base);
//extern float strtof(const char *nptr, char **endptr);
//extern double strtod(const char *nptr, char **endptr);
//extern long double strtold(const char *nptr, char **endptr);


/*
** itostr(3), utostr(3), ltostr(3),
** ultostr(3), lltostr(3), ulltostr(3),
** ftostr(3), dtostr(3), ldtostr(3).
*/
extern char *itostr(int n, int base, int upcasse);
extern char *utostr(unsigned int n, int base, int upcasse);
extern char *ltostr(long n, int base, int upcasse);
extern char *ultostr(unsigned long n, int base, int upcasse);
extern char *lltostr(long long n, int base, int upcasse);
extern char *ulltostr(unsigned long long n, int base, int upcasse);
//extern char *ftostr(float f, int base, int upcasse);
//extern char *dtostr(double f, int base, int upcasse);
//extern char *ldtostr(long double f, int base, int upcasse);


/*
** rand(3), srand(3), rand_r(3)
*/
extern int rand(void);
//extern int rand_r(unsigned int *seedp);
extern void srand(unsigned int seed);


/*
** seed48(3), srand48(3), lcong48(3),
** drand48(3), erand48(3), lrand48(3),
** nrand48(3), mrand48(3), jrand48(3).
*/
//extern void srand48(long int seedval);
//extern unsigned short *seed48(unsigned short seed16v[3]);
//extern void lcong48(unsigned short param[7]);
//extern double drand48(void);
//extern double erand48(unsigned short xsubi[3]);
//extern long int lrand48(void);
//extern long int nrand48(unsigned short xsubi[3]);
//extern long int mrand48(void);
//extern long int jrand48(unsigned short xsubi[3]);


extern void *bsearch(const void *key, const void *base, size_t nmemb,
					size_t size, int (*compar)(const void *, const void *));
extern void *bsearch_s(const void *key, const void *base, size_t nmemb,
					size_t size, int (*compar)(const void *, const void *));
extern void qsort(void *base, size_t nmemb, size_t size,
					int (*compar)(const void *, const void *));
extern void qsort_s(void *base, size_t nmemb, size_t size,
					int (*compar)(const void *, const void *));


extern void	*malloc(size_t size);
extern void	*calloc(size_t nmemb, size_t size);
extern void	free(void *ptr);
extern void	*realloc(void *ptr, size_t size);


#endif

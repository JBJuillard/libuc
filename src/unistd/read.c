/*
** read.c
**
** read function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/25 by Juillard Jean-Baptiste
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

#include <libuc/errno.h>
#include <libuc/stdint.h>
#include <sys/types.h>
#include <sys/syscall.h>

#if     defined(__i386__)
# define SYSCALL_ASSEMBLY		"int $0x80\n"
# define SYSCALL_OUTPUT(r)		"=a"(r)
# define SYSCALL_INPUT(f,b,c)	"0"(SYS_read), "b"(f), "c"(b), "d"(c)
#else
# define SYSCALL_ASSEMBLY		"movq %1, %%rax\n\t" \
								"movq %2, %%rdi\n\t" \
								"movq %3, %%rsi\n\t" \
								"movq %4, %%rdx\n\t" \
								"syscall\n"
# define SYSCALL_OUTPUT(r)		"=a"(r)
# define SYSCALL_INPUT(f,b,c)	"I"(SYS_read), "m"(f), "m"(b), "m"(c)
#endif

ssize_t read(int fd, void *buf, size_t count)
{
	register ssize_t    ret;

	if (fd < 0 || !buf || !count || count > SIZE_MAX)
	{
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	__asm__ __volatile__(	SYSCALL_ASSEMBLY
							: SYSCALL_OUTPUT(ret)
							: SYSCALL_INPUT(fd, buf, count)
							: );
	return (ret);
}

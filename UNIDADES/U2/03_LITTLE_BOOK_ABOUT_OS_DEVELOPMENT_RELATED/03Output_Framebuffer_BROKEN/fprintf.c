/* fprintf.c - _fdoprnt */

/*#include <xinu.h>*/
#include "kernel.h"
#include "conf.h"
#include "tty.h"
#include "uart.h"
#include "semaphore.h"
#include "process.h"
#include "queue.h"
#include "prototypes.h"
#include "stdarg.h"

extern void _fdoprnt(char *, va_list, int (*)(did32, char), int);

/*------------------------------------------------------------------------
 *  fprintf  -  Print a formatted message on specified device (file).
 *				Return 0 if the output was printed successfully,
 *				-1 if an error occurred.
 *------------------------------------------------------------------------
 */
int		fprintf(
		  int		dev,			/* device to write to				*/
		  char		*fmt,			/* format string					*/
		  ...
		)
{
    va_list ap;
    int putc(did32, char);

    va_start(ap, fmt);
    _fdoprnt(fmt, ap, putc, dev);
    va_end(ap);

    return 0;
}

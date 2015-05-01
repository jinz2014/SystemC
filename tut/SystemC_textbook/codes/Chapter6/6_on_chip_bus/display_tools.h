#ifndef _DISPLAY_TOOLS_H
#define _DISPLAY_TOOLS_H
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
char transfer_status_str[4][30]={
	"Transfer Ok!","Transfer Error",
		"Transfer wait","Address out of range"
}; 
int sb_fprintf(FILE *fp, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  int ret = 0;
  do {
    errno = 0;
    ret = vfprintf(fp, fmt, ap);
  } while (errno == EINTR);
  return ret;
}
#endif
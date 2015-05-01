/*******************************************************
By Chenxi,2003.5.24
All rights reserverd
This file is copied from System 2.01 library. it is
used to display debug output 
*******************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>

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

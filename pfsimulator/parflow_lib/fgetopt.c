/*
 * Copyright (c) 1987, 1993, 1994
 *      The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the University of
 *      California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "fgetopt.h"

#include <string.h>
#include <stdio.h>

int opterr = 1,                 /* if error message should be printed */
    optind = 1,                 /* index into parent argv vector */
    optopt,                     /* character checked for validity */
    optreset;                   /* reset getopt */
char    *optarg;                /* argument associated with option */

#define BADCH   (int)'?'
#define BADARG  (int)':'
#define EMSG    ""

/*
 * getopt --
 *      Parse argc/argv argument vector.
 */
int getopt(int nargc, char * const nargv[], const char *ostr)
{
  static char *place = EMSG;              /* option letter processing */
  const char *oli;                              /* option letter list index */

  if (optreset || !*place)                /* update scanning pointer */
  {
    optreset = 0;
    if (optind >= nargc || *(place = nargv[optind]) != '-')
    {
      place = EMSG;
      return(-1);
    }
    if (place[1] && *++place == '-')        /* found "--" */
    {
      ++optind;
      place = EMSG;
      return(-1);
    }
  }                                       /* option letter okay? */
  if ((optopt = (int)*place++) == (int)':' ||
      !(oli = strchr(ostr, optopt)))
  {
    /*
     * if the user didn't specify '-' as an option,
     * assume it means -1.
     */
    if (optopt == (int)'-')
      return(-1);
    if (!*place)
      ++optind;
    if (opterr && *ostr != ':')
      (void)printf("illegal option -- %c\n", optopt);
    return(BADCH);
  }
  if (*++oli != ':')                      /* don't need argument */
  {
    optarg = NULL;
    if (!*place)
      ++optind;
  }
  else                                    /* need an argument */
  {
    if (*place)                     /* no white space */
      optarg = place;
    else if (nargc <= ++optind)     /* no arg */
    {
      place = EMSG;
      if (*ostr == ':')
        return(BADARG);
      if (opterr)
        (void)printf("option requires an argument -- %c\n", optopt);
      return(BADCH);
    }
    else                            /* white space */
      optarg = nargv[optind];
    place = EMSG;
    ++optind;
  }
  return(optopt);                         /* dump back option letter */
}

@mattypiper
mattypiper commented on Jan 15, 2014

I think you need to add extern char *optarg; in getopt.h as well to get that portion of the getopt interface to work.
@Marraz
Marraz commented on Jun 17, 2016

Actually, according to how http: //pubs.opengroup.org/onlinepubs/9699919799/functions/getopt.html describe the functionality, the header should look like this, perhaps optreset not but I guess it doesn't hurt to have it there:
ifndef GETOPT_H
define GETOPT_H

extern int opterr,   /* if error message should be printed /
                      * optind, / index into parent argv vector /
                      * optopt, / character checked for validity /
                      * optreset; / reset getopt /
                      * extern char *optarg; / argument associated with option */

int getopt(int nargc, char * const nargv[], const char *ostr);
endif
@billkotsias
billkotsias commented on May 24, 2017

Exactly what Marraz says !
@netskink
netskink commented on Aug 9, 2017

#ifndef GETOPT_H

#define GETOPT_H

extern int opterr;              /* if error message should be printed */
extern int optind;              /* index into parent argv vector */
extern int optopt;              /* character checked for validity */
extern int optreset;    /* reset getopt  */
extern char *optarg;    /* argument associated with option */

int getopt(int nargc, char * const nargv[], const char *ostr);

#endif

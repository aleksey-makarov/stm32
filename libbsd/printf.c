/*  $NetBSD: subr_prf.c,v 1.124.4.1 2009/02/02 19:47:47 snj Exp $   */

/*-
 * Copyright (c) 1986, 1988, 1991, 1993
 *  The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
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
 *
 *  @(#)subr_prf.c  8.4 (Berkeley) 5/4/95
 */

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define NBBY 8
#define __UNCONST(a) ((void *)(unsigned long)(const void *)(a))

#define BUFSIZE     (sizeof(int64_t) * NBBY / 3 + 2)

/*
 * macros for converting digits to letters and vice versa
 */
#define to_digit(c) ((c) - '0')
#define is_digit(c) ((unsigned)to_digit(c) <= 9)
#define to_char(n)  ((n) + '0')

/*
 * flags used during conversion.
 */
#define ALT     0x001       /* alternate form */
#define HEXPREFIX   0x002       /* add 0x or 0X prefix */
#define LADJUST     0x004       /* left adjustment */
#define LONGDBL     0x008       /* long double; unimplemented */
#define LONGINT     0x010       /* long integer */
#define QUADINT     0x020       /* quad integer */
#define SHORTINT    0x040       /* short integer */
#define MAXINT      0x080       /* intmax_t */
#define PTRINT      0x100       /* intptr_t */
#define SIZEINT     0x200       /* size_t */
#define ZEROPAD     0x400       /* zero (as opposed to blank) pad */
#define FPT     0x800       /* Floating point number */

/*
 * To extend shorts properly, we need both signed and unsigned
 * argument extraction methods.
 */
#define SARG() \
    (flags&MAXINT ? va_arg(ap, intmax_t) : \
        flags&PTRINT ? va_arg(ap, intptr_t) : \
        flags&SIZEINT ? va_arg(ap, long) : /* XXX */ \
        flags&QUADINT ? va_arg(ap, int64_t) : \
        flags&LONGINT ? va_arg(ap, long) : \
        flags&SHORTINT ? (long)(short)va_arg(ap, int) : \
        (long)va_arg(ap, int))
#define UARG() \
    (flags&MAXINT ? va_arg(ap, uintmax_t) : \
        flags&PTRINT ? va_arg(ap, uintptr_t) : \
        flags&SIZEINT ? va_arg(ap, size_t) : \
        flags&QUADINT ? va_arg(ap, uint64_t) : \
        flags&LONGINT ? va_arg(ap, unsigned long) : \
        flags&SHORTINT ? (unsigned long)(unsigned short)va_arg(ap, int) : \
        (unsigned long)va_arg(ap, unsigned int))

#define PUTCHAR(c) putchar(c)

static const char HEXDIGITS[] = "0123456789ABCDEF";
static const char hexdigits[] = "0123456789abcdef";

int
vprintf(const char *fmt, va_list ap)
{
    int ch;         /* character from fmt */
    int n;          /* handy integer (short term usage) */
    char *cp;       /* handy char pointer (short term usage) */
    int flags;      /* flags as above */
    int ret;        /* return value accumulator */
    int width;      /* width from format (%8d), or 0 */
    int prec;       /* precision from format (%.3d), or -1 */
    char sign;      /* sign prefix (' ', '+', '-', or \0) */

    uint64_t _uquad;    /* integer arguments %[diouxX] */
    enum { OCT, DEC, HEX } base;/* base for [diouxX] conversion */
    int dprec;      /* a copy of prec if [diouxX], 0 otherwise */
    int realsz;     /* field size expanded by dprec */
    int size;       /* size of converted field or string */
    const char *xdigs;  /* digits for [xX] conversion */
    char bf[BUFSIZE]; /* space for %c, %[diouxX] */

    cp = NULL;  /* XXX: shutup gcc */
    size = 0;   /* XXX: shutup gcc */
    ret = 0;
    xdigs = NULL;   /* XXX: shut up gcc warning */

    /*
     * Scan the format for conversions (`%' character).
     */
    for (;;) {
        while (*fmt != '%' && *fmt) {
            ret++;
            PUTCHAR(*fmt++);
        }
        if (*fmt == 0)
            goto done;

        fmt++;      /* skip over '%' */

        flags = 0;
        dprec = 0;
        width = 0;
        prec = -1;
        sign = '\0';

rflag:      ch = *fmt++;
reswitch:   switch (ch) {
        case ' ':
            /*
             * ``If the space and + flags both appear, the space
             * flag will be ignored.''
             *  -- ANSI X3J11
             */
            if (!sign)
                sign = ' ';
            goto rflag;
        case '#':
            flags |= ALT;
            goto rflag;
        case '*':
            /*
             * ``A negative field width argument is taken as a
             * - flag followed by a positive field width.''
             *  -- ANSI X3J11
             * They don't exclude field widths read from args.
             */
            if ((width = va_arg(ap, int)) >= 0)
                goto rflag;
            width = -width;
            /* FALLTHROUGH */
        case '-':
            flags |= LADJUST;
            goto rflag;
        case '+':
            sign = '+';
            goto rflag;
        case '.':
            if ((ch = *fmt++) == '*') {
                n = va_arg(ap, int);
                prec = n < 0 ? -1 : n;
                goto rflag;
            }
            n = 0;
            while (is_digit(ch)) {
                n = 10 * n + to_digit(ch);
                ch = *fmt++;
            }
            prec = n < 0 ? -1 : n;
            goto reswitch;
        case '0':
            /*
             * ``Note that 0 is taken as a flag, not as the
             * beginning of a field width.''
             *  -- ANSI X3J11
             */
            flags |= ZEROPAD;
            goto rflag;
        case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            n = 0;
            do {
                n = 10 * n + to_digit(ch);
                ch = *fmt++;
            } while (is_digit(ch));
            width = n;
            goto reswitch;
        case 'h':
            flags |= SHORTINT;
            goto rflag;
        case 'j':
            flags |= MAXINT;
            goto rflag;
        case 'l':
            if (*fmt == 'l') {
                fmt++;
                flags |= QUADINT;
            } else {
                flags |= LONGINT;
            }
            goto rflag;
        case 'q':
            flags |= QUADINT;
            goto rflag;
        case 't':
            flags |= PTRINT;
            goto rflag;
        case 'z':
            flags |= SIZEINT;
            goto rflag;
        case 'c':
            *(cp = bf) = va_arg(ap, int);
            size = 1;
            sign = '\0';
            break;
        case 'D':
            flags |= LONGINT;
            /*FALLTHROUGH*/
        case 'd':
        case 'i':
            _uquad = SARG();
            if ((int64_t)_uquad < 0) {
                _uquad = -_uquad;
                sign = '-';
            }
            base = DEC;
            goto number;
        case 'n':
            if (flags & MAXINT)
                *va_arg(ap, intmax_t *) = ret;
            else if (flags & PTRINT)
                *va_arg(ap, intptr_t *) = ret;
            else if (flags & SIZEINT)
                *va_arg(ap, long *) = ret;
            else if (flags & QUADINT)
                *va_arg(ap, int64_t *) = ret;
            else if (flags & LONGINT)
                *va_arg(ap, long *) = ret;
            else if (flags & SHORTINT)
                *va_arg(ap, short *) = ret;
            else
                *va_arg(ap, int *) = ret;
            continue;   /* no output */
        case 'O':
            flags |= LONGINT;
            /*FALLTHROUGH*/
        case 'o':
            _uquad = UARG();
            base = OCT;
            goto nosign;
        case 'p':
            /*
             * ``The argument shall be a pointer to void.  The
             * value of the pointer is converted to a sequence
             * of printable characters, in an implementation-
             * defined manner.''
             *  -- ANSI X3J11
             */
            /* NOSTRICT */
            _uquad = (unsigned long)va_arg(ap, void *);
            base = HEX;
            xdigs = hexdigits;
            flags |= HEXPREFIX;
            ch = 'x';
            goto nosign;
        case 's':
            if ((cp = va_arg(ap, char *)) == NULL)
                /*XXXUNCONST*/
                cp = __UNCONST("(null)");
            if (prec >= 0) {
                /*
                 * can't use strlen; can only look for the
                 * NUL in the first `prec' characters, and
                 * strlen() will go further.
                 */
                char *p = memchr(cp, 0, prec);

                if (p != NULL) {
                    size = p - cp;
                    if (size > prec)
                        size = prec;
                } else
                    size = prec;
            } else
                size = strlen(cp);
            sign = '\0';
            break;
        case 'U':
            flags |= LONGINT;
            /*FALLTHROUGH*/
        case 'u':
            _uquad = UARG();
            base = DEC;
            goto nosign;
        case 'X':
            xdigs = HEXDIGITS;
            goto hex;
        case 'x':
            xdigs = hexdigits;
hex:            _uquad = UARG();
            base = HEX;
            /* leading 0x/X only if non-zero */
            if (flags & ALT && _uquad != 0)
                flags |= HEXPREFIX;

            /* unsigned conversions */
nosign:         sign = '\0';
            /*
             * ``... diouXx conversions ... if a precision is
             * specified, the 0 flag will be ignored.''
             *  -- ANSI X3J11
             */
number:         if ((dprec = prec) >= 0)
                flags &= ~ZEROPAD;

            /*
             * ``The result of converting a zero value with an
             * explicit precision of zero is no characters.''
             *  -- ANSI X3J11
             */
            cp = bf + BUFSIZE;
            if (_uquad != 0 || prec != 0) {
                /*
                 * Unsigned mod is hard, and unsigned mod
                 * by a constant is easier than that by
                 * a variable; hence this switch.
                 */
                switch (base) {
                case OCT:
                    do {
                        *--cp = to_char(_uquad & 7);
                        _uquad >>= 3;
                    } while (_uquad);
                    /* handle octal leading 0 */
                    if (flags & ALT && *cp != '0')
                        *--cp = '0';
                    break;

                case DEC:
                    /* many numbers are 1 digit */
                    while (_uquad >= 10) {
                        *--cp = to_char(_uquad % 10);
                        _uquad /= 10;
                    }
                    *--cp = to_char(_uquad);
                    break;

                case HEX:
                    do {
                        *--cp = xdigs[_uquad & 15];
                        _uquad >>= 4;
                    } while (_uquad);
                    break;

                default:
                    /*XXXUNCONST*/
                    cp = __UNCONST("bug in kprintf: bad base");
                    size = strlen(cp);
                    goto skipsize;
                }
            }
            size = bf + BUFSIZE - cp;
        skipsize:
            break;
        default:    /* "%?" prints ?, unless ? is NUL */
            if (ch == '\0')
                goto done;
            /* pretend it was %c with argument ch */
            cp = bf;
            *cp = ch;
            size = 1;
            sign = '\0';
            break;
        }

        /*
         * All reasonable formats wind up here.  At this point, `cp'
         * points to a string which (if not flags&LADJUST) should be
         * padded out to `width' places.  If flags&ZEROPAD, it should
         * first be prefixed by any sign or other prefix; otherwise,
         * it should be blank padded before the prefix is emitted.
         * After any left-hand padding and prefixing, emit zeroes
         * required by a decimal [diouxX] precision, then print the
         * string proper, then emit zeroes required by any leftover
         * floating precision; finally, if LADJUST, pad with blanks.
         *
         * Compute actual size, so we know how much to pad.
         * size excludes decimal prec; realsz includes it.
         */
        realsz = dprec > size ? dprec : size;
        if (sign)
            realsz++;
        else if (flags & HEXPREFIX)
            realsz+= 2;

        /* adjust ret */
        ret += width > realsz ? width : realsz;

        /* right-adjusting blank padding */
        if ((flags & (LADJUST|ZEROPAD)) == 0) {
            n = width - realsz;
            while (n-- > 0)
                PUTCHAR(' ');
        }

        /* prefix */
        if (sign) {
            PUTCHAR(sign);
        } else if (flags & HEXPREFIX) {
            PUTCHAR('0');
            PUTCHAR(ch);
        }

        /* right-adjusting zero padding */
        if ((flags & (LADJUST|ZEROPAD)) == ZEROPAD) {
            n = width - realsz;
            while (n-- > 0)
                PUTCHAR('0');
        }

        /* leading zeroes from decimal precision */
        n = dprec - size;
        while (n-- > 0)
            PUTCHAR('0');

        /* the string or number proper */
        while (size--)
            PUTCHAR(*cp++);
        /* left-adjusting padding (always blank) */
        if (flags & LADJUST) {
            n = width - realsz;
            while (n-- > 0)
                PUTCHAR(' ');
        }
    }

done:
    return ret;
    /* NOTREACHED */
}

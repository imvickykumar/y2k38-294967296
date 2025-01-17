```python
>>> from datetime import datetime
>>> ts = int("2147483647")
>>> ts
2147483647
>>> print(datetime.utcfromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S'))
2038-01-19 03:14:07
```

This is an implementation of POSIX time.h which solves the year 2038
bug on systems where time_t is only 32 bits.  It is implemented in
bog-standard ANSI C.  The latest version can be found at
https://github.com/evalEmpire/y2038

It makes use of the system's native 32 bit functions to perform time
zone and daylight savings time calculations and thus does *not* need
to ship its own time zone table.

Here is a list of the currently implemented functions in time64.h and
their POSIX time.h equivalents.

      time64.h                      time.h
      --------                      ------
      localtime64_r                 localtime_r
      localtime64                   localtime
      gmtime64_r                    gmtime_r
      gmtime64                      gmtime
      asctime64_r                   asctime_r
      asctime64                     asctime
      ctime64_r                     ctime_r
      ctime64                       ctime
      timelocal64                   mktime
      mktime64                      mktime
      timegm64                      timegm (a GNU extension)

To install, simply copy time64.c and time64.h into your project and
make use of the functions.

To test, run "make test".  You must have Perl, prove (which comes with
a recent version of the Test::Harness Perl module) and bzdiff
installed to run the full test suite.  It will do a number of unit
tests, plus test against a large table of known good values in
different time zones.


Limitations, Issues, etc...
---------------------------

localtime64_r() gets its time zone and daylight savings time
information by mappping the future year back to a similar one between
2010 and 2037, safe for localtime_r().  The calculations are accurate
according to current time zone and daylight savings information, but
may become inaccurate if a change is made that takes place after 2010.
But its better to be off by an hour than 137 years.

Future versions will probe for a 64 bit safe system localtime_r() and
gmtime_r() and use that.  You can manually set the safe range of your
system in time64_config.h.

The maximum date is still limited by your tm struct.  Most 32 bit
systems use a signed integer tm_year which means the practical upper
limit is the year 2147483647 which is somewhere around 2**54.  You can
use a 64 bit clean tm struct by setting USE_TM64 in time64_config.h


Portability
-----------

I would like to add some configuration detection stuff in the future, but
for now all I can do is document the assumptions...

There are a number of configuration options in time64.h.

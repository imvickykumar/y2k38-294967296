#include <stdarg.h>
#include "time64.h"

#ifdef USE_TM64
#define year_t Year
#else
#define year_t int
#endif

int diag(const char*, ...);
void skip_all(const char *);
int do_test(const int, const char *, va_list);

int ok(const int, const char *, ...);
int is_int(const int, const int, const char *, ...);
int is_str(const char*, const char*, const char *, ...);
int is_Int64(const Int64, const Int64, const char *, ...);
int is_not_null(void *, const char *);
int tm_ok(const struct TM *,
          const int, const int, const int,
          const int, const int, const int);

int tm_is(const struct TM *, const struct TM *, const char *);
struct TM make_tm( int, int, int, int, int, Year );

void done_testing(void);

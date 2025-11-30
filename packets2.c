# 1 "packets.c"
# 1 "<command line>" 1
# 1 "packets.c" 2

# 1 "/usr/include/stdio.h" 1
# 29 "/usr/include/stdio.h"
# 1 "/usr/include/bits/libc-header-start.h" 1
# 34 "/usr/include/bits/libc-header-start.h"
# 1 "/usr/include/features.h" 1
# 416 "/usr/include/features.h"
# 1 "/usr/include/features-time64.h" 1
# 21 "/usr/include/features-time64.h"
# 1 "/usr/include/bits/wordsize.h" 1
# 21 "/usr/include/features-time64.h" 2

# 1 "/usr/include/bits/timesize.h" 1
# 20 "/usr/include/bits/timesize.h"
# 1 "/usr/include/bits/wordsize.h" 1
# 20 "/usr/include/bits/timesize.h" 2
# 22 "/usr/include/features-time64.h" 2
# 416 "/usr/include/features.h" 2
# 503 "/usr/include/features.h"
# 1 "/usr/include/stdc-predef.h" 1
# 503 "/usr/include/features.h" 2
# 525 "/usr/include/features.h"
# 1 "/usr/include/sys/cdefs.h" 1
# 731 "/usr/include/sys/cdefs.h"
# 1 "/usr/include/bits/wordsize.h" 1
# 731 "/usr/include/sys/cdefs.h" 2

# 1 "/usr/include/bits/long-double.h" 1
# 732 "/usr/include/sys/cdefs.h" 2
# 525 "/usr/include/features.h" 2
# 549 "/usr/include/features.h"
# 1 "/usr/include/gnu/stubs.h" 1
# 11 "/usr/include/gnu/stubs.h"
# 1 "/usr/include/gnu/stubs-64.h" 1
# 11 "/usr/include/gnu/stubs.h" 2
# 549 "/usr/include/features.h" 2
# 34 "/usr/include/bits/libc-header-start.h" 2
# 29 "/usr/include/stdio.h" 2






# 1 "/usr/lib/tcc/include/stddef.h" 1



typedef unsigned long size_t;
typedef long ssize_t;
typedef int wchar_t;
typedef long ptrdiff_t;
typedef long intptr_t;
typedef unsigned long uintptr_t;
# 23 "/usr/lib/tcc/include/stddef.h"
void *alloca(size_t size);
# 35 "/usr/include/stdio.h" 2



# 1 "/usr/lib/tcc/include/stdarg.h" 1



typedef __builtin_va_list va_list;






typedef va_list __gnuc_va_list;
# 38 "/usr/include/stdio.h" 2


# 1 "/usr/include/bits/types.h" 1
# 28 "/usr/include/bits/types.h"
# 1 "/usr/include/bits/wordsize.h" 1
# 28 "/usr/include/bits/types.h" 2

# 1 "/usr/include/bits/timesize.h" 1
# 20 "/usr/include/bits/timesize.h"
# 1 "/usr/include/bits/wordsize.h" 1
# 20 "/usr/include/bits/timesize.h" 2
# 29 "/usr/include/bits/types.h" 2


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;






typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;



typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
# 142 "/usr/include/bits/types.h"
# 1 "/usr/include/bits/typesizes.h" 1
# 142 "/usr/include/bits/types.h" 2

# 1 "/usr/include/bits/time64.h" 1
# 143 "/usr/include/bits/types.h" 2


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef long int __suseconds64_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;
# 40 "/usr/include/stdio.h" 2

# 1 "/usr/include/bits/types/__fpos_t.h" 1





# 1 "/usr/include/bits/types/__mbstate_t.h" 1
# 13 "/usr/include/bits/types/__mbstate_t.h"
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
# 6 "/usr/include/bits/types/__fpos_t.h" 2




typedef struct _G_fpos_t
{
  __off_t __pos;
  __mbstate_t __state;
} __fpos_t;
# 41 "/usr/include/stdio.h" 2

# 1 "/usr/include/bits/types/__fpos64_t.h" 1
# 10 "/usr/include/bits/types/__fpos64_t.h"
typedef struct _G_fpos64_t
{
  __off64_t __pos;
  __mbstate_t __state;
} __fpos64_t;
# 42 "/usr/include/stdio.h" 2

# 1 "/usr/include/bits/types/__FILE.h" 1



struct _IO_FILE;
typedef struct _IO_FILE __FILE;
# 43 "/usr/include/stdio.h" 2

# 1 "/usr/include/bits/types/FILE.h" 1



struct _IO_FILE;


typedef struct _IO_FILE FILE;
# 44 "/usr/include/stdio.h" 2

# 1 "/usr/include/bits/types/struct_FILE.h" 1
# 36 "/usr/include/bits/types/struct_FILE.h"
# 1 "/usr/include/bits/wordsize.h" 1
# 36 "/usr/include/bits/types/struct_FILE.h" 2

struct _IO_FILE;
struct _IO_marker;
struct _IO_codecvt;
struct _IO_wide_data;




typedef void _IO_lock_t;





struct _IO_FILE
{
  int _flags;


  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;


  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;
  int _flags2:24;

  char _short_backupbuf[1];
  __off_t _old_offset;


  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];

  _IO_lock_t *_lock;







  __off64_t _offset;

  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
  struct _IO_FILE **_prevchain;
  int _mode;

  int _unused3;

  __uint64_t _total_written;




  char _unused2[12 * sizeof (int) - 5 * sizeof (void *)];
};
# 45 "/usr/include/stdio.h" 2



# 1 "/usr/include/bits/types/cookie_io_functions_t.h" 1
# 27 "/usr/include/bits/types/cookie_io_functions_t.h"
typedef __ssize_t cookie_read_function_t (void *__cookie, char *__buf,
                                          size_t __nbytes);







typedef __ssize_t cookie_write_function_t (void *__cookie, const char *__buf,
                                           size_t __nbytes);







typedef int cookie_seek_function_t (void *__cookie, __off64_t *__pos, int __w);


typedef int cookie_close_function_t (void *__cookie);






typedef struct _IO_cookie_io_functions_t
{
  cookie_read_function_t *read;
  cookie_write_function_t *write;
  cookie_seek_function_t *seek;
  cookie_close_function_t *close;
} cookie_io_functions_t;
# 48 "/usr/include/stdio.h" 2
# 64 "/usr/include/stdio.h"
typedef __off_t off_t;
# 78 "/usr/include/stdio.h"
typedef __ssize_t ssize_t;






typedef __fpos_t fpos_t;
# 130 "/usr/include/stdio.h"
# 1 "/usr/include/bits/stdio_lim.h" 1
# 130 "/usr/include/stdio.h" 2
# 149 "/usr/include/stdio.h"
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;






extern int remove (const char *__filename) ;

extern int rename (const char *__old, const char *__new) ;



extern int renameat (int __oldfd, const char *__old, int __newfd,
		     const char *__new) ;
# 187 "/usr/include/stdio.h"
extern int fclose (FILE *__stream) ;
# 197 "/usr/include/stdio.h"
extern FILE *tmpfile (void)
    ;
# 214 "/usr/include/stdio.h"
extern char *tmpnam (char[20])  ;




extern char *tmpnam_r (char __s[20])  ;
# 231 "/usr/include/stdio.h"
extern char *tempnam (const char *__dir, const char *__pfx)
      ;






extern int fflush (FILE *__stream);
# 248 "/usr/include/stdio.h"
extern int fflush_unlocked (FILE *__stream);
# 267 "/usr/include/stdio.h"
extern FILE *fopen (const char *restrict __filename,
		    const char *restrict __modes)
    ;




extern FILE *freopen (const char *restrict __filename,
		      const char *restrict __modes,
		      FILE *restrict __stream)  ;
# 302 "/usr/include/stdio.h"
extern FILE *fdopen (int __fd, const char *__modes)
    ;





extern FILE *fopencookie (void *restrict __magic_cookie,
			  const char *restrict __modes,
			  cookie_io_functions_t __io_funcs)
    ;




extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
     ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc)
    ;
# 337 "/usr/include/stdio.h"
extern void setbuf (FILE *restrict __stream, char *restrict __buf)
  ;



extern int setvbuf (FILE *restrict __stream, char *restrict __buf,
		    int __modes, size_t __n)  ;




extern void setbuffer (FILE *restrict __stream, char *restrict __buf,
		       size_t __size)  ;


extern void setlinebuf (FILE *__stream)  ;







extern int fprintf (FILE *restrict __stream,
		    const char *restrict __format, ...) ;




extern int printf (const char *restrict __format, ...);

extern int sprintf (char *restrict __s,
		    const char *restrict __format, ...) ;





extern int vfprintf (FILE *restrict __s, const char *restrict __format,
		     __gnuc_va_list __arg) ;




extern int vprintf (const char *restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *restrict __s, const char *restrict __format,
		     __gnuc_va_list __arg) ;



extern int snprintf (char *restrict __s, size_t __maxlen,
		     const char *restrict __format, ...)
      ;

extern int vsnprintf (char *restrict __s, size_t __maxlen,
		      const char *restrict __format, __gnuc_va_list __arg)
      ;





extern int vasprintf (char **restrict __ptr, const char *restrict __f,
		      __gnuc_va_list __arg)
       ;
extern int __asprintf (char **restrict __ptr,
		       const char *restrict __fmt, ...)
       ;
extern int asprintf (char **restrict __ptr,
		     const char *restrict __fmt, ...)
       ;




extern int vdprintf (int __fd, const char *restrict __fmt,
		     __gnuc_va_list __arg)
     ;
extern int dprintf (int __fd, const char *restrict __fmt, ...)
     ;







extern int fscanf (FILE *restrict __stream,
		   const char *restrict __format, ...)  ;




extern int scanf (const char *restrict __format, ...) ;

extern int sscanf (const char *restrict __s,
		   const char *restrict __format, ...) ;






# 1 "/usr/include/bits/floatn.h" 1
# 132 "/usr/include/bits/floatn.h"
# 1 "/usr/include/bits/floatn-common.h" 1
# 25 "/usr/include/bits/floatn-common.h"
# 1 "/usr/include/bits/long-double.h" 1
# 25 "/usr/include/bits/floatn-common.h" 2
# 214 "/usr/include/bits/floatn-common.h"
typedef float _Float32;
# 251 "/usr/include/bits/floatn-common.h"
typedef double _Float64;
# 268 "/usr/include/bits/floatn-common.h"
typedef double _Float32x;
# 285 "/usr/include/bits/floatn-common.h"
typedef long double _Float64x;
# 132 "/usr/include/bits/floatn.h" 2
# 441 "/usr/include/stdio.h" 2
# 466 "/usr/include/stdio.h"
extern int fscanf (FILE *restrict __stream, const char *restrict __format, ...) __asm__("__isoc99_fscanf")  ;


extern int scanf (const char *restrict __format, ...) __asm__("__isoc99_scanf") ;

extern int sscanf (const char *restrict __s, const char *restrict __format, ...) __asm__("__isoc99_sscanf");
# 493 "/usr/include/stdio.h"
extern int vfscanf (FILE *restrict __s, const char *restrict __format,
		    __gnuc_va_list __arg)
       ;





extern int vscanf (const char *restrict __format, __gnuc_va_list __arg)
      ;


extern int vsscanf (const char *restrict __s,
		    const char *restrict __format, __gnuc_va_list __arg)
      ;
# 543 "/usr/include/stdio.h"
extern int vfscanf (FILE *restrict __s, const char *restrict __format, __gnuc_va_list __arg) __asm__("__isoc99_vfscanf")



       ;
extern int vscanf (const char *restrict __format, __gnuc_va_list __arg) __asm__("__isoc99_vscanf")

      ;
extern int vsscanf (const char *restrict __s, const char *restrict __format, __gnuc_va_list __arg) __asm__("__isoc99_vsscanf")



     ;
# 578 "/usr/include/stdio.h"
extern int fgetc (FILE *__stream) ;
extern int getc (FILE *__stream) ;





extern int getchar (void);






extern int getc_unlocked (FILE *__stream) ;
extern int getchar_unlocked (void);
# 603 "/usr/include/stdio.h"
extern int fgetc_unlocked (FILE *__stream) ;







extern int fputc (int __c, FILE *__stream) ;
extern int putc (int __c, FILE *__stream) ;





extern int putchar (int __c);
# 627 "/usr/include/stdio.h"
extern int fputc_unlocked (int __c, FILE *__stream) ;







extern int putc_unlocked (int __c, FILE *__stream) ;
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream) ;


extern int putw (int __w, FILE *__stream) ;







extern char *fgets (char *restrict __s, int __n, FILE *restrict __stream)
       ;
# 667 "/usr/include/stdio.h"
extern char *gets (char *__s)  ;
# 689 "/usr/include/stdio.h"
extern __ssize_t __getdelim (char **restrict __lineptr,
                             size_t *restrict __n, int __delimiter,
                             FILE *restrict __stream)  ;
extern __ssize_t getdelim (char **restrict __lineptr,
                           size_t *restrict __n, int __delimiter,
                           FILE *restrict __stream)  ;


extern __ssize_t getline (char **restrict __lineptr,
                          size_t *restrict __n,
                          FILE *restrict __stream)  ;







extern int fputs (const char *restrict __s, FILE *restrict __stream)
  ;





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream) ;






extern size_t fread (void *restrict __ptr, size_t __size,
		     size_t __n, FILE *restrict __stream)
  ;




extern size_t fwrite (const void *restrict __ptr, size_t __size,
		      size_t __n, FILE *restrict __s) ;
# 756 "/usr/include/stdio.h"
extern size_t fread_unlocked (void *restrict __ptr, size_t __size,
			      size_t __n, FILE *restrict __stream)
  ;
extern size_t fwrite_unlocked (const void *restrict __ptr, size_t __size,
			       size_t __n, FILE *restrict __stream)
  ;







extern int fseek (FILE *__stream, long int __off, int __whence)
  ;




extern long int ftell (FILE *__stream)  ;




extern void rewind (FILE *__stream) ;
# 793 "/usr/include/stdio.h"
extern int fseeko (FILE *__stream, __off_t __off, int __whence)
  ;




extern __off_t ftello (FILE *__stream)  ;
# 819 "/usr/include/stdio.h"
extern int fgetpos (FILE *restrict __stream, fpos_t *restrict __pos)
  ;




extern int fsetpos (FILE *__stream, const fpos_t *__pos) ;
# 850 "/usr/include/stdio.h"
extern void clearerr (FILE *__stream)  ;

extern int feof (FILE *__stream)   ;

extern int ferror (FILE *__stream)   ;



extern void clearerr_unlocked (FILE *__stream)  ;
extern int feof_unlocked (FILE *__stream)   ;
extern int ferror_unlocked (FILE *__stream)   ;







extern void perror (const char *__s) ;




extern int fileno (FILE *__stream)   ;




extern int fileno_unlocked (FILE *__stream)   ;
# 887 "/usr/include/stdio.h"
extern int pclose (FILE *__stream) ;





extern FILE *popen (const char *__command, const char *__modes)
    ;






extern char *ctermid (char *__s)
  ;
# 931 "/usr/include/stdio.h"
extern void flockfile (FILE *__stream)  ;



extern int ftrylockfile (FILE *__stream)   ;


extern void funlockfile (FILE *__stream)  ;
# 949 "/usr/include/stdio.h"
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);
# 2 "packets.c" 2

# 1 "/usr/include/stdlib.h" 1
# 27 "/usr/include/stdlib.h"
# 1 "/usr/include/bits/libc-header-start.h" 1
# 27 "/usr/include/stdlib.h" 2






# 1 "/usr/lib/tcc/include/stddef.h" 1
# 33 "/usr/include/stdlib.h" 2
# 41 "/usr/include/stdlib.h"
# 1 "/usr/include/bits/waitflags.h" 1
# 41 "/usr/include/stdlib.h" 2

# 1 "/usr/include/bits/waitstatus.h" 1
# 42 "/usr/include/stdlib.h" 2
# 59 "/usr/include/stdlib.h"
typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;





 typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;
# 98 "/usr/include/stdlib.h"
extern size_t __ctype_get_mb_cur_max (void)  ;



extern double atof (const char *__nptr)
        ;

extern int atoi (const char *__nptr)
        ;

extern long int atol (const char *__nptr)
        ;



 extern long long int atoll (const char *__nptr)
        ;



extern double strtod (const char *restrict __nptr,
		      char **restrict __endptr)
      ;



extern float strtof (const char *restrict __nptr,
		     char **restrict __endptr)  ;

extern long double strtold (const char *restrict __nptr,
			    char **restrict __endptr)
      ;
# 177 "/usr/include/stdlib.h"
extern long int strtol (const char *restrict __nptr,
			char **restrict __endptr, int __base)
      ;

extern unsigned long int strtoul (const char *restrict __nptr,
				  char **restrict __endptr, int __base)
      ;




extern long long int strtoq (const char *restrict __nptr,
			     char **restrict __endptr, int __base)
      ;


extern unsigned long long int strtouq (const char *restrict __nptr,
				       char **restrict __endptr, int __base)
      ;





extern long long int strtoll (const char *restrict __nptr,
			      char **restrict __endptr, int __base)
      ;


extern unsigned long long int strtoull (const char *restrict __nptr,
					char **restrict __endptr, int __base)
      ;
# 505 "/usr/include/stdlib.h"
extern char *l64a (long int __n)  ;


extern long int a64l (const char *__s)
        ;





# 1 "/usr/include/sys/types.h" 1
# 33 "/usr/include/sys/types.h"
typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;


typedef __loff_t loff_t;




typedef __ino_t ino_t;
# 59 "/usr/include/sys/types.h"
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;
# 97 "/usr/include/sys/types.h"
typedef __pid_t pid_t;





typedef __id_t id_t;
# 114 "/usr/include/sys/types.h"
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;





# 1 "/usr/include/bits/types/clock_t.h" 1






typedef __clock_t clock_t;
# 127 "/usr/include/sys/types.h" 2


# 1 "/usr/include/bits/types/clockid_t.h" 1






typedef __clockid_t clockid_t;
# 129 "/usr/include/sys/types.h" 2

# 1 "/usr/include/bits/types/time_t.h" 1
# 10 "/usr/include/bits/types/time_t.h"
typedef __time_t time_t;
# 130 "/usr/include/sys/types.h" 2

# 1 "/usr/include/bits/types/timer_t.h" 1






typedef __timer_t timer_t;
# 131 "/usr/include/sys/types.h" 2
# 145 "/usr/include/sys/types.h"
# 1 "/usr/lib/tcc/include/stddef.h" 1
# 145 "/usr/include/sys/types.h" 2



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;





# 1 "/usr/include/bits/stdint-intn.h" 1
# 24 "/usr/include/bits/stdint-intn.h"
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 156 "/usr/include/sys/types.h" 2


typedef __uint8_t u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;




typedef int register_t;
# 177 "/usr/include/sys/types.h"
# 1 "/usr/include/endian.h" 1
# 25 "/usr/include/endian.h"
# 1 "/usr/include/bits/endian.h" 1
# 36 "/usr/include/bits/endian.h"
# 1 "/usr/include/bits/endianness.h" 1
# 36 "/usr/include/bits/endian.h" 2
# 25 "/usr/include/endian.h" 2
# 36 "/usr/include/endian.h"
# 1 "/usr/include/bits/byteswap.h" 1
# 33 "/usr/include/bits/byteswap.h"
static inline __uint16_t
__bswap_16 (__uint16_t __bsx)
{



  return ((__uint16_t) ((((__bsx) >> 8) & 0xff) | (((__bsx) & 0xff) << 8)));

}






static inline __uint32_t
__bswap_32 (__uint32_t __bsx)
{



  return ((((__bsx) & 0xff000000u) >> 24) | (((__bsx) & 0x00ff0000u) >> 8) | (((__bsx) & 0x0000ff00u) << 8) | (((__bsx) & 0x000000ffu) << 24));

}
# 69 "/usr/include/bits/byteswap.h"
 static inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{



  return ((((__bsx) & 0xff00000000000000ull) >> 56) | (((__bsx) & 0x00ff000000000000ull) >> 40) | (((__bsx) & 0x0000ff0000000000ull) >> 24) | (((__bsx) & 0x000000ff00000000ull) >> 8) | (((__bsx) & 0x00000000ff000000ull) << 8) | (((__bsx) & 0x0000000000ff0000ull) << 24) | (((__bsx) & 0x000000000000ff00ull) << 40) | (((__bsx) & 0x00000000000000ffull) << 56));

}
# 36 "/usr/include/endian.h" 2

# 1 "/usr/include/bits/uintn-identity.h" 1
# 32 "/usr/include/bits/uintn-identity.h"
static inline __uint16_t
__uint16_identity (__uint16_t __x)
{
  return __x;
}

static inline __uint32_t
__uint32_identity (__uint32_t __x)
{
  return __x;
}

static inline __uint64_t
__uint64_identity (__uint64_t __x)
{
  return __x;
}
# 37 "/usr/include/endian.h" 2
# 177 "/usr/include/sys/types.h" 2



# 1 "/usr/include/sys/select.h" 1
# 31 "/usr/include/sys/select.h"
# 1 "/usr/include/bits/select.h" 1
# 31 "/usr/include/sys/select.h" 2



# 1 "/usr/include/bits/types/sigset_t.h" 1




# 1 "/usr/include/bits/types/__sigset_t.h" 1




typedef struct
{
  unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
} __sigset_t;
# 5 "/usr/include/bits/types/sigset_t.h" 2


typedef __sigset_t sigset_t;
# 34 "/usr/include/sys/select.h" 2




# 1 "/usr/include/bits/types/struct_timeval.h" 1







struct timeval
{




  __time_t tv_sec;
  __suseconds_t tv_usec;

};
# 38 "/usr/include/sys/select.h" 2


# 1 "/usr/include/bits/types/struct_timespec.h" 1
# 11 "/usr/include/bits/types/struct_timespec.h"
struct timespec
{



  __time_t tv_sec;




  __syscall_slong_t tv_nsec;
# 31 "/usr/include/bits/types/struct_timespec.h"
};
# 40 "/usr/include/sys/select.h" 2



typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
# 59 "/usr/include/sys/select.h"
typedef struct
  {






    __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];


  } fd_set;






typedef __fd_mask fd_mask;
# 102 "/usr/include/sys/select.h"
extern int select (int __nfds, fd_set *restrict __readfds,
		   fd_set *restrict __writefds,
		   fd_set *restrict __exceptfds,
		   struct timeval *restrict __timeout);
# 127 "/usr/include/sys/select.h"
extern int pselect (int __nfds, fd_set *restrict __readfds,
		    fd_set *restrict __writefds,
		    fd_set *restrict __exceptfds,
		    const struct timespec *restrict __timeout,
		    const __sigset_t *restrict __sigmask);
# 180 "/usr/include/sys/types.h" 2





typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 228 "/usr/include/sys/types.h"
# 1 "/usr/include/bits/pthreadtypes.h" 1
# 24 "/usr/include/bits/pthreadtypes.h"
# 1 "/usr/include/bits/thread-shared-types.h" 1
# 45 "/usr/include/bits/thread-shared-types.h"
# 1 "/usr/include/bits/pthreadtypes-arch.h" 1
# 22 "/usr/include/bits/pthreadtypes-arch.h"
# 1 "/usr/include/bits/wordsize.h" 1
# 22 "/usr/include/bits/pthreadtypes-arch.h" 2
# 45 "/usr/include/bits/thread-shared-types.h" 2


# 1 "/usr/include/bits/atomic_wide_counter.h" 1
# 25 "/usr/include/bits/atomic_wide_counter.h"
typedef union
{
   unsigned long long int __value64;
  struct
  {
    unsigned int __low;
    unsigned int __high;
  } __value32;
} __atomic_wide_counter;
# 47 "/usr/include/bits/thread-shared-types.h" 2




typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;

typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;
# 77 "/usr/include/bits/thread-shared-types.h"
# 1 "/usr/include/bits/struct_mutex.h" 1
# 22 "/usr/include/bits/struct_mutex.h"
struct __pthread_mutex_s
{
  int __lock;
  unsigned int __count;
  int __owner;

  unsigned int __nusers;



  int __kind;

  short __spins;
  short __elision;
  __pthread_list_t __list;
# 53 "/usr/include/bits/struct_mutex.h"
};
# 77 "/usr/include/bits/thread-shared-types.h" 2
# 90 "/usr/include/bits/thread-shared-types.h"
# 1 "/usr/include/bits/struct_rwlock.h" 1
# 23 "/usr/include/bits/struct_rwlock.h"
struct __pthread_rwlock_arch_t
{
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad3;
  unsigned int __pad4;

  int __cur_writer;
  int __shared;
  signed char __rwelision;




  unsigned char __pad1[7];


  unsigned long int __pad2;


  unsigned int __flags;
# 55 "/usr/include/bits/struct_rwlock.h"
};
# 90 "/usr/include/bits/thread-shared-types.h" 2




struct __pthread_cond_s
{
  __atomic_wide_counter __wseq;
  __atomic_wide_counter __g1_start;
  unsigned int __g_size[2] ;
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
  unsigned int __unused_initialized_1;
  unsigned int __unused_initialized_2;
};

typedef unsigned int __tss_t;
typedef unsigned long int __thrd_t;

typedef struct
{
  int __data ;
} __once_flag;
# 24 "/usr/include/bits/pthreadtypes.h" 2



typedef unsigned long int pthread_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int  pthread_once_t;


union pthread_attr_t
{
  char __size[56];
  long int __align;
};

typedef union pthread_attr_t pthread_attr_t;




typedef union
{
  struct __pthread_mutex_s __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;


typedef union
{
  struct __pthread_cond_s __data;
  char __size[48];
   long long int __align;
} pthread_cond_t;





typedef union
{
  struct __pthread_rwlock_arch_t __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 228 "/usr/include/sys/types.h" 2
# 515 "/usr/include/stdlib.h" 2






extern long int random (void) ;


extern void srandom (unsigned int __seed) ;





extern char *initstate (unsigned int __seed, char *__statebuf,
			size_t __statelen)  ;



extern char *setstate (char *__statebuf)  ;







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *restrict __buf,
		     int32_t *restrict __result)  ;

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
      ;

extern int initstate_r (unsigned int __seed, char *restrict __statebuf,
			size_t __statelen,
			struct random_data *restrict __buf)
      ;

extern int setstate_r (char *restrict __statebuf,
		       struct random_data *restrict __buf)
      ;





extern int rand (void) ;

extern void srand (unsigned int __seed) ;



extern int rand_r (unsigned int *__seed) ;







extern double drand48 (void) ;
extern double erand48 (unsigned short int __xsubi[3])  ;


extern long int lrand48 (void) ;
extern long int nrand48 (unsigned short int __xsubi[3])
      ;


extern long int mrand48 (void) ;
extern long int jrand48 (unsigned short int __xsubi[3])
      ;


extern void srand48 (long int __seedval) ;
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
      ;
extern void lcong48 (unsigned short int __param[7])  ;





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
     unsigned long long int __a;

  };


extern int drand48_r (struct drand48_data *restrict __buffer,
		      double *restrict __result)  ;
extern int erand48_r (unsigned short int __xsubi[3],
		      struct drand48_data *restrict __buffer,
		      double *restrict __result)  ;


extern int lrand48_r (struct drand48_data *restrict __buffer,
		      long int *restrict __result)
      ;
extern int nrand48_r (unsigned short int __xsubi[3],
		      struct drand48_data *restrict __buffer,
		      long int *restrict __result)
      ;


extern int mrand48_r (struct drand48_data *restrict __buffer,
		      long int *restrict __result)
      ;
extern int jrand48_r (unsigned short int __xsubi[3],
		      struct drand48_data *restrict __buffer,
		      long int *restrict __result)
      ;


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
      ;

extern int seed48_r (unsigned short int __seed16v[3],
		     struct drand48_data *__buffer)  ;

extern int lcong48_r (unsigned short int __param[7],
		      struct drand48_data *__buffer)
      ;


extern __uint32_t arc4random (void)
      ;


extern void arc4random_buf (void *__buf, size_t __size)
      ;



extern __uint32_t arc4random_uniform (__uint32_t __upper_bound)
      ;




extern void *malloc (size_t __size)
      ;

extern void *calloc (size_t __nmemb, size_t __size)
        ;






extern void *realloc (void *__ptr, size_t __size)
       ;


extern void free (void *__ptr) ;







extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)


    ;


extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
      ;




# 1 "/usr/include/alloca.h" 1
# 25 "/usr/include/alloca.h"
# 1 "/usr/lib/tcc/include/stddef.h" 1
# 25 "/usr/include/alloca.h" 2







extern void *alloca (size_t __size) ;
# 707 "/usr/include/stdlib.h" 2





extern void *valloc (size_t __size)
      ;




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
       ;
# 730 "/usr/include/stdlib.h"
extern void abort (void)   ;



extern int atexit (void (*__func) (void))  ;
# 749 "/usr/include/stdlib.h"
extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
      ;





extern void exit (int __status)  ;
# 768 "/usr/include/stdlib.h"
extern void _Exit (int __status)  ;




extern char *getenv (const char *__name)   ;
# 786 "/usr/include/stdlib.h"
extern int putenv (char *__string)  ;





extern int setenv (const char *__name, const char *__value, int __replace)
      ;


extern int unsetenv (const char *__name)  ;






extern int clearenv (void) ;
# 814 "/usr/include/stdlib.h"
extern char *mktemp (char *__template)  ;
# 827 "/usr/include/stdlib.h"
extern int mkstemp (char *__template)  ;
# 849 "/usr/include/stdlib.h"
extern int mkstemps (char *__template, int __suffixlen)  ;
# 870 "/usr/include/stdlib.h"
extern char *mkdtemp (char *__template)   ;
# 923 "/usr/include/stdlib.h"
extern int system (const char *__command) ;
# 940 "/usr/include/stdlib.h"
extern char *realpath (const char *restrict __name,
		       char *restrict __resolved)  ;






typedef int (*__compar_fn_t) (const void *, const void *);
# 960 "/usr/include/stdlib.h"
extern void *bsearch (const void *__key, const void *__base,
		      size_t __nmemb, size_t __size, __compar_fn_t __compar)
      ;







extern void qsort (void *__base, size_t __nmemb, size_t __size,
		   __compar_fn_t __compar) ;
# 980 "/usr/include/stdlib.h"
extern int abs (int __x)   ;
extern long int labs (long int __x)   ;


 extern long long int llabs (long long int __x)
       ;
# 998 "/usr/include/stdlib.h"
extern div_t div (int __numer, int __denom)
       ;
extern ldiv_t ldiv (long int __numer, long int __denom)
       ;


 extern lldiv_t lldiv (long long int __numer,
				    long long int __denom)
       ;
# 1018 "/usr/include/stdlib.h"
extern char *ecvt (double __value, int __ndigit, int *restrict __decpt,
		   int *restrict __sign)   ;




extern char *fcvt (double __value, int __ndigit, int *restrict __decpt,
		   int *restrict __sign)   ;




extern char *gcvt (double __value, int __ndigit, char *__buf)
       ;




extern char *qecvt (long double __value, int __ndigit,
		    int *restrict __decpt, int *restrict __sign)
       ;
extern char *qfcvt (long double __value, int __ndigit,
		    int *restrict __decpt, int *restrict __sign)
       ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
       ;




extern int ecvt_r (double __value, int __ndigit, int *restrict __decpt,
		   int *restrict __sign, char *restrict __buf,
		   size_t __len)  ;
extern int fcvt_r (double __value, int __ndigit, int *restrict __decpt,
		   int *restrict __sign, char *restrict __buf,
		   size_t __len)  ;

extern int qecvt_r (long double __value, int __ndigit,
		    int *restrict __decpt, int *restrict __sign,
		    char *restrict __buf, size_t __len)
      ;
extern int qfcvt_r (long double __value, int __ndigit,
		    int *restrict __decpt, int *restrict __sign,
		    char *restrict __buf, size_t __len)
      ;





extern int mblen (const char *__s, size_t __n) ;


extern int mbtowc (wchar_t *restrict __pwc,
		   const char *restrict __s, size_t __n) ;


extern int wctomb (char *__s, wchar_t __wchar) ;



extern size_t mbstowcs (wchar_t *restrict  __pwcs,
			const char *restrict __s, size_t __n)
    ;

extern size_t wcstombs (char *restrict __s,
			const wchar_t *restrict __pwcs, size_t __n)


  ;






extern int rpmatch (const char *__response)   ;
# 1105 "/usr/include/stdlib.h"
extern int getsubopt (char **restrict __optionp,
		      char *const *restrict __tokens,
		      char **restrict __valuep)
       ;
# 1151 "/usr/include/stdlib.h"
extern int getloadavg (double __loadavg[], int __nelem)
      ;
# 1162 "/usr/include/stdlib.h"
# 1 "/usr/include/bits/stdlib-float.h" 1
# 1162 "/usr/include/stdlib.h" 2
# 3 "packets.c" 2

# 1 "/usr/include/string.h" 1
# 27 "/usr/include/string.h"
# 1 "/usr/include/bits/libc-header-start.h" 1
# 27 "/usr/include/string.h" 2







# 1 "/usr/lib/tcc/include/stddef.h" 1
# 34 "/usr/include/string.h" 2
# 43 "/usr/include/string.h"
extern void *memcpy (void *restrict __dest, const void *restrict __src,
		     size_t __n)  ;


extern void *memmove (void *__dest, const void *__src, size_t __n)
      ;





extern void *memccpy (void *restrict __dest, const void *restrict __src,
		      int __c, size_t __n)
      ;




extern void *memset (void *__s, int __c, size_t __n)  ;


extern int memcmp (const void *__s1, const void *__s2, size_t __n)
       ;
# 80 "/usr/include/string.h"
extern int __memcmpeq (const void *__s1, const void *__s2, size_t __n)
       ;
# 107 "/usr/include/string.h"
extern void *memchr (const void *__s, int __c, size_t __n)
        ;
# 141 "/usr/include/string.h"
extern char *strcpy (char *restrict __dest, const char *restrict __src)
      ;

extern char *strncpy (char *restrict __dest,
		      const char *restrict __src, size_t __n)
      ;


extern char *strcat (char *restrict __dest, const char *restrict __src)
      ;

extern char *strncat (char *restrict __dest, const char *restrict __src,
		      size_t __n)  ;


extern int strcmp (const char *__s1, const char *__s2)
       ;

extern int strncmp (const char *__s1, const char *__s2, size_t __n)
       ;


extern int strcoll (const char *__s1, const char *__s2)
       ;

extern size_t strxfrm (char *restrict __dest,
		       const char *restrict __src, size_t __n)
      ;




# 1 "/usr/include/bits/types/locale_t.h" 1
# 23 "/usr/include/bits/types/locale_t.h"
# 1 "/usr/include/bits/types/__locale_t.h" 1
# 27 "/usr/include/bits/types/__locale_t.h"
struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
};

typedef struct __locale_struct *__locale_t;
# 23 "/usr/include/bits/types/locale_t.h" 2

typedef __locale_t locale_t;
# 173 "/usr/include/string.h" 2


extern int strcoll_l (const char *__s1, const char *__s2, locale_t __l)
       ;


extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
			 locale_t __l)
     ;





extern char *strdup (const char *__s)
       ;






extern char *strndup (const char *__string, size_t __n)
       ;
# 246 "/usr/include/string.h"
extern char *strchr (const char *__s, int __c)
       ;
# 273 "/usr/include/string.h"
extern char *strrchr (const char *__s, int __c)
       ;
# 286 "/usr/include/string.h"
extern char *strchrnul (const char *__s, int __c)
       ;





extern size_t strcspn (const char *__s, const char *__reject)
       ;


extern size_t strspn (const char *__s, const char *__accept)
       ;
# 323 "/usr/include/string.h"
extern char *strpbrk (const char *__s, const char *__accept)
       ;
# 350 "/usr/include/string.h"
extern char *strstr (const char *__haystack, const char *__needle)
       ;




extern char *strtok (char *restrict __s, const char *restrict __delim)
      ;



extern char *__strtok_r (char *restrict __s,
			 const char *restrict __delim,
			 char **restrict __save_ptr)
      ;

extern char *strtok_r (char *restrict __s, const char *restrict __delim,
		       char **restrict __save_ptr)
      ;
# 380 "/usr/include/string.h"
extern char *strcasestr (const char *__haystack, const char *__needle)
       ;







extern void *memmem (const void *__haystack, size_t __haystacklen,
		     const void *__needle, size_t __needlelen)


    ;



extern void *__mempcpy (void *restrict __dest,
			const void *restrict __src, size_t __n)
      ;
extern void *mempcpy (void *restrict __dest,
		      const void *restrict __src, size_t __n)
      ;




extern size_t strlen (const char *__s)
       ;




extern size_t strnlen (const char *__string, size_t __maxlen)
       ;




extern char *strerror (int __errnum) ;
# 432 "/usr/include/string.h"
extern int strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__("__xpg_strerror_r")


    ;
# 458 "/usr/include/string.h"
extern char *strerror_l (int __errnum, locale_t __l) ;




# 1 "/usr/include/strings.h" 1
# 24 "/usr/include/strings.h"
# 1 "/usr/lib/tcc/include/stddef.h" 1
# 24 "/usr/include/strings.h" 2
# 34 "/usr/include/strings.h"
extern int bcmp (const void *__s1, const void *__s2, size_t __n)
       ;


extern void bcopy (const void *__src, void *__dest, size_t __n)
   ;


extern void bzero (void *__s, size_t __n)  ;
# 68 "/usr/include/strings.h"
extern char *index (const char *__s, int __c)
       ;
# 96 "/usr/include/strings.h"
extern char *rindex (const char *__s, int __c)
       ;






extern int ffs (int __i)  ;





extern int ffsl (long int __l)  ;
 extern int ffsll (long long int __ll)
      ;



extern int strcasecmp (const char *__s1, const char *__s2)
       ;


extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
       ;






extern int strcasecmp_l (const char *__s1, const char *__s2, locale_t __loc)
       ;



extern int strncasecmp_l (const char *__s1, const char *__s2,
			  size_t __n, locale_t __loc)
       ;
# 463 "/usr/include/string.h" 2



extern void explicit_bzero (void *__s, size_t __n)
    ;



extern char *strsep (char **restrict __stringp,
		     const char *restrict __delim)
      ;




extern char *strsignal (int __sig) ;
# 489 "/usr/include/string.h"
extern char *__stpcpy (char *restrict __dest, const char *restrict __src)
      ;
extern char *stpcpy (char *restrict __dest, const char *restrict __src)
      ;



extern char *__stpncpy (char *restrict __dest,
			const char *restrict __src, size_t __n)
      ;
extern char *stpncpy (char *restrict __dest,
		      const char *restrict __src, size_t __n)
      ;




extern size_t strlcpy (char *restrict __dest,
		       const char *restrict __src, size_t __n)
    ;



extern size_t strlcat (char *restrict __dest,
		       const char *restrict __src, size_t __n)
     ;
# 4 "packets.c" 2






# 1 "packets.h" 1

# 1 "/usr/include/stdint.h" 1
# 27 "/usr/include/stdint.h"
# 1 "/usr/include/bits/libc-header-start.h" 1
# 27 "/usr/include/stdint.h" 2


# 1 "/usr/include/bits/wchar.h" 1
# 29 "/usr/include/stdint.h" 2

# 1 "/usr/include/bits/wordsize.h" 1
# 30 "/usr/include/stdint.h" 2
# 38 "/usr/include/stdint.h"
# 1 "/usr/include/bits/stdint-uintn.h" 1
# 24 "/usr/include/bits/stdint-uintn.h"
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
# 38 "/usr/include/stdint.h" 2




# 1 "/usr/include/bits/stdint-least.h" 1
# 25 "/usr/include/bits/stdint-least.h"
typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;


typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;
# 42 "/usr/include/stdint.h" 2





typedef signed char		int_fast8_t;

typedef long int		int_fast16_t;
typedef long int		int_fast32_t;
typedef long int		int_fast64_t;
# 60 "/usr/include/stdint.h"
typedef unsigned char		uint_fast8_t;

typedef unsigned long int	uint_fast16_t;
typedef unsigned long int	uint_fast32_t;
typedef unsigned long int	uint_fast64_t;
# 76 "/usr/include/stdint.h"
typedef long int		intptr_t;


typedef unsigned long int	uintptr_t;
# 90 "/usr/include/stdint.h"
typedef __intmax_t		intmax_t;
typedef __uintmax_t		uintmax_t;
# 2 "packets.h" 2


# 1 "types.h" 1




typedef struct L_str {
  char *str;
  int len;
} lstr;

typedef struct Uuid {
  int64_t high;
  int64_t low;
} uuid;
# 4 "packets.h" 2

# 1 "player.h" 1




typedef struct Connection {
  int fd;
  uint8_t* backlog;
  uint32_t backlog_len;
} connection;

typedef struct Player {
  connection conn;
  int connection_state;
} player;

player *create_player(int fd);

void free_player(player *player);
# 5 "packets.h" 2

# 1 "rw.h" 1


# 1 "error_codes.h" 1
# 3 "rw.h" 2



int read_bool(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t *out);
int read_byte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int8_t *out);
int read_ubyte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t *out);
int read_short(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int16_t *out);
int read_ushort(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint16_t *out);
int read_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t *out);
int read_uint(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint32_t *out);
int read_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t *out);
int read_float(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, float *out);
int read_double(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t *out);
int read_var_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t *out);
int read_var_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t *out);
int read_var_str(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, lstr *out);
int read_uuid(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uuid *out);


int write_bool(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t val);
int write_byte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int8_t val);
int write_ubyte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t val);
int write_short(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int16_t val);
int write_ushort(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint16_t val);
int write_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t val);
int write_uint(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint32_t val);
int write_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t val);
int write_float(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, float val_float);
int write_double(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t val_double);
int write_var_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t value);
int write_var_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t value);
int write_var_str(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, lstr value);
int write_uuid(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uuid value);
# 6 "packets.h" 2
# 55 "packets.h"
typedef struct Game_Profile_Property {
  lstr name;
  lstr value;
  lstr signature;
} game_profile_property;

typedef struct Game_Profile {
  uuid uuid;
  lstr username;
  game_profile_property *properties;
  int game_profile_property_count;
} game_profile;



typedef struct Handshake_s {
  uint8_t *raw_data;

  int32_t protocol_version;
  lstr server_address;
  uint16_t port;
  int32_t intent;
} handshake;


typedef struct Login_Start_s {
  uint8_t *raw_data;

  lstr name;
  uuid uuid;
} login_start;


typedef struct Disconnect_Login_c {
  uint8_t *raw_data;

  lstr json;
} disconnect_login;
# 113 "packets.h"
int read_handshake (uint8_t **packet_buffer, unsigned int *pos, unsigned int max, handshake *out) { int error = 0; error = read_var_int(packet_buffer, pos, max, &out->protocol_version); if(error) return error;; error = read_var_str(packet_buffer, pos, max, &out->server_address); if(error) return error;; error = read_ushort(packet_buffer, pos, max, &out->port); if(error) return error;; error = read_var_int(packet_buffer, pos, max, &out->intent); if(error) return error;; return 0; };




int read_game_profile_property (uint8_t **packet_buffer, unsigned int *pos, unsigned int max, game_profile_property *out) { int error = 0; error = read_var_str(packet_buffer, pos, max, &out->name); if(error) return error;; error = read_var_str(packet_buffer, pos, max, &out->value); if(error) return error;; return 0; }





int read_game_profile (uint8_t **packet_buffer, unsigned int *pos, unsigned int max, game_profile *out) { int error = 0; error = read_uuid(packet_buffer, pos, max, &out->uuid); if(error) return error;; error = read_var_str(packet_buffer, pos, max, &out->username); if(error) return error;; error = read_var_int(packet_buffer, pos, max, &out->game_profile_property_count); out->properties = malloc(out->game_profile_property_count*sizeof(game_profile_property)); game_profile_property *properties_ptr = out->properties; for (int i = 0; i < out->game_profile_property_count; i++) { error = read_game_profile_property(packet_buffer, pos, max, (properties_ptr++)); if(error) return error; }; return 0; };




int read_login_start (uint8_t **packet_buffer, unsigned int *pos, unsigned int max, login_start *out) { int error = 0; error = read_var_str(packet_buffer, pos, max, &out->name); if(error) return error;; error = read_uuid(packet_buffer, pos, max, &out->uuid); if(error) return error;; return 0; };






int read_disconnect_login (uint8_t **packet_buffer, unsigned int *pos, unsigned int max, disconnect_login *out) { int error = 0; error = read_var_str(packet_buffer, pos, max, &out->json); if(error) return error;; return 0; };

void print_handshake(handshake shake);


int read_login_start(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, login_start *out);
void print_login_start(login_start shake);
# 10 "packets.c" 2



# 1 "packets.h" 1





# 1 "rw.h" 1


# 1 "error_codes.h" 1
# 3 "rw.h" 2



int read_bool(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t *out);
int read_byte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int8_t *out);
int read_ubyte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t *out);
int read_short(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int16_t *out);
int read_ushort(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint16_t *out);
int read_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t *out);
int read_uint(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint32_t *out);
int read_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t *out);
int read_float(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, float *out);
int read_double(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t *out);
int read_var_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t *out);
int read_var_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t *out);
int read_var_str(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, lstr *out);
int read_uuid(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uuid *out);


int write_bool(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t val);
int write_byte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int8_t val);
int write_ubyte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t val);
int write_short(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int16_t val);
int write_ushort(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint16_t val);
int write_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t val);
int write_uint(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint32_t val);
int write_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t val);
int write_float(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, float val_float);
int write_double(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t val_double);
int write_var_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t value);
int write_var_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t value);
int write_var_str(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, lstr value);
int write_uuid(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uuid value);
# 6 "packets.h" 2
# 113 "packets.h"
int write_handshake (uint8_t **packet_buffer, unsigned int *pos, unsigned int max, handshake out) { int error = 0; error = write_var_int(packet_buffer, pos, max, out.protocol_version); if(error) return error;; error = write_var_str(packet_buffer, pos, max, out.server_address); if(error) return error;; error = write_ushort(packet_buffer, pos, max, out.port); if(error) return error;; error = write_var_int(packet_buffer, pos, max, out.intent); if(error) return error;; return 0; };




int write_game_profile_property (uint8_t **packet_buffer, unsigned int *pos, unsigned int max, game_profile_property out) { int error = 0; error = write_var_str(packet_buffer, pos, max, out.name); if(error) return error;; error = write_var_str(packet_buffer, pos, max, out.value); if(error) return error;; return 0; }





int write_game_profile (uint8_t **packet_buffer, unsigned int *pos, unsigned int max, game_profile out) { int error = 0; error = write_uuid(packet_buffer, pos, max, out.uuid); if(error) return error;; error = write_var_str(packet_buffer, pos, max, out.username); if(error) return error;; error = read_var_int(packet_buffer, pos, max, &out->game_profile_property_count); out->properties = malloc(out->game_profile_property_count*sizeof(game_profile_property)); game_profile_property *properties_ptr = out->properties; for (int i = 0; i < out->game_profile_property_count; i++) { error = read_game_profile_property(packet_buffer, pos, max, (properties_ptr++)); if(error) return error; }; return 0; };




int write_login_start (uint8_t **packet_buffer, unsigned int *pos, unsigned int max, login_start out) { int error = 0; error = write_var_str(packet_buffer, pos, max, out.name); if(error) return error;; error = write_uuid(packet_buffer, pos, max, out.uuid); if(error) return error;; return 0; };






int write_disconnect_login (uint8_t **packet_buffer, unsigned int *pos, unsigned int max, disconnect_login out) { int error = 0; error = write_var_str(packet_buffer, pos, max, out.json); if(error) return error;; return 0; };

void print_handshake(handshake shake);


int read_login_start(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, login_start *out);
void print_login_start(login_start shake);
# 13 "packets.c" 2


void print_handshake(handshake shake) {
  puts("handshake:");
  printf("protocol version: %d\n", shake.protocol_version);
  printf("hostname: %.*s\n", shake.server_address.len, shake.server_address.str);
  printf("port: %d\n", shake.port);
  printf("intent: %d\n", shake.intent);
}



void print_login_start(login_start login_s) {
  puts("login start:");
  printf("name: %.*s\n", login_s.name.len, login_s.name.str);
  {printf("uuid: %ld, %ld\n", (login_s.uuid).low, (login_s.uuid).high);};
}

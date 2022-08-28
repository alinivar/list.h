
#ifndef __list_h__
#define __list_h__

#ifdef __cplusplus
extern "{"
#endif

#include <stddef.h>

#ifndef LIST_MALLOC
extern void* malloc(size_t);
#define LIST_MALLOC malloc
#endif

#ifndef LIST_REALLOC
extern void* realloc(void*, size_t);
#define LIST_REALLOC realloc
#endif

#ifndef LIST_FREE
extern void free(void*);
#define LIST_FREE free
#endif

#define list(t) struct { size_t __itemsize, len, cap; t* data; }

#define lnew(t)     { sizeof(t), 0, 1, LIST_MALLOC(sizeof(t)*1), }

#define lnewn(t, c) { sizeof(t), 0, c, LIST_MALLOC(sizeof(t)*c), }

#define lpush(l, v) { \
                        if (l.len+1 > l.cap) \
                        { \
                            l.cap+=(l.cap>>1); \
                            l.data=LIST_REALLOC(l.data, l.cap*l.__itemsize); \
                        } \
                        l.data[l.len] = v; \
                        l.len = l.len + 1; \
                    }

#define lpop(l)     l.data[(l.len == 0) ? (l.len) : (l.len-1, l.len-=1)]

#define lfree(l)    { LIST_FREE(l.data); l.len = 0; l.cap = 0; l.__itemsize = 0; }

#ifdef __cplusplus
}
#endif

#endif

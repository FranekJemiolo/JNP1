#include <stdio.h>
#define ul unsigned long
#define cc const char
#ifdef __cplusplus
extern "C" {
#endif

ul strset_new();

void strset_delete(ul id);

size_t strset_size(ul id);

void strset_insert(ul id, cc* value);

void strset_remove(ul id, cc* value);

int strset_test(ul id, cc* value);

void strset_clear(ul id);

int strset_comp(ul id1, ul id2);
#ifdef __cplusplus
}
#endif

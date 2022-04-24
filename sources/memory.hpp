#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define CHUNK_SIZE sizeof(struct meta_data)
#define ALIGN_SIZE 2048
#define ALIGN(size) (((size) + (ALIGN_SIZE - 1)) & ~(ALIGN_SIZE - 1))

typedef struct meta_data
{
    size_t size;
    struct meta_data *next;
    int free;
} chunk;

void *my_malloc(size_t _size);
void *my_calloc(size_t nelem, size_t elsize);
void my_free(void *ptr);
chunk *find_free(chunk **last, size_t size);
chunk *os_request(chunk *last, size_t size);
chunk *get_chunk_ptr(void *ptr);

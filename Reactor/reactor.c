#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <glib.h>
#include <sys/epoll.h>
#include <unistd.h>

#include "reactor.h"

#define MAX_EVENTS 4096

struct reactor
{
    int epoll_fd;
    GHashTable *table; // (int, CallbackData)
};

static int *int_in_heap(int key)
{
    int *result;
    if ((result = malloc(sizeof(*result))) == NULL)
        abort();
    *result = key;
    return result;
}

typedef struct {
    Callback callback;
    void *arg;
} CallbackData;
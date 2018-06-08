#ifndef COMMON_H
#define COMMON_H

// what is this header really about? networking?

#ifdef LIBUS_USE_EPOLL
#include "internal/eventing/epoll.h"
#else
#include "internal/eventing/libuv.h"
#endif

#include "internal/networking/bsd.h"

enum {
    /* Two first bits */
    POLL_TYPE_SOCKET = 0,
    POLL_TYPE_LISTEN_SOCKET = 1,
    POLL_TYPE_CALLBACK = 2,

    /* Two last bits */
    POLL_TYPE_SOCKET_POLLING_OUT = 4,
    POLL_TYPE_SOCKET_POLLING_IN = 8
};

int us_internal_poll_type(struct us_poll *p);

void us_internal_dispatch_ready_poll(struct us_poll *p, int error, int events);
void us_internal_timer_sweep(struct us_loop *loop);
unsigned int us_internal_accept_poll_event(struct us_poll *p);

void sweep_timer_cb(struct us_timer *t);

struct us_socket {
    struct us_poll p;
    struct us_socket_context *context;
    struct us_socket *prev, *next;
    unsigned short timeout;
};

struct us_listen_socket {
    struct us_socket s;
    int socket_ext_size;
};

struct us_socket_context {
    struct us_loop *loop;
    //unsigned short timeout;
    struct us_socket *head;
    struct us_socket_context *next;

    void (*on_open)(struct us_socket *);
    void (*on_data)(struct us_socket *, char *data, int length);
    void (*on_writable)(struct us_socket *);
    void (*on_close)(struct us_socket *);
    //void (*on_timeout)(struct us_socket_context *);
    void (*on_socket_timeout)(struct us_socket *);
};

#endif // COMMON_H

#ifndef LOOP_H
#define LOOP_H

// we need to define us_internal_async here still!

struct us_internal_async;

struct us_internal_async *us_internal_create_async(struct us_loop *loop, int fallthrough, int ext_size);
void us_internal_async_set(struct us_internal_async *a, void (*cb)(struct us_internal_async *));
void us_internal_async_wakeup(struct us_internal_async *a);

struct us_loop_data {
    struct us_timer *sweep_timer;
    struct us_internal_async *wakeup_async;
    int last_write_failed;
    struct us_socket_context *head;
    void *recv_buf;
    void (*pre_cb)(struct us_loop *);
    void (*post_cb)(struct us_loop *);
};

void us_internal_loop_data_init(struct us_loop *loop, void (*wakeup_cb)(struct us_loop *loop), void (*pre_cb)(struct us_loop *loop), void (*post_cb)(struct us_loop *loop));

#endif // LOOP_H

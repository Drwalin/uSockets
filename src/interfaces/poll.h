/* Public interfaces for polls */

/* A fallthrough poll does not keep the loop running, it falls through */
WIN32_EXPORT struct us_poll *us_create_poll(struct us_loop *loop, int fallthrough, int ext_size);

/* Associate this poll with a socket descriptor and poll type */
WIN32_EXPORT void us_poll_init(struct us_poll *p, LIBUS_SOCKET_DESCRIPTOR fd, int poll_type);

/* Start, change and stop polling for events */
WIN32_EXPORT void us_poll_start(struct us_poll *p, struct us_loop *loop, int events);
WIN32_EXPORT void us_poll_change(struct us_poll *p, struct us_loop *loop, int events);
WIN32_EXPORT void us_poll_stop(struct us_poll *p, struct us_loop *loop);

/* Return what events we are polling for */
WIN32_EXPORT int us_poll_events(struct us_poll *p);

/* After stopping a poll you must manually free the memory */
WIN32_EXPORT void us_poll_free(struct us_poll *p);

/* Returns the user data extension of this poll */
WIN32_EXPORT void *us_poll_ext(struct us_poll *p);

/* Get associated socket descriptor from a poll */
WIN32_EXPORT LIBUS_SOCKET_DESCRIPTOR us_poll_fd(struct us_poll *p);

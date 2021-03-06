#ifndef PROXY_HTTP_LOGGER_H
#define PROXY_HTTP_LOGGER_H
#include <buffer/buffer.h>
#include <buffer/buffer.h>
#include <logger/logger.h>
#include <memory.h>
#include <pthread.h>
#include <selector/selector.h>
#include <stdbool.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>

#define GET_LOG(key) (struct log*)((key)->data)

typedef enum { LOG_OK, PIPE_FAIL } log_status;

struct log
{
  int readfd;
  int writefd;
  pthread_t logthread;
  buffer logbuf;
  void* log_buf_mem;
  fd_selector selector;
};
/** initialize the log structure and create the thread */
int log_start(struct log* l, fd_selector sel);
/**logger handle */
void log_close(struct selector_key* key);
/**logger handle */
void log_write(struct selector_key* key);

/**
* @param log structure which will going to write the message
* @param string of the message
*/
void log_send(struct log* l, char* s);
/**log_send with printf-like params */
void log_sendf(struct log* l, const char* fmt, ...);

#endif // PROXY_HTTP_LOGGER_H

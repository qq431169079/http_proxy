#include <protocol/protocol.h>
#include <stdlib.h>
#include <messages/messages.h>
#include <msg_queue/msg_queue.h>
#include <serializer/serializer.h>
#include <actions/actions.h>
#include "handlers.h"
#include <stdio.h>

void
admin_read_handler(struct selector_key * key)
{
  int rd_sz;
  addr_data_t admin_data = (addr_data_t) key->data;
  msg_t * msg = malloc(sizeof(msg_t));
  unsigned char buffer[MAX_READ];

  rd_sz = sctp_recvmsg(key->fd, buffer, MAX_READ,
      admin_data->addr, &admin_data->len, &admin_data->sri,
                       &admin_data->msg_flags);

  if(rd_sz <= 0)
    return;

  deserialize_msg(buffer, msg);
  printf("deserialized tipo %d\n\n", msg->type);
  switch(msg->type) {
    case SEND_CRED:
      check_credentials(msg->buffer, msg->buffer_size);
      break;
    case LIST_METRICS:
      send_list_metrics();
      break;
    case LIST_CONFIGS:
      send_list_configs();
      break;
    case GET_METRIC:
      send_metric(msg->param);
      break;
    case GET_CONFIG:
      send_config(msg->param);
      break;
    case SET_CONFIG:
      check_set_config(msg->param, msg->buffer, msg->buffer_size);
      break;
  }
}

void
admin_write_handler(struct selector_key * key) {
  addr_data_t admin_data = (addr_data_t) key->data;
  unsigned char buffer[MAX_MSG_SIZE];
  unsigned char * pointer;
  msg_t * msg;

  if (q_is_empty())
    return;

  msg = q_poll();
  pointer = serialize_msg(buffer, msg);

  sctp_sendmsg(key->fd, buffer, pointer - buffer,
     admin_data->addr, admin_data->len,
      admin_data->sri.sinfo_ppid, admin_data->sri.sinfo_flags,
       admin_data->sri.sinfo_stream, 0, 0);

}
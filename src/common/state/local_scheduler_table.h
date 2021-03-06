#ifndef LOCAL_SCHEDULER_TABLE_H
#define LOCAL_SCHEDULER_TABLE_H

#include "db.h"
#include "table.h"
#include "task.h"

/** This struct is sent with heartbeat messages from the local scheduler to the
 *  global scheduler, and it contains information about the load on the local
 *  scheduler. */
typedef struct {
  /** The total number of workers that are connected to this local scheduler. */
  int total_num_workers;
  /** The number of tasks queued in this local scheduler. */
  int task_queue_length;
  /** The number of workers that are available and waiting for tasks. */
  int available_workers;
  /** The resource vector of resources generally available to this local
   *  scheduler. */
  double static_resources[MAX_RESOURCE_INDEX];
  /** The resource vector of resources currently available to this local
   *  scheduler. */
  double dynamic_resources[MAX_RESOURCE_INDEX];
} local_scheduler_info;

/*
 *  ==== Subscribing to the local scheduler table ====
 */

/* Callback for subscribing to the local scheduler table. */
typedef void (*local_scheduler_table_subscribe_callback)(
    db_client_id client_id,
    local_scheduler_info info,
    void *user_context);

/**
 * Register a callback for a local scheduler table event.
 *
 * @param db_handle Database handle.
 * @param subscribe_callback Callback that will be called when the local
 *        scheduler event happens.
 * @param subscribe_context Context that will be passed into the
 *        subscribe_callback.
 * @param retry Information about retrying the request to the database.
 * @return Void.
 */
void local_scheduler_table_subscribe(
    db_handle *db_handle,
    local_scheduler_table_subscribe_callback subscribe_callback,
    void *subscribe_context,
    retry_info *retry);

/* Data that is needed to register local scheduler table subscribe callbacks
 * with the state database. */
typedef struct {
  local_scheduler_table_subscribe_callback subscribe_callback;
  void *subscribe_context;
} local_scheduler_table_subscribe_data;

/**
 * Send a heartbeat to all subscriers to the local scheduler table. This
 * heartbeat contains some information about the load on the local scheduler.
 *
 * @param db_handle Database handle.
 * @param info Information about the local scheduler, including the load on the
 *        local scheduler.
 * @param retry Information about retrying the request to the database.
 */
void local_scheduler_table_send_info(db_handle *db_handle,
                                     local_scheduler_info *info,
                                     retry_info *retry);

/* Data that is needed to publish local scheduer heartbeats to the local
 * scheduler table. */
typedef struct {
  local_scheduler_info info;
} local_scheduler_table_send_info_data;

#endif /* LOCAL_SCHEDULER_TABLE_H */

#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "request.h"
#include "web_server.h"

/**
 * @file load_balancer.h
 * @brief Declaration of the LoadBalancer class for managing web server
 * requests.
 */

#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

/**
 * @class LoadBalancer
 * @brief Manages a pool of web servers and distributes incoming requests among
 * them.
 */
class LoadBalancer {
 public:
  /**
   * @brief Number of active web servers managed by the load balancer.
   */
  int num_servers;

  /**
   * @brief Total number of cycles to run the load balancer.
   */
  int time_to_run;

  /**
   * @brief Number of cycles elapsed since the load balancer started.
   */
  int time_elapsed = 0;

  /**
   * @brief Minimum duration (in cycles) for a request.
   */
  int min_request_time = 5;

  /**
   * @brief Maximum duration (in cycles) for a request.
   */
  int max_request_time = 45;

  /**
   * @brief Output stream for logging and status messages.
   */
  std::ostream& output_stream;

  /**
   * @brief Queue storing all pending requests.
   */
  std::queue<Request> request_queue;

  /**
   * @brief Vector holding pointers to all heap-allocated web servers.
   */
  std::vector<WebServer*> servers;

  /**
   * @brief Constructs a LoadBalancer with a given number of servers and run
   * time.
   * @param num_servers Number of web servers to start with.
   * @param time_to_run Number of cycles to run the load balancer.
   * @param output_stream Output stream for logging.
   */
  LoadBalancer(int num_servers, int time_to_run, std::ostream& output_stream);

  /**
   * @brief Destructor. Cleans up all heap-allocated web servers and logs final
   * state.
   */
  ~LoadBalancer();

  /**
   * @brief Checks if the load balancer has finished running.
   * @return True if the elapsed time is greater than or equal to the run time.
   */
  bool is_finished() { return time_elapsed >= time_to_run; }

  /**
   * @brief Generates a random request with random IPs and duration.
   * @return A randomly generated Request object.
   */
  Request generate_random_request();

  /**
   * @brief Adds a request to the request queue.
   * @param req The request to add.
   */
  void add_request(const Request& req) { this->request_queue.push(req); }

  /**
   * @brief Main loop for handling requests and managing servers.
   * Continues until the specified run time is reached.
   */
  void handle_requests();

 private:
  /**
   * @brief Generates a random IPv4 address as a string.
   * @return Randomly generated IP address in the format x.x.x.x
   */
  std::string generate_random_ip();
};

#endif  // LOAD_BALANCER_H
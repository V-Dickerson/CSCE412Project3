
/**
 * @file web_server.h
 * @brief Declaration of the WebServer class for simulating a web server
 * handling requests.
 */

#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <iostream>

#include "request.h"

/**
 * @class WebServer
 * @brief Simulates a web server that processes incoming requests.
 */
class WebServer {
 public:
  /**
   * @brief Output stream for logging server activity.
   */
  std::ostream& output_stream;

  /**
   * @brief Unique identifier for the web server instance.
   */
  int num_webserver;

  /**
   * @brief The current request being processed by the server.
   */
  Request current;

  /**
   * @brief Indicates whether the server is idle and ready for a new request.
   */
  bool is_idle = true;

  /**
   * @brief Number of cycles spent processing the current request.
   */
  int processed_time = 0;

  /**
   * @brief Constructs a WebServer with a unique identifier and output stream.
   * @param num_webserver The server's unique number.
   * @param output_stream Output stream for logging.
   */
  WebServer(int num_webserver, std::ostream& output_stream = std::cout)
      : output_stream(output_stream), num_webserver(num_webserver) {
    output_stream << "Web server " << num_webserver << " opened." << std::endl;
  }

  /**
   * @brief Destructor. Logs server closure.
   */
  ~WebServer() {
    output_stream << "Web server " << num_webserver << " closed." << std::endl;
  }

  /**
   * @brief Assigns a new request to the server and begins processing.
   * @param request The request to handle.
   */
  void handle_request(Request request) {
    is_idle = false;
    processed_time = 0;
    current = request;
    output_stream << "Web server " << num_webserver << ": request from "
                  << request.ip_in << " to " << request.ip_out
                  << " :: Duration " << request.time << " Cycles" << std::endl;
  }

  /**
   * @brief Advances the server's processing by one cycle. Marks idle if done.
   */
  void pass_time() {
    processed_time++;
    if (processed_time >= current.time) {
      // enough time has passed, request is complete
      output_stream << "Web server " << num_webserver
                    << " request complete. Opening for new request."
                    << std::endl;
      is_idle = true;
      processed_time = 0;  // reset processed time for next request
    }
  }
};

#endif  // WEB_SERVER_H
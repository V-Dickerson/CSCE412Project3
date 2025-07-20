
/**
 * @file request.h
 * @brief Definition of the Request struct for representing network requests.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @struct Request
 * @brief Represents a network request with source and destination IPs and a
 * processing time.
 */
struct Request {
  /**
   * @brief Source IP address of the request.
   */
  std::string ip_in;

  /**
   * @brief Destination IP address of the request.
   */
  std::string ip_out;

  /**
   * @brief Number of cycles required to process the request.
   */
  int time;
};

#endif  // REQUEST_H

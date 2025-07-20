/**
 * @file main.cpp
 * @brief Entry point for the load balancer simulation program.
 */

#include <fstream>
#include <iostream>

#include "load_balancer.h"

/**
 * @brief Main function. Initializes the load balancer and runs the simulation.
 * @return Exit code.
 */
int main() {
  // get parameters from user
  int AMOUNT_TIME;
  int NUM_SERVERS;
  std::string OUTPUT_FILE_NAME;

  std::cout << "Enter the amount of cycles to run the load balancer: ";
  std::cin >> AMOUNT_TIME;
  std::cout << "Enter the number of servers to start with: ";
  std::cin >> NUM_SERVERS;
  std::cin.ignore();  // clear newline from input buffer
  std::cout << "Enter the preferred output file name (hit enter to default to log.txt): ";
  std::getline(std::cin, OUTPUT_FILE_NAME);
  if (OUTPUT_FILE_NAME.empty()) {
    OUTPUT_FILE_NAME = "log.txt";  // default file name
  }

  // Open log file for output
  std::ofstream log_file("load_balancer_logs/" + OUTPUT_FILE_NAME);
  if (!log_file.is_open()) {
    std::cerr << "Failed to open log file!" << std::endl;
    return 1;
  }

  log_file << "Load Balancer Started." << std::endl;

  // initialize load balancer, which will create all necessary requests &
  // servers
  LoadBalancer load_balancer(NUM_SERVERS, AMOUNT_TIME, log_file);

  // run the main simulation loop
  load_balancer.handle_requests();

  // notify user of completion
  std::cout << "Load balancer complete. Check log file for details."
            << std::endl;

  return 0;
}
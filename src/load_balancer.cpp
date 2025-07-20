
/**
 * @file load_balancer.cpp
 * @brief Implementation of the LoadBalancer class methods.
 */

#include "../include/load_balancer.h"

/**
 * @brief Constructs a LoadBalancer with a given number of servers and run time.
 * Initializes the request queue and creates the initial set of servers.
 * @param num_servers Number of web servers to start with.
 * @param time_to_run Number of cycles to run the load balancer.
 * @param output_stream Output stream for logging.
 */
LoadBalancer::LoadBalancer(int num_servers, int time_to_run,
                           std::ostream& output_stream)
    : num_servers(num_servers),
      time_to_run(time_to_run),
      output_stream(output_stream) {
  this->request_queue = std::queue<Request>();
  int NUM_STARTING_REQUESTS = 100 * num_servers;
  for (int i = 0; i < NUM_STARTING_REQUESTS; ++i) {
    Request req = this->generate_random_request();
    this->request_queue.push(req);
  }
  servers.reserve(num_servers);
  for (int i = 0; i < num_servers; ++i) {
    servers.push_back(new WebServer(i + 1, output_stream));
  }
  output_stream << "Number of servers: " << num_servers << std::endl;
  output_stream << "Total cycles to run: " << time_to_run << " cycles"
                << std::endl;
  output_stream << "Number of requests in queue: " << NUM_STARTING_REQUESTS
                << std::endl;
  output_stream << "Max request cycles: " << max_request_time << " cycles"
                << std::endl;
  output_stream << "Min request cycles: " << min_request_time << " cycles"
                << std::endl;
  output_stream << "######################## Load balancer initialized "
                   "########################"
                << std::endl;
}

/**
 * @brief Destructor. Cleans up all heap-allocated web servers and logs final
 * state.
 */
LoadBalancer::~LoadBalancer() {
  // add final logging
  output_stream << "######################## Load balancer closed "
                   "########################"
                << std::endl;
  // get relevant stats for logging before deletion
  int num_busy_servers = 0;
  for (const auto* server : this->servers) {
    if (!server->is_idle) {
      num_busy_servers++;
      output_stream << "Server " << server->num_webserver
                    << " still processing request from "
                    << server->current.ip_in << " to " << server->current.ip_out
                    << " :: Duration " << server->current.time << " Cycles"
                    << std::endl;
      output_stream << "Processed time: " << server->processed_time << " Cycles"
                    << std::endl;
    } else {
      output_stream << "Server " << server->num_webserver
                    << " is idle and ready for new requests." << std::endl;
    }
  }

  // delete all webserver objects after completion
  for (auto server : servers) {
    delete server;
  }
  servers.clear();

  output_stream << "Number of requests remaining in queue: "
                << this->request_queue.size() << std::endl;

  output_stream << "Number of busy servers: " << num_busy_servers << std::endl;
  output_stream << "Number of idle servers: "
                << (num_servers - num_busy_servers) << std::endl;
}

/**
 * @brief Generates a random IPv4 address as a string.
 * @return Randomly generated IP address in the format x.x.x.x
 */
std::string LoadBalancer::generate_random_ip() {
  std::string ip =
      std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." +
      std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
  return ip;
}

/**
 * @brief Generates a random request with random IPs and duration.
 * @return A randomly generated Request object.
 */
Request LoadBalancer::generate_random_request() {
  Request req;
  req.ip_in = this->generate_random_ip();
  req.ip_out = this->generate_random_ip();
  // anywhere between min and max cycles
  req.time =
      min_request_time + rand() % (max_request_time - min_request_time + 1);
  return req;
}

/**
 * @brief Main loop for handling requests and managing servers.
 * Assigns requests to idle servers, scales server pool, and simulates new
 * requests.
 */
void LoadBalancer::handle_requests() {
  while (!this->is_finished()) {
    output_stream << "######################## CYCLE " << time_elapsed + 1
                  << " ########################" << std::endl;
    int num_idle_servers = num_servers;
    int queue_size = request_queue.size();
    output_stream << "Current queue size: " << queue_size << std::endl;

    // assign requests to idle servers
    bool has_processed_request = false;
    for (auto* server : servers) {
      if (server->is_idle && !request_queue.empty()) {
        num_idle_servers--;
        Request req = request_queue.front();
        request_queue.pop();
        server->handle_request(req);
        has_processed_request = true;
      } else if (!server->is_idle) {
        num_idle_servers--;
      }
    }
    if (!has_processed_request && queue_size > 0) {
      output_stream << "No requests processed this cycle: all servers busy."
                    << std::endl;
      output_stream << "Queue Size: " << queue_size << std::endl;
    }
    output_stream << "Number of idle servers: " << num_idle_servers
                  << std::endl;
    output_stream << "Number of total servers: " << num_servers << std::endl;

    // Pass time for all servers
    for (auto* server : servers) {
      server->pass_time();
    }

    // dynamically add or remove servers based on queue size per server
    const double ADD_THRESHOLD = 1.8;
    const double REMOVE_THRESHOLD = 1.0;
    double queue_per_server =
        static_cast<double>(request_queue.size()) / num_servers;
    if (queue_per_server > ADD_THRESHOLD) {
      output_stream << "Adding new server " << (servers.size() + 1)
                    << " due to high load." << std::endl;
      servers.push_back(new WebServer(servers.size() + 1, output_stream));
      num_servers++;
    } else if (queue_per_server < REMOVE_THRESHOLD && servers.size() > 1) {
      output_stream << "Removing server " << servers.size()
                    << " due to low load." << std::endl;
      delete servers.back();
      servers.pop_back();
      num_servers--;
    }
    time_elapsed += 1;

    // simulate random new requests while program runs
    if (rand() % 3 == 0) {
      Request req = this->generate_random_request();
      this->add_request(req);
    }
  }
}

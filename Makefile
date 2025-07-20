CC = g++
CFLAGS = -Wall -Werror -Iinclude
BUILD = build

TARGET = outDebug
OBJS = $(BUILD)/main.o $(BUILD)/web_server.o $(BUILD)/load_balancer.o

all: $(BUILD) $(TARGET)

$(BUILD):
	mkdir -p $(BUILD)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(BUILD)/main.o: src/main.cpp include/web_server.h include/load_balancer.h include/request.h | $(BUILD)
	$(CC) $(CFLAGS) -c src/main.cpp -o $(BUILD)/main.o

$(BUILD)/web_server.o: src/web_server.cpp include/web_server.h include/request.h | $(BUILD)
	$(CC) $(CFLAGS) -c src/web_server.cpp -o $(BUILD)/web_server.o

$(BUILD)/load_balancer.o: src/load_balancer.cpp include/load_balancer.h include/web_server.h include/request.h | $(BUILD)
	$(CC) $(CFLAGS) -c src/load_balancer.cpp -o $(BUILD)/load_balancer.o

clean:
	rm -rf $(BUILD) $(TARGET)

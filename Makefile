##
## EPITECH PROJECT, 2023
## FLIP-LIB
## File description:
## Makefile
##


CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++20 -I./includes


LIB_NAME = flip


BUILD_DIR = build


SRCS = 	sources/App.cpp				\
		sources/Payload.cpp			\
		sources/SerialString.cpp	\
		sources/Client.cpp			\
		sources/Callback.cpp		\
		sources/Socket.cpp			\
		sources/Request.cpp			\
		sources/ThreadManager.cpp	\
		sources/Logger.cpp

OBJS = $(patsubst sources/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

all: $(LIB_NAME)
	cp lib$(LIB_NAME).so ../

$(LIB_NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -shared -o lib$(LIB_NAME).so $(OBJS)

$(BUILD_DIR)/%.o: sources/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf lib$(LIB_NAME).so

re: fclean all

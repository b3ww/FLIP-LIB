# FLIP-LIB

FLIP-LIB is a C++ library that provides a simple way to create network applications with a focus on ease of use and modularity. It includes features such as serialization, routing, and logging.

## Table of Contents

1. [Installation](#installation)
2. [Usage](#usage)
    1. [Creating an Application](#creating-an-application)
    2. [Defining Routes](#defining-routes)
    3. [Serializable Types](#serializable-types)
    4. [Client](#client)
    5. [Logging](#logging)
3. [Examples](#examples)
4. [API Reference](#api-reference)
5. [License](#license)

## Installation

To install FLIP-LIB, simply clone the repository and include the necessary headers in your project.

```bash
git clone https://github.com/your-username/flip-lib.git
```

## Usage

### Creating an Application

To create an application using FLIP-LIB, you need to define an instance of the `App` class. You can do this using the `FLIP_APP` macro, which takes the name of your application as an argument.

```cpp
FLIP_APP(MyApp);
```

This will create an instance of the `App` class named `MyApp`, with a default port of 0 (which will be automatically assigned by the system). If you want to specify a port, you can pass it as a second argument to the `run` method.

```cpp
int main() {
    MyApp.run(8080);
    return 0;
}
```

### Defining Routes

To define a route for your application, you can use the `FLIP_ROUTE` macro. This macro takes three arguments: the name of your application, the name of the route, and the type of the request payload.

```cpp
FLIP_ROUTE(MyApp, exampleRoute, SerialString) {
    // Your route handling code goes here
    FLIP_RESPONSE(200, SerialString, "Hello, world!");
}
```

The `FLIP_RESPONSE` macro is used to create a response for the route. It takes three arguments: the status code, the type of the response payload, and the response data.

### Serializable Types

FLIP-LIB provides several built-in serializable types, such as `SerialString`, `SerialUint16`, and `SerialVector`. You can also create your own serializable types by inheriting from the `Serializable` class and implementing the `serialize` and `deserialize` methods.

```cpp
class MySerializable : public Serializable {
public:
    MySerializable(int data) : _data(data) {}

    serialStream serialize() const override {
        // Serialize your data here
    }

    void deserialize(const serialStream& stream) override {
        // Deserialize your data here
    }

private:
    int _data;
};
```

To use your custom serializable type in a route, you need to declare it using the `FLIP_DECLARE_SERIALIZABLE_TEMPLATE` macro.

```cpp
FLIP_DECLARE_SERIALIZABLE_TEMPLATE(MySerializable);
```

### Client

To make requests to a server using FLIP-LIB, you can use the `Client` class. First, create an instance of the `Client` class with the server's IP address and port.

```cpp
Client client("127.0.0.1", 8080);
```

Then, you can send a request using the `request` method. This method takes three arguments: the name of the route, the request payload, and a callback to handle the response.

```cpp
client.request<SerialString>("exampleRoute", "Hello, server!", [](uint16_t code, const serialStream& data) {
    SerialString response;
    response.deserialize(data);
    std::cout << "Received response: " << response.getData() << std::endl;
});
```

### Logging

FLIP-LIB includes a simple logging system using the `Logger` class. You can create a logger instance with a specific name and use it to log messages at different levels (INFO, WARNING, ERROR, and DEBUG).

```cpp
Logger logger("MyLogger");
logger(LogLevel::INFO) << "This is an info message";
logger(LogLevel::WARNING) << "This is a warning message";
logger(LogLevel::ERROR) << "This is an error message";
logger(LogLevel::DEBUG) << "This is a debug message";
```

You can also configure the logger to output messages to different streams (e.g., stdout, stderr, or a file) using the `setup` method.

```cpp
std::ofstream logFile("log.txt");
logger.setup(LogLevel::INFO, logFile);
```

## Examples

For examples on how to use FLIP-LIB, please refer to the [examples](examples) directory in the repository.

## API Reference

For a detailed API reference, please refer to the [API documentation](docs/api.md).

## License

FLIP-LIB is released under the MIT License. See the [LICENSE](LICENSE) file for more information.
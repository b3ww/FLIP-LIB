# FLIP-LIB

FLIP-LIB is a C++ library that provides a simple way to create network applications with a focus on ease of use and modularity. It includes features such as serialization, routing, and logging.

## Table of Contents

1. [Installation](#installation)
2. [Usage](#usage)
    1. [Creating an Application](#creating-an-application)
    2. [Defining Routes](#defining-routes)
    3. [Serializable Types](#serializable-types)
        1. [Pre-implemented Types](#pre-implemented-types)
        2. [Custom Serializable Types](#custom-serializable-types)
    4. [Client](#client)
    5. [Callback Manager](#callback-manager)
    6. [Logging](#logging)
3. [Examples](#examples)
4. [License](#license)

## Installation

To install FLIP-LIB, simply clone the repository and include the necessary headers in your project.

```bash
git clone git@github.com:b3ww/FLIP-LIB.git
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

#### Pre-implemented Types

FLIP-LIB provides several built-in serializable types, such as `SerialString`, `SerialUint8`, `SerialUint16`, `SerialUint32`, `SerialUint64`, `SerialInt8`, `SerialInt16`, `SerialInt32`, `SerialInt64`, `SerialChar`, `SerialCharShort`, `SerialCharFloat`, `SerialCharDouble`, `SerialInt`, and `SerialVector`. These types can be used directly in your routes without any additional setup.

```cpp
FLIP_ROUTE(MyApp, echo, SerialString) {
    FLIP_RESPONSE(200, SerialString, pack.getData());
}

FLIP_ROUTE(MyApp, add, SerialVector<SerialUint32>) {
    SerialUint32 result = 0;
    for (const auto& num : pack.getData()) {
        result += num;
    }
    FLIP_RESPONSE(200, SerialUint32, result);
}
```

#### Custom Serializable Types

You can also create your own serializable types by inheriting from the `Serializable` class and implementing the `serialize` and `deserialize` methods.

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

### Callback Manager

The `CallbackManager` class allows you to manage multiple callbacks for different status codes. You can create a `CallbackManager` instance and pass it to the `Client::request` method.

```cpp
CallbackManager callbackManager({
    {200, [](uint16_t code, const serialStream& data) {
        SerialString response;
        response.deserialize(data);
        std::cout << "Received response: " << response.getData() << std::endl;
    }},
    {404, [](uint16_t code, const serialStream& data) {
        std::cout << "Route not found" << std::endl;
    }}
});

client.request<SerialString>("exampleRoute", "Hello, server!", callbackManager);
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

## License

FLIP-LIB is released under the following open-source license:

```
MIT License

Copyright (c) 2024 b3w/popochounet

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

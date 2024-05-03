#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "Flip.hpp"
#include "Serializable.hpp"
#include "Flip.hpp"
#include "SerialString.hpp"
#include "Client.hpp"

void print(uint16_t code, const flip::SerialString &r)
{
    std::cout << r.getData() << std::endl;
}

int main() {
    try {
        flip::Client a("127.0.0.1", 4242);
        flip::SerialString code("hello world !");
        flip::SerializableUint16 i(1);
        flip::Payload p("say_hello", i, code.serialize());
        flip::CallbackManager call({
            flip::makeCallback<flip::SerialString>(1, print)
        });
        flip::Request(p, call);
        flip::Request req(p, call);
        req >> a;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

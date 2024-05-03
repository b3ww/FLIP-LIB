#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "Flip.hpp"
#include "Serializable.hpp"
#include "Flip.hpp"
#include "SerialString.hpp"
#include "Client.hpp"

FLIP_APP(app, -1);

FLIP_ROUTE(app, test, flip::SerialString) {
    std::cout << pack.getData() << std::endl;
    // return {FLIP_VALID_RESPONSE_CODE, flip::SerialString("heyll ")}
}

FLIP_ROUTE(app, say_hello, flip::SerialString)
{
    std::cout << pack.getData() << std::endl;
}

void print(uint16_t code, const flip::SerializableUint64 &r)
{

}

int main() {
    app.run();
    return 0;
}

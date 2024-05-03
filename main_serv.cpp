#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "Flip.hpp"
#include "Serializable.hpp"
#include "MapPack.hpp"
#include "Flip.hpp"
#include "SerialString.hpp"
#include "Client.hpp"

FLIP_APP(app, 4242);

FLIP_ROUTE(app, test, flip::SerialString) {
    std::cout << pack.getData() << std::endl;
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

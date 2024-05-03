#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "Flip.hpp"
#include "Serializable.hpp"
#include "Flip.hpp"
#include "SerialString.hpp"
#include "Client.hpp"

FLIP_APP(app, 4242);

FLIP_ROUTE(app, say_hello, flip::SerialString)
{
    std::cout << pack.getData() << std::endl;
    FLIP_RESPONSE(7, flip::SerialString, "OK");
}

FLIP_ROUTE(app, backToBack, flip::SerialString)
{
    FLIP_RESPONSE(0, flip::SerialString, pack.getData());
}

FLIP_ROUTE(app, null, flip::SerialEmpty)
{
    FLIP_RESPONSE(0, flip::SerialString, "NULL data ok");
}

int main() {
    try {
        app.run();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

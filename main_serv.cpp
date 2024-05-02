#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "Flip.hpp"
#include "Serializable.hpp"
#include "MapPack.hpp"
#include "String.hpp"

FLIP_APP(4241, app);

FLIP_ROUTE(app, test, flip::SerialString) {
    std::cout << pack.getData() << std::endl;
}

FLIP_ROUTE(app, say_hello, flip::SerializableDouble)
{

}

int main() {
    app.run();
    return 0;
}

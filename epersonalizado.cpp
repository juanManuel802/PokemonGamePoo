#include "epersonalizado.h"
#include <iostream>
using namespace std;

Epersonalizado::Epersonalizado(const char *mensaje, const char *cau) : msg(mensaje), causa(cau) {}

const char *Epersonalizado::what() const noexcept {
    cerr << "ERROR: " << msg << endl;
    return causa;
}

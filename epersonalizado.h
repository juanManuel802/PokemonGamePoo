#ifndef EPERSONALIZADO_H
#define EPERSONALIZADO_H

#include <exception>
#include "iostream" 
using namespace std;

class Epersonalizado : public exception {
private:
    const char *msg;
    const char *causa;

public:
    Epersonalizado(const char *mensaje, const char *cau);
    const char *what() const noexcept override;
};

#endif

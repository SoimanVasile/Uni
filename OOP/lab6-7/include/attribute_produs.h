#ifndef ATTRIBUTE_PRODUS_H
#define ATTRIBUTE_PRODUS_H

#include <string>
class AttributeProdus{
    private:
        std::string nume, producator;

    public:
        AttributeProdus() = default;
        AttributeProdus(std::string n, std::string prod);

        std::string get_nume() const;
        std::string get_producator() const;
};

#endif

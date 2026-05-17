#pragma once
#include <string>

class Domain {
public:
    virtual int get_id() const = 0;

    virtual std::string to_csv() const = 0;

    virtual ~Domain() = default;
};

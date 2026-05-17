#pragma once
#include <vector>
#include <stdexcept>

class AbstractRepo {
public:
    virtual void add(const DOMAIN& item) = 0;
    virtual void remove(const int& id) = 0;
    virtual void update(const DOMAIN& item) = 0;
    virtual const DOMAIN& find(const int& id) const = 0;
    virtual const std::vector<DOMAIN>& get_all() const = 0;
    virtual size_t size() const = 0;
    virtual ~AbstractRepo() = default;
};

class RepoException : public std::runtime_error {
public:
    explicit RepoException(const std::string& message) : std::runtime_error(message) {}
};

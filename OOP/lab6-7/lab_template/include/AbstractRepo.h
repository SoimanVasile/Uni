#pragma once
#include <vector>
#include <stdexcept>

template <typename T, typename Key>
class AbstractRepo {
public:
    virtual void add(const T& item) = 0;
    virtual void remove(const Key& id) = 0;
    virtual void update(const T& item) = 0;
    virtual const T& find(const Key& id) const = 0;
    virtual const std::vector<T>& get_all() const = 0;
    virtual size_t size() const = 0;
    virtual ~AbstractRepo() = default;
};

class RepoException : public std::runtime_error {
public:
    explicit RepoException(const std::string& message) : std::runtime_error(message) {}
};

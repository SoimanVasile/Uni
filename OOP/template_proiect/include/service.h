#pragma once
#include "AbstractRepo.h"
#include <vector>

class Service {
protected:
    AbstractRepo& repo;

public:
    explicit Service(AbstractRepo& r) : repo(r) {}

    virtual void add(const DOMAIN& item) {
        repo.add(item);
    }

    virtual void remove(const DOMAIN& id) {
        repo.remove(id);
    }

    virtual void update(const DOMAIN& item) {
        repo.update(item);
    }

    virtual const DOMAIN& find(const int& id) const {
        return repo.find(id);
    }

    virtual const std::vector<DOMAIN>& get_all() const {
        return repo.get_all();
    }

    virtual size_t size() const {
        return repo.size();
    }

    virtual ~Service() = default;
};

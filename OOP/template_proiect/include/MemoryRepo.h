#pragma once
#include "AbstractRepo.h"
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>

class MemoryRepo : public AbstractRepo {
protected:
    std::vector<DOMAIN> items;

public:
    virtual void add(const DOMAIN& item) override {
        auto it = std::find_if(items.begin(), items.end(),
                               [&](const DOMAIN& el) { return el.get_id() == item.get_id(); });
        if (it != items.end()) {
            throw RepoException("Entity with this ID already exists!");
        }
        items.push_back(item);
    }

    virtual void remove(const int& id) override {
        auto it = std::find_if(items.begin(), items.end(),
                               [&](const DOMAIN& el) { return el.get_id() == id; });
        if (it == items.end()) {
            throw RepoException("Entity with this ID does not exist!");
        }
        items.erase(it);
    }

    virtual void update(const DOMAIN& item) override {
        auto it = std::find_if(items.begin(), items.end(),
                               [&](const DOMAIN& el) { return el.get_id() == item.get_id(); });
        if (it == items.end()) {
            throw RepoException("Entity to update does not exist!");
        }
        *it = item;
    }

    virtual const DOMAIN& find(const int& id) const override {
        auto it = std::find_if(items.begin(), items.end(),
                               [&](const DOMAIN& el) { return el.get_id() == id; });
        if (it == items.end()) {
            throw RepoException("Entity with this ID does not exist!");
        }
        return *it;
    }

    virtual const std::vector<DOMAIN>& get_all() const override {
        return items;
    }

    virtual size_t size() const override {
        return items.size();
    }
};

/**
 * FileRepo - CSV-backed repository.
 *
 * Extends MemoryRepo by persisting all data to a CSV file.
 * Loads the file into memory on construction, and re-saves after every mutation.
 *
 * USAGE: When you define your concrete DOMAIN class, you must:
 *   1. Implement `std::string to_csv() const` — returns all fields comma-separated
 *      e.g., "1,John,25"
 *   2. Provide a factory function matching the signature:
 *      DOMAIN from_csv(const std::string& line)
 *      that parses a CSV line and constructs a DOMAIN object.
 *   3. Pass that factory function to the FileRepo constructor.
 *
 * EXAMPLE (assuming a Product domain with id, name, price):
 *
 *   Product product_from_csv(const std::string& line) {
 *       std::istringstream ss(line);
 *       std::string token;
 *
 *       std::getline(ss, token, ','); int id = std::stoi(token);
 *       std::getline(ss, token, ','); std::string name = token;
 *       std::getline(ss, token, ','); double price = std::stod(token);
 *
 *       return Product(id, name, price);
 *   }
 *
 *   FileRepo repo("products.csv", product_from_csv);
 */
class FileRepo : public MemoryRepo {
private:
    std::string file_path;
    std::function<DOMAIN(const std::string&)> parser;

    void load_from_file() {
        std::ifstream fin(file_path);
        if (!fin.is_open()) {
            return;
        }

        std::string line;
        while (std::getline(fin, line)) {
            if (line.empty()) continue;
            DOMAIN item = parser(line);
            items.push_back(item);
        }
        fin.close();
    }

    void save_to_file() const {
        std::ofstream fout(file_path);
        if (!fout.is_open()) {
            throw RepoException("Cannot open file for writing: " + file_path);
        }

        for (const auto& item : items) {
            fout << item.to_csv() << "\n";
        }
        fout.close();
    }

public:
    /**
     * @param file_path  Path to the CSV file.
     * @param parser     A function that takes a CSV line and returns a DOMAIN object.
     */
    FileRepo(const std::string& file_path,
             std::function<DOMAIN(const std::string&)> parser)
        : file_path(file_path), parser(std::move(parser)) {
        load_from_file();
    }

    void add(const DOMAIN& item) override {
        MemoryRepo::add(item);
        save_to_file();
    }

    void remove(const int& id) override {
        MemoryRepo::remove(id);
        save_to_file();
    }

    void update(const DOMAIN& item) override {
        MemoryRepo::update(item);
        save_to_file();
    }
};

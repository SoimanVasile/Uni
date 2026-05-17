#include <domain.h>
#include <string>
#include <sstream>

// ──────────────────────────────────────────────────────────────────
// EXAMPLE concrete domain — replace with your actual entity.
//
// Steps to adapt:
//   1. Rename the class
//   2. Change the fields (add/remove private members)
//   3. Update the constructor, getters/setters
//   4. Update to_csv()  — output all fields comma-separated
//   5. Update NAME_from_csv() — parse them back in the same order
//   6. Replace DOMAIN with your class name everywhere in the project
// ──────────────────────────────────────────────────────────────────

class NAME : public Domain {
private:
    int id;
    // std::string field1;
    // double field2;
    // Add more fields here...

public:
    // Constructor — update parameters to match your fields
    NAME(int id /*, std::string field1, double field2 */)
        : id(id) /*, field1(field1), field2(field2) */ {}

    int get_id() const override {
        return id;
    }

    // Serialize all fields as CSV (same order as from_csv)
    std::string to_csv() const override {
        std::ostringstream oss;
        oss << id;
        // oss << "," << field1;
        // oss << "," << field2;
        return oss.str();
    }

    // Getters / setters for your fields...
    // std::string get_field1() const { return field1; }
    // double get_field2() const { return field2; }
};

// Factory function — parses one CSV line into a NAME object.
// Pass this to FileRepo's constructor.
// Must read fields in the SAME ORDER as to_csv() writes them.
NAME NAME_from_csv(const std::string& line) {
    std::istringstream ss(line);
    std::string token;

    std::getline(ss, token, ',');
    int id = std::stoi(token);

    // std::getline(ss, token, ',');
    // std::string field1 = token;

    // std::getline(ss, token, ',');
    // double field2 = std::stod(token);

    return NAME(id /*, field1, field2 */);
}

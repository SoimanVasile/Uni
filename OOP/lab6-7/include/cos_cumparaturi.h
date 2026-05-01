#ifndef COS_CUMPARATURI_H
#define COS_CUMPARATURI_H

#include "domain_produs.h"
#include <vector>
#include <random>

class CosCumparaturi {
private:
    std::vector<Produs> cos_produse;
public:
    /**
     * @brief Default constructor for CosCumparaturi
     */
    CosCumparaturi() = default;
    
    /**
     * @brief Empties all the products from the shopping cart
     */
    void goleste() {
        cos_produse.clear();
    }
    
    /**
     * @brief Adds a product to the shopping cart
     * 
     * @param p The product to add
     */
    void adauga(const Produs& p) {
        cos_produse.push_back(p);
    }
    
    /**
     * @brief Generates random products and adds them to the cart
     * 
     * @param numar Number of products to generate
     * @param produse_disponibile List of available products to choose from
     */
    void genereaza_random(size_t numar, const std::vector<Produs>& produse_disponibile);
    
    /**
     * @brief Calculates the total price of all products in the cart
     * 
     * @return float The total price
     */
    float get_total() const {
        float sum = 0;
        for (const auto& p : cos_produse) {
            sum += p.get_pret();
        }
        return sum;
    }
    
    /**
     * @brief Gets all products currently in the cart
     * 
     * @return const std::vector<Produs>& Reference to the vector of products
     */
    const std::vector<Produs>& get_all() const {
        return cos_produse;
    }

    /**
     * @brief Exports the shopping cart to a CSV file
     * 
     * @param filename Name of the export file
     */
    void export_csv(const std::string& filename) const;

    /**
     * @brief Exports the shopping cart to an HTML file
     * 
     * @param filename Name of the export file
     */
    void export_html(const std::string& filename) const;
};

#endif

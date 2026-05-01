#ifndef SERVICE_PRODUS_H
#define SERVICE_PRODUS_H

#include <string>
#include <vector>
#include "abstract_repo.h"
#include "attribute_produs.h"
#include "produs_tip.h"
#include "repo_produs.h"
#include "validator.h"
#include "undo.h"
#include <memory>
#include "cos_cumparaturi.h"

class ServiceProdus{
    private:
        AbstractRepo& repo_produs;
        Validator& validator_produs;
        std::vector<std::unique_ptr<ActiuneUndo>> undo_actions;
        CosCumparaturi cos_cump;

    public:

        /**
         * @brief Construct a new Service Produs object
         * 
         * @param repo_produs Reference to the product repository
         * @param validator Reference to the product validator
         */
        ServiceProdus(RepoProdus& repo_produs, Validator& validator);

        /**
         * @brief Adds a new product
         * 
         * @param attrib Attributes of the product
         * @param tip Type of the product
         * @param pret Price of the product
         */
        void add_produs(const AttributeProdus& attrib, const ProdusTip tip, const float pret);

        /**
         * @brief Undoes the last operation (add, delete, modify)
         */
        void undo();

        /**
         * @brief Gets all products
         * 
         * @return std::vector<Produs> Vector of all products
         */
        std::vector<Produs> get_all() const;

        /**
         * @brief Deletes a product by name and producer
         * 
         * @param name Name of the product
         * @param producator Producer of the product
         */
        void sterge_produs(const std::string& name, const std::string& producator);

        /**
         * @brief Modifies a product's price and type
         * 
         * @param attrib Attributes identifying the product
         * @param tip The new type
         * @param pret The new price
         */
        void modifica_produs(AttributeProdus& attrib, ProdusTip tip, float pret);

        /**
         * @brief Finds a product by name and producer
         * 
         * @param name Name of the product
         * @param producator Producer of the product
         * @return const Produs& Reference to the found product
         */
        const Produs& find_dupa_nume_si_producator(const std::string& name, const std::string& producator) const;

        /**
         * @brief Filters products by price
         * 
         * @param pret Maximum price
         * @return std::vector<Produs> Filtered products
         */
        std::vector<Produs> filtrare_dupa_pret(const float pret) const;

        /**
         * @brief Filters products by name
         * 
         * @param nume Name prefix or exact name
         * @return std::vector<Produs> Filtered products
         */
        std::vector<Produs> filtrare_dupa_nume(const std::string& nume) const;

        /**
         * @brief Filters products by producer
         * 
         * @param producator Producer's name
         * @return std::vector<Produs> Filtered products
         */
        std::vector<Produs> filtrare_dupa_producator(const std::string& producator) const;

        /**
         * @brief Sorts products by price
         * 
         * @return std::vector<Produs> Sorted products
         */
        std::vector<Produs> sortare_dupa_pret() const;

        /**
         * @brief Sorts products by name
         * 
         * @return std::vector<Produs> Sorted products
         */
        std::vector<Produs> sortare_dupa_nume() const;

        /**
         * @brief Sorts products by name and then by type
         * 
         * @return std::vector<Produs> Sorted products
         */
        std::vector<Produs> sortare_dupa_nume_si_tip() const;

        /**
         * @brief Empties the shopping cart
         */
        void cos_goleste();

        /**
         * @brief Adds a product to the shopping cart by name
         * 
         * @param nume Name of the product
         */
        void cos_adauga(const std::string& nume);

        /**
         * @brief Generates random products in the shopping cart
         * 
         * @param numar Number of products to generate
         */
        void cos_genereaza(size_t numar);

        /**
         * @brief Exports the shopping cart to a CSV file
         * 
         * @param filename Name of the export file
         */
        void cos_export_csv(const std::string& filename) const;

        /**
         * @brief Exports the shopping cart to an HTML file
         * 
         * @param filename Name of the export file
         */
        void cos_export_html(const std::string& filename) const;

        /**
         * @brief Gets the total price of the items in the shopping cart
         * 
         * @return float The total price
         */
        float cos_total() const;

        /**
         * @brief Gets all products in the shopping cart
         * 
         * @return const std::vector<Produs>& Reference to the cart products
         */
        const std::vector<Produs>& cos_get_all() const;
};

#endif

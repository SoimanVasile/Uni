#ifndef REPO_PRODUS_H
#define REPO_PRODUS_H

#include <vector>
#include "domain_produs.h"
#include "abstract_repo.h"
class RepoProdus : public AbstractRepo{
    
    private:
        std::vector<Produs> lista_produse;

    public:
        RepoProdus()=default;
        /**
         * @brief Default destructor
         */
        virtual ~RepoProdus() = default;

        /**
         * @brief Adds a new product to the repository
         * 
         * @param produs The product to add
         */
        virtual void add_produs(const Produs& produs) override;

        /**
         * @brief Gets the number of products in the repository
         * 
         * @return size_t The number of products
         */
        virtual size_t size() const override;

        /**
         * @brief Deletes a product from the repository by name and producer
         * 
         * @param nume The name of the product to delete
         * @param producator The producer of the product to delete
         */
        virtual void sterge_produs(const std::string& nume, const std::string& producator) override;

        /**
         * @brief Modifies an existing product in the repository
         * 
         * @param produs_nou The new product data (must match an existing product's name and producer)
         */
        virtual void modifica_produs(const Produs& produs_nou) override;

        /**
         * @brief Finds a product by its index
         * 
         * @param i The index of the product
         * @return const Produs& Reference to the found product
         */
        virtual const Produs& find_dupa_index(size_t i) const override;

        /**
         * @brief Finds a product by its name and producer
         * 
         * @param nume The name of the product
         * @param producator The producer of the product
         * @return const Produs& Reference to the found product
         */
        virtual const Produs& find_dupa_nume_si_producator(const std::string& nume, const std::string& producator) const override;

        /**
         * @brief Gets all products in the repository
         * 
         * @return const std::vector<Produs>& Reference to the vector of products
         */
        virtual const std::vector<Produs>& get_all() const override;
};

#include <string>

class RepoException {
private:
    std::string mesaj_eroare;
public:
    /**
     * @brief Construct a new Repo Exception object
     * 
     * @param mesaj The error message
     */
    RepoException(std::string mesaj) : mesaj_eroare(mesaj) {}
    
    /**
     * @brief Gets the error message
     * 
     * @return std::string The error message
     */
    std::string get_mesaj() const { return mesaj_eroare; }
};

#endif

#ifndef DOMAIN_PRODUS_H
#define DOMAIN_PRODUS_H

#include <string>

#include "attribute_produs.h"
#include "produs_tip.h"
class Produs{
    private:
        AttributeProdus attrib;
        ProdusTip tip;
        float pret{};

    public:
        /**
         * @brief Default constructor for Produs
         */
        Produs() = default;

        /**
         * @brief Construct a new Produs object
         * 
         * @param attrib Attributes of the product (name, producer)
         * @param tip Type of the product
         * @param pret Price of the product
         */
        Produs(const AttributeProdus& attrib,const ProdusTip tip, const float pret);

        /**
         * @brief Get the name of the product
         * 
         * @return std::string The product's name
         */
        std::string get_nume() const;

        /**
         * @brief Get the producer of the product
         * 
         * @return std::string The product's producer
         */
        std::string get_producator() const;

        /**
         * @brief Get the price of the product
         * 
         * @return float The product's price
         */
        float get_pret() const;

        /**
         * @brief Get the type of the product
         * 
         * @return ProdusTip The product's type
         */
        ProdusTip get_tip() const;

        /**
         * @brief Set a new price for the product
         * 
         * @param pret_nou The new price
         */
        void set_pret(float pret_nou);

        /**
         * @brief Set a new type for the product
         * 
         * @param tip_nou The new type
         */
        void set_tip(ProdusTip tip_nou);

        /**
         * @brief Output stream operator for Produs
         * 
         * @param stream The output stream
         * @param produs The product to output
         * @return std::ostream& The modified output stream
         */
        friend std::ostream& operator<<(std::ostream& stream, const Produs& produs);

        /**
         * @brief Equality operator for Produs
         * 
         * @param produs_check Another product to compare with
         * @return true If the products are equal
         * @return false If the products are not equal
         */
        bool operator==(const Produs& produs_check) const;

};

#endif

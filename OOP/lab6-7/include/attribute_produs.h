#ifndef ATTRIBUTE_PRODUS_H
#define ATTRIBUTE_PRODUS_H

#include <string>
class AttributeProdus{
    private:
        std::string nume, producator;

    public:
        /**
         * @brief Construct a new Attribute Produs object (default constructor)
         */
        AttributeProdus() = default;

        /**
         * @brief Construct a new Attribute Produs object
         * 
         * @param n Name of the product
         * @param prod Producer of the product
         */
        AttributeProdus(std::string n, std::string prod);

        /**
         * @brief Get the name of the product
         * 
         * @return std::string The name of the product
         */
        std::string get_nume() const;

        /**
         * @brief Get the producer of the product
         * 
         * @return std::string The producer of the product
         */
        std::string get_producator() const;
};

#endif

#ifndef PRODUS_TIP_H
#define PRODUS_TIP_H

#include <iostream>
#include <string>
enum ProdusTip{
    LACTATE,
    CARNE,
    DULCIURI,
    CURATENIE,
};

class ProdusTipExpection {
    private:
        std::string eroare;

    public:
        /**
         * @brief Construct a new Produs Tip Expection object
         * 
         * @param error The error message
         */
        ProdusTipExpection(std::string error) : eroare(error) {}

        /**
         * @brief Get the exception message
         * 
         * @return std::string The error message
         */
        std::string mesaj() const{
            return eroare;
        }
};

/**
 * @brief Input stream operator to read ProdusTip
 * 
 * @param stream The input stream
 * @param produs The ProdusTip variable to store the read value
 * @return std::istream& The modified input stream
 */
std::istream& operator>>(std::istream& stream, ProdusTip& produs);

/**
 * @brief Output stream operator to print ProdusTip
 * 
 * @param stream The output stream
 * @param produs The ProdusTip to print
 * @return std::ostream& The modified output stream
 */
std::ostream& operator<<(std::ostream& stream, const ProdusTip& produs);

#endif

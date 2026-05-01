#ifndef UI_H
#define UI_H

#include "service_produs.h"
class UI{
    private:
        ServiceProdus& service_produs;

        /**
         * @brief Handles user input for adding a product
         */
        void add_produs();

        /**
         * @brief Prints all products to the console
         */
        void print();

        /**
         * @brief Handles user input for deleting a product
         */
        void sterge_produs();

        /**
         * @brief Handles user input for modifying a product
         */
        void modifica_produs();

        /**
         * @brief Handles user input for finding a product
         */
        void find_dupa_nume_si_producator();

        /**
         * @brief Handles user input for filtering by price
         */
        void filtrare_dupa_pret();

        /**
         * @brief Handles user input for filtering by name
         */
        void filtrare_dupa_nume();

        /**
         * @brief Handles user input for filtering by producer
         */
        void filtrare_dupa_producator();

        /**
         * @brief Handles sorting by price
         */
        void sortare_dupa_pret();

        /**
         * @brief Handles sorting by name
         */
        void sortare_dupa_nume();

        /**
         * @brief Handles sorting by name and type
         */
        void sortare_dupa_nume_si_tip();

        /**
         * @brief Dispatches the undo action
         */
        void undo();

        /**
         * @brief Empties the shopping cart
         */
        void cos_goleste();

        /**
         * @brief Handles user input to add a product to the cart
         */
        void cos_adauga();

        /**
         * @brief Handles user input to generate a random cart
         */
        void cos_genereaza();

        /**
         * @brief Handles user input to export the cart to a file
         */
        void export_cos();


    public:
        /**
         * @brief Construct a new UI object
         * 
         * @param service_produs Reference to the product service
         */
        UI(ServiceProdus& service_produs);

        /**
         * @brief Runs the main UI loop
         */
        void run();
};

#endif

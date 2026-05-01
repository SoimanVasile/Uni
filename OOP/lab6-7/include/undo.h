#ifndef UNDO_H
#define UNDO_H

#include "abstract_repo.h"
#include "domain_produs.h"

/**
 * @brief Base class for undo actions
 */
class ActiuneUndo {
public:
    /**
     * @brief Executes the undo operation
     */
    virtual void doUndo() = 0;
    // LCOV_EXCL_START
    
    /**
     * @brief Virtual destructor
     */
    virtual ~ActiuneUndo() = default;
    // LCOV_EXCL_STOP
};

/**
 * @brief Undo action for adding a product
 */
class UndoAdauga : public ActiuneUndo {
private:
    AbstractRepo& repo;
    Produs produs_adaugat;
public:
    /**
     * @brief Construct a new Undo Adauga object
     * 
     * @param repo Reference to the repository
     * @param p The product that was added
     */
    UndoAdauga(AbstractRepo& repo, const Produs& p) : repo(repo), produs_adaugat(p) {}
    
    /**
     * @brief Undoes the add operation by deleting the product
     */
    void doUndo() override {
        repo.sterge_produs(produs_adaugat.get_nume(), produs_adaugat.get_producator());
    }
};

/**
 * @brief Undo action for deleting a product
 */
class UndoSterge : public ActiuneUndo {
private:
    AbstractRepo& repo;
    Produs produs_sters;
public:
    /**
     * @brief Construct a new Undo Sterge object
     * 
     * @param repo Reference to the repository
     * @param p The product that was deleted
     */
    UndoSterge(AbstractRepo& repo, const Produs& p) : repo(repo), produs_sters(p) {}
    
    /**
     * @brief Undoes the delete operation by adding the product back
     */
    void doUndo() override {
        repo.add_produs(produs_sters);
    }
};

/**
 * @brief Undo action for modifying a product
 */
class UndoModifica : public ActiuneUndo {
private:
    AbstractRepo& repo;
    Produs produs_vechi;
public:
    /**
     * @brief Construct a new Undo Modifica object
     * 
     * @param repo Reference to the repository
     * @param p The previous state of the product
     */
    UndoModifica(AbstractRepo& repo, const Produs& p) : repo(repo), produs_vechi(p) {}
    
    /**
     * @brief Undoes the modify operation by restoring the old product data
     */
    void doUndo() override {
        repo.modifica_produs(produs_vechi);
    }
};

#endif

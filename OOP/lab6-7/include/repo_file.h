#pragma once

#include "repo_produs.h"
#include <string>

class RepoFile : public RepoProdus {
    private:
        std::string file_path;

        void save_to_file() const;
        void load_from_file();
    public:
        RepoFile(const std::string& file_path);
        
        void add_produs(const Produs& produs) override;
        void sterge_produs(const std::string& nume, const std::string& producator) override;
        void modifica_produs(const Produs& produs_nou) override;
        
        ~RepoFile() override = default;
};

#include "cos_cumparaturi.h"
#include "repo_produs.h" // For RepoException
#include <fstream>

void CosCumparaturi::genereaza_random(size_t numar, const std::vector<Produs>& produse_disponibile) {
    if (produse_disponibile.empty()) return;

    static std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution<> dist(0, produse_disponibile.size() - 1);
    
    for (size_t i = 0; i < numar; ++i) {
        int rnd_idx = dist(mt);
        cos_produse.push_back(produse_disponibile[rnd_idx]);
    }
}

void CosCumparaturi::export_csv(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw RepoException("Nu se poate deschide fisierul pentru CSV!\n");
    }
    for (const auto& p : cos_produse) {
        out << p.get_nume() << "," << p.get_producator() << "," << p.get_tip() << "," << p.get_pret() << "\n";
    }
    out.close();
}

void CosCumparaturi::export_html(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw RepoException("Nu se poate deschide fisierul pentru HTML!\n");
    }
    out << "<html><body>\n<table border=\"1\">\n";
    out << "<tr><th>Nume</th><th>Producator</th><th>Tip</th><th>Pret</th></tr>\n";
    for (const auto& p : cos_produse) {
        out << "<tr><td>" << p.get_nume() << "</td><td>" << p.get_producator() << "</td><td>" 
            << p.get_tip() << "</td><td>" << p.get_pret() << "</td></tr>\n";
    }
    out << "</table>\n</body></html>\n";
    out.close();
}

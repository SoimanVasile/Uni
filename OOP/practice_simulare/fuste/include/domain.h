#pragma once
#include <string>

enum Marime{
    XS,
    S,
    M,
    L,
    XL,
};

inline std::string marime_to_string(Marime m){
    switch(m){
        case XS: return "XS";
        case S:  return "S";
        case M:  return "M";
        case L:  return "L";
        case XL: return "XL";
    }
    return "";
}

inline Marime string_to_marime(const std::string& s){
    if (s == "XS") return XS;
    if (s == "S")  return S;
    if (s == "M")  return M;
    if (s == "L")  return L;
    if (s == "XL") return XL;
    return XS;
}

class Fusta{
    private:
        int cod;
        std::string denumire;
        Marime marime;
        float pret;
        bool disponibilitate;

    public:
        Fusta(int cod, std::string& denumire, Marime m, float p, bool dis) : cod(cod), denumire(denumire), marime(m), pret(p), disponibilitate(dis) {};

        int get_cod() const{
            return cod;
        }
        std::string get_denumire() const{
            return denumire;
        }
        
        Marime get_marime() const{
            return marime;
        }

        float get_pret() const{
            return pret;
        }

        bool get_disponibilitate() const{
            return disponibilitate;
        }

        void set_disponibilitate(){
            disponibilitate = !disponibilitate;
        }

        ~Fusta()=default;
};

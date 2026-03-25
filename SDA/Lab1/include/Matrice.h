#pragma once

typedef int TElem;
#define NULL_TELEMENT 0

class DynamicArray {
private:
    TElem* elements;
    int capacity;
    int size;

    // BC = WC = AC: Theta(size)
    void resize() {
        capacity *= 2;
        TElem* newElements = new TElem[capacity];
        for (int i = 0; i < size; i++) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

public:
    // BC = WC = AC: Theta(1)
    DynamicArray(int initialCapacity = 10) {
        capacity = initialCapacity > 0 ? initialCapacity : 1;
        size = 0;
        elements = new TElem[capacity];
    }

    // BC = WC = AC: Theta(1)
    ~DynamicArray() {
        delete[] elements;
    }

    // BC: Theta(1), WC: Theta(size), AC: Theta(1) amortizat
    void push_back(TElem e) {
        if (size == capacity) resize();
        elements[size++] = e;
    }

    // BC: Theta(1), WC: Theta(size), AC: Theta(size)
    void insert(int pos, TElem e) {
        if (size == capacity) resize();
        for (int i = size; i > pos; i--) {
            elements[i] = elements[i - 1];
        }
        elements[pos] = e;
        size++;
    }

    // BC: Theta(1), WC: Theta(size), AC: Theta(size)
    void erase(int pos) {
        for (int i = pos; i < size - 1; i++) {
            elements[i] = elements[i + 1];
        }
        size--;
    }

    // BC = WC = AC: Theta(newSize)
    void manual_resize(int newSize, TElem defaultValue) {
        delete[] elements;
        size = newSize;
        capacity = newSize > 0 ? newSize : 1;
        elements = new TElem[capacity];
        for (int i = 0; i < size; i++) {
            elements[i] = defaultValue;
        }
    }

    TElem& operator[](int index) { return elements[index]; }             // BC = WC = AC: Theta(1)
    const TElem& operator[](int index) const { return elements[index]; } // BC = WC = AC: Theta(1)
    int getSize() const { return size; }                                  // BC = WC = AC: Theta(1)
};

class Matrice {
private:
    DynamicArray Linii;
    DynamicArray Coloana;
    DynamicArray valoare;
    int numar_linii;
    int numar_coloane;

public:
    Matrice(int nrLinii, int nrColoane);
    ~Matrice() {};

    TElem element(int i, int j) const;
    int nrLinii() const;
    int nrColoane() const;
    TElem modifica(int i, int j, TElem);
};

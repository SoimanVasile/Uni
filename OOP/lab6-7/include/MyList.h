#ifndef MY_LIST_H
#define MY_LIST_H
#include <concepts>
#define INIT_CAPACITY 2
#include <cstddef>
#include <functional>
template <typename T> class MyList{
    private:
        size_t number_of_elems, capacity;
        T* elem;

        void resize(){
            this->capacity *= 2;
            T* new_elem = new T[this->capacity];

            for (size_t i=0; i<this->number_of_elems; i++){
                new_elem[i] = this->elem[i];
            }

            delete[] this->elem;
            this->elem = new_elem;
        }
    public:

        T* begin() { return elem; }
        T* end()   { return elem + number_of_elems; }

        const T* begin() const { return elem; }
        const T* end()   const { return elem + number_of_elems; }

        T& operator[](size_t index) { return elem[index]; }
        const T& operator[](size_t index) const { return elem[index]; }

        MyList():number_of_elems(0), capacity(INIT_CAPACITY){elem = new T[capacity];  };

        void push(const T& value){
            if (number_of_elems >= capacity)
                resize();

            this->elem[this->number_of_elems] = value;
            this->number_of_elems++;
        }

        bool empty() const {
            if (number_of_elems == 0)
                return true;
            return false;
        }

        template <typename F>
            requires std::invocable<F, T, T>
        const T* find_elem(const T& value, F func) const{
            for (size_t i=0; i<this->size(); i++){
                if (func(value, this->elem[i]))
                    return &elem[i];
            }
            return nullptr;
        }

        template <typename F>
            requires std::invocable<F, T, T>
        bool remove_elem(const T& value, F func){
            for (size_t i=0; i<this->size(); i++){
                if (func(value, this->elem[i])){
                    for (size_t j=i; j<this->size()-1; j++)
                        elem[j] = elem[j+1];
                    this->number_of_elems--;
                    return true;
                }
            }
            return false;
        }

        std::size_t size() const{
            return number_of_elems;
        }

        template <typename F>
            requires std::invocable<F, T, T>
        bool modifica_elem(const T& val, F func){
            for (size_t i=0; i<this->size(); i++){
                if (func(val, elem[i])){
                    elem[i] = val;
                    return true;
                }
            }
            return false;
        }

        const T& find_index(size_t i) const{
            return elem[i];
        }

        const MyList<T>& get_list() const{
            return *this;
        }

        MyList& operator=(const MyList& other){
            if (this == &other){
                return *this;
            }
            delete[] this->elem;

            this->capacity = other.capacity;
            this->number_of_elems = other.number_of_elems;
            this->elem = new T[this->capacity];

            for (size_t i=0; i<this->number_of_elems; i++){
                this->elem[i] = other.elem[i];
            }

            return *this;

        }
        MyList(const MyList& my_list){
            this->capacity = my_list.number_of_elems;
            this->number_of_elems = my_list.number_of_elems;
            this->elem = new T[this->capacity];

            for (size_t i=0; i<this->number_of_elems; i++){
                this->elem[i] = my_list.elem[i];
            }
        }
        ~MyList(){delete[] elem;}
};

#endif 

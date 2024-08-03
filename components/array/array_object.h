#include <stdio.h>
#include <string.h>
#include <cstring>
#include "shape.h"
#include <math.h>

template<typename D>
class Array {
    public:

        Array();
        Array(Shape shape);
        Array(std::initializer_list<int> dims);

        //basic ops
        Array operator=(const Array& arr2);
        // template <typename U>
        // Array& operator=(Array<U>& arr2);

        Array operator+(D rhs);
        Array operator-(D rhs);
        Array operator/(D rhs);
        Array operator*(D rhs);
        Array operator^(D rhs);

        //array ops
        Array operator+(Array& rhs);
        Array operator-(Array& rhs);
        Array operator*(Array& rhs);
        Array operator/(Array& rhs);

        //access ops
        D& operator()(std::initializer_list<size_t> idxes);
        void operator()(D value, std::initializer_list<size_t> idxes);

        Array reshape(std::initializer_list<int> dims);
        Array permute(std::initializer_list<int> dims);
        Array t();
        Array dot(Array& rhs);

        std::vector<Array> split(int dim);
        
        Array squeeze(int dim);
        Array unsqueeze(int dim);
        
        Array expand(std::initializer_list<int> dims);

        Array broadcast_to(std::initializer_list<int> dims);
        Array broadcast_to(int dim1, int dim2, int dim3);
        Array broadcast_to(int dim1, int dim2, int dim3, int dim4);

        void set_name(std::string string);

        void fill_arr(D _data[], int size);
        void fill_vec(std::vector<D> _data, int size);
        void fill_grad_vec(std::vector<D> _data, std::vector<float> _dots, int size);

        Array ones();
        Array random();
        Array zeros();
        Array lin();

        static Array zeros(std::initializer_list<int> dims);
        static Array random(std::initializer_list<int> dims);
        static Array ones(std::initializer_list<int> dims);
        static Array lin(std::initializer_list<int> dims);
        static Array from_array(std::initializer_list<int> dims, std::initializer_list<D> array);

        void print_grad();
        void print();

        inline Shape get_shape(){
            return this->shape;
        }
        inline std::vector<D> get_data(){
            return this->data;  
        }
        inline std::vector<float> get_grad(){
            return this->dots;
        }

        //void to_array2();

    private:
        char name[10];
        Shape shape;
        int rank;

        std::vector<D> data;
        std::vector<float> dots;

        void print_arr2();
        void print_arr3();
        void print_arr4();

        Array try_dot_arr1(Array& rhs);
        Array try_dot_arr2(Array& rhs);
        Array try_dot_arr3(Array& rhs);
        Array try_dot_arr4(Array& rhs);
        
        Array try_dot(Array& lhs, Array& rhs);
};

template <typename D>
void Array<D>::set_name(std::string string){
    if (string.size() > 8) {
        std::cout << "that name is too long!"<< std::endl;
        return; 
    }

    if(8 > string.size())
        string.insert(0, 8 - string.size(), ' ');

    strcpy(this->name, string.c_str());
}
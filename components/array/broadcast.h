#include "dot.h"

Array Array::expand(int dim1, int dim2){
    if(this->rank > 2){
        printf("Cannot use Array2 expand method for Array%d.", this->rank);
        exit(0);  
    }

    if (dim1 == -1) dim1 = this->shape.shape()[0];
    if (dim2 == -1) dim2 = this->shape.shape()[1];

    if(dim1 % this->shape.shape()[0] != 0 || dim2 % this->shape.shape()[1] != 0){
        printf("Cannot expand Array with shape: (%d, %d) to shape: (%d, %d)", this->shape.shape()[0], this->shape.shape()[1], dim1, dim2);
        exit(0);
    }

    int dim1_repeats = dim1 / this->shape.shape()[0]; 
    int dim2_repeats = dim2 / this->shape.shape()[1]; 

    Array result(dim1, dim2);
    strcpy(result.name, this->name);
    int count = 0;

    for(int j = 0; j < this->shape.shape()[0] * dim1_repeats; j++){
        for(int i = 0; i < this->shape.shape()[1] * dim2_repeats; i++){
            result.data[count] = this->data[(j%this->shape.shape()[0])* this->shape.strides()[0] + i%this->shape.shape()[1]];
            result.dots[count] = this->dots[(j%this->shape.shape()[0])* this->shape.strides()[0] + i%this->shape.shape()[1]];
            count += 1;
        }
    }

    return result;
}
Array Array::expand(int dim1, int dim2, int dim3){
    if(this->rank != 3){
        printf("Cannot use Array3 expand method for Array%d.", this->rank);
        exit(0);  
    }

    if (dim1 == -1) dim1 = this->shape.shape()[0];
    if (dim2 == -1) dim2 = this->shape.shape()[1];
    if (dim3 == -1) dim3 = this->shape.shape()[2];

    if(dim1 % this->shape.shape()[0] != 0 || dim2 % this->shape.shape()[1] != 0 || dim3 % this->shape.shape()[2] != 0){
        printf(
            "Cannot expand Array with shape: (%d, %d, %d) to shape: (%d, %d, %d)",
            this->shape.shape()[0], 
            this->shape.shape()[1],
            this->shape.shape()[2],
            dim1, 
            dim2,
            dim3
        );
        exit(0);
    }

    int dim1_repeats = dim1 / this->shape.shape()[0]; 
    int dim2_repeats = dim2 / this->shape.shape()[1]; 
    int dim3_repeats = dim3 / this->shape.shape()[2]; 

    Array result(dim1, dim2, dim3);
    strcpy(result.name, this->name);
    int count = 0;
    
    for(int k = 0; k < this->shape.shape()[0] * dim1_repeats ; k++){
        for(int j = 0; j < this->shape.shape()[1] * dim2_repeats; j++){
            for(int i = 0; i < this->shape.shape()[2] * dim3_repeats; i++){
                result.data[count] = this->data[(k%this->shape.shape()[0])* this->shape.strides()[0] + (j%this->shape.shape()[1])* this->shape.strides()[1] + i%this->shape.shape()[2]];
                result.dots[count] = this->dots[(k%this->shape.shape()[0])* this->shape.strides()[0] + (j%this->shape.shape()[1])* this->shape.strides()[1] + i%this->shape.shape()[2]];
                count += 1;
            }
        }    
    }

    return result;
}
Array Array::expand(int dim1, int dim2, int dim3, int dim4){
    if(this->rank != 4){
        printf("Cannot use Array4 expand method for Array%d.", this->rank);
        exit(0);  
    }

    if (dim1 == -1) dim1 = this->shape.shape()[0];
    if (dim2 == -1) dim2 = this->shape.shape()[1];
    if (dim3 == -1) dim3 = this->shape.shape()[2];
    if (dim4 == -1) dim4 = this->shape.shape()[3 ];

    if(
        dim1 % this->shape.shape()[0] != 0 ||
        dim2 % this->shape.shape()[1] != 0 || 
        dim3 % this->shape.shape()[2] != 0 || 
        dim4 % this->shape.shape()[3] != 0
    ){
        printf(
            "Cannot expand Array with shape: (%d, %d, %d, %d) to shape: (%d, %d, %d, %d)",
            this->shape.shape()[0], 
            this->shape.shape()[1],
            this->shape.shape()[2],
            this->shape.shape()[2],
            dim1, 
            dim2,
            dim3,
            dim4
        );
        exit(0);
    }

    int dim1_repeats = dim1 / this->shape.shape()[0]; 
    int dim2_repeats = dim2 / this->shape.shape()[1]; 
    int dim3_repeats = dim3 / this->shape.shape()[2]; 
    int dim4_repeats = dim4 / this->shape.shape()[3]; 

    Array result(dim1, dim2, dim3, dim4);
    strcpy(result.name, this->name);
    int count = 0;

    for(int l = 0; l < this->shape.shape()[0] * dim1_repeats ; l++){
        for(int k = 0; k < this->shape.shape()[1] * dim2_repeats ; k++){
            for(int j = 0; j < this->shape.shape()[2] * dim3_repeats; j++){
                for(int i = 0; i < this->shape.shape()[3] * dim4_repeats; i++){
                    result.data[count] = this->data[(l%this->shape.shape()[0])* this->shape.strides()[0] + (k%this->shape.shape()[1])* this->shape.strides()[1] + (j%this->shape.shape()[2])* this->shape.strides()[2] + i%this->shape.shape()[3]];
                    result.dots[count] = this->dots[(l%this->shape.shape()[0])* this->shape.strides()[0] + (k%this->shape.shape()[1])* this->shape.strides()[1] + (j%this->shape.shape()[2])* this->shape.strides()[2] + i%this->shape.shape()[3]];
                    count += 1;
                }
            }    
        }
    }

    return result;
}

Array Array::broadcast_to(int dim1, int dim2){

    if (dim2 == -1) dim2 = this->shape.shape()[1];

    if(this->shape.shape()[1] != dim2 || this-> rank != 1){
        printf(
            "Cannot broadcast Array with shape: (%d, %d) to (%d, %d).",
            this->shape.shape()[0],
            this->shape.shape()[1],
            dim1,
            dim2
            );
        exit(0);  
    }

    Array result(dim1, dim2);
    strcpy(result.name, this->name);

    for(int i = 0; i < result.shape.size(); i++){
        result.data[i] = this->data[i % this->shape.size()];
        result.dots[i] = this->data[i % this->shape.size()];
    }

    return result;
}
Array Array::broadcast_to(int dim1, int dim2, int dim3){
    
    switch(this->rank){
        case 1: 
            if (dim3 == -1) dim3 = this->shape.shape()[1];
            if(this->shape.shape()[1] != dim3){
                printf(
                    "Cannot broadcast Array with shape: (%d, %d) to (%d, %d, %d).",
                    this->shape.shape()[0],
                    this->shape.shape()[1],
                    dim1,
                    dim2,
                    dim3
                );
                exit(0);  
            }
            break;
        case 2: 
            if (dim2 == -1) dim2 = this->shape.shape()[0];
            if (dim3 == -1) dim3 = this->shape.shape()[1];
            if(this->shape.shape()[0] != dim2 || this->shape.shape()[1] != dim3){
                printf(
                    "Cannot broadcast Array with shape: (%d, %d) to (%d, %d, %d).",
                    this->shape.shape()[0],
                    this->shape.shape()[1],
                    dim1,
                    dim2,
                    dim3
                );
                exit(0);  
            }
            break;
        default:
            printf("Invalid broadcast method for Array%d", this->rank);
            exit(0);
            break;
    }

    Array result(dim1, dim2, dim3);
    strcpy(result.name, this->name);

    for(int i = 0; i < result.shape.size(); i++){
        result.data[i] = this->data[i % this->shape.size()];
        result.dots[i] = this->data[i % this->shape.size()];
    }

    return result;
}
Array Array::broadcast_to(int dim1, int dim2, int dim3, int dim4){
    
    switch(this->rank){
        case 1: 
            if (dim4 == -1) dim4 = this->shape.shape()[1];
            if(this->shape.shape()[1] != dim4){
                printf(
                    "Cannot broadcast Array with shape: (%d, %d) to (%d, %d, %d, %d).",
                    this->shape.shape()[0],
                    this->shape.shape()[1],
                    dim1,
                    dim2,
                    dim3,
                    dim4
                );
                exit(0);  
            }
            break;
        case 2: 
            if (dim4 == -1) dim4 = this->shape.shape()[1];
            if (dim3 == -1) dim3 = this->shape.shape()[0];
            if(this->shape.shape()[0] != dim3 || this->shape.shape()[1] != dim4){
                printf(
                    "Cannot broadcast Array with shape: (%d, %d) to (%d, %d, %d, %d).",
                    this->shape.shape()[0],
                    this->shape.shape()[1],
                    dim1,
                    dim2,
                    dim3,
                    dim4
                );
                exit(0);  
            }
            break;
        case 3: 
            if (dim2 == -1) dim2 = this->shape.shape()[0];
            if (dim3 == -1) dim3 = this->shape.shape()[1];
            if (dim4 == -1) dim4 = this->shape.shape()[2];
            if(this->shape.shape()[0] != dim2 || this->shape.shape()[1] != dim3 || this->shape.shape()[2] != dim4){
                printf(
                    "Cannot broadcast Array with shape: (%d, %d, %d) to (%d, %d, %d, %d).",
                    this->shape.shape()[0],
                    this->shape.shape()[1],
                    this->shape.shape()[2],
                    dim1,
                    dim2,
                    dim3,
                    dim4
                );
                exit(0);  
            }
            break;
        default:
            printf("Invalid broadcast method for Array%d", this->rank);
            exit(0);
            break;
    }

    Array result(dim1, dim2, dim3, dim4);
    strcpy(result.name, this->name);

    for(int i = 0; i < result.shape.size(); i++){
        result.data[i] = this->data[i % this->shape.size()];
        result.dots[i] = this->data[i % this->shape.size()];
    }

    return result;
}

int test_expand(){
    Array array2(3,1);
    array2.lin();
    array2.print();
    std::cout<<std::endl;

    Array result;

    result = array2.expand(-1, -1);
    result.print();
    std::cout<<std::endl;

    result = array2.expand(6, -1);
    result.print();
    std::cout<<std::endl;

    result = array2.expand(-1, 9);
    result.print();
    std::cout<<std::endl;
    
    result = array2.expand(9, 5);
    result.print();
    std::cout<<std::endl;

    Array array3(3,2,1);
    array3.lin();
    array3.print();
    std::cout<<std::endl;

    result = array3.expand(-1,-1, 8);
    result.print();
    std::cout<<std::endl;

    result = array3.expand(6, 4, 8);
    result.print();
    std::cout<<std::endl;

    Array array4(4, 3,2,1);
    array4.lin();
    array4.print();
    std::cout<<std::endl;

    result = array4.expand(-1,-1,-1, 5);
    result.print();
    std::cout<<std::endl;

    result = array4.expand(8, -1, -1, -1);
    result.print();
    std::cout<<std::endl;

    return 0;
}
int test_broadcast_to(){
    Array array1(3);
    array1.lin();
    array1.print();
    std::cout<<std::endl;

    Array result;

    std::cout<<"braodcast_to: (5, -1)"<<std::endl;
    result = array1.broadcast_to(5, -1);
    result.print();
    std::cout<<std::endl;

    std::cout<<"braodcast_to: (4, 5,-1)"<<std::endl;
    result = array1.broadcast_to(4, 5, -1);
    result.print();
    std::cout<<std::endl;

    std::cout<<"braodcast_to: (2, 4, 5, -1)"<<std::endl;
    result = array1.broadcast_to(2, 4, 5, -1);
    result.print();
    std::cout<<std::endl;

    Array array2(2, 3);
    array2.lin();
    array2.print();
    std::cout<<std::endl;

    std::cout<<"braodcast_to: (4, -1,-1)"<<std::endl;
    result = array2.broadcast_to(4, -1, -1);
    result.print();
    std::cout<<std::endl;

    std::cout<<"braodcast_to: (2, 4, -1, -1)"<<std::endl;
    result = array2.broadcast_to(2, 4, -1, -1);
    result.print();
    std::cout<<std::endl;

    Array array3(2, 3, 3);
    array3.lin();
    array3.print();
    std::cout<<std::endl;

    std::cout<<"braodcast_to: (4, -1, -1, -1)"<<std::endl;
    result = array3.broadcast_to(4, -1, -1, -1);
    result.print();
    std::cout<<std::endl;

}
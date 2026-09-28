#include "dod.hpp"
#include "vector.cpp"
#include "data.cpp"

int
main(
    int    argc,
    char** argv) {

    dod::buffer             buf;
    dod::vector_array       vec_array;
    dod::vector_class_array vec_class_array;

    dod::data_buffer_create_and_init (buf);
    
    dod::vector_array_init           (vec_array, buf);
    dod::vector_array_process        (vec_array);
    dod::vector_array_destroy        (vec_array);

    dod::vector_class_array_init     (vec_class_array, buf);
    dod::vector_class_array_process  (vec_class_array);
    dod::vector_class_array_destroy  (vec_class_array);

    dod::data_buffer_destroy(buf);
    
}

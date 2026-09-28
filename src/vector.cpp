#include "dod.hpp"
#include <cstddef>
#include <math.h>
#include <assert.h>
namespace dod {

    vector_class::vector_class(
        const f32 x,
        const f32 y) {

        _x = x;
        _y = y;
    }


    f32
    vector_class::magnitude(
        void) {

        const f32 x_pow_2 = (_x * _x); 
        const f32 y_pow_2 = (_y * _y); 
        const f32 mag     = sqrtf(x_pow_2 + y_pow_2); 
    
        return(mag);
    }


    void
    vector_magnitude(
        const vector* in_vec,
        const u32     in_count,
        f32*          out_mag) {

        assert(in_vec   != NULL);
        assert(in_count != 0);
        assert(out_mag  != NULL);
    
        for (
            u32 vec_index = 0;
            vec_index < in_count;
            ++vec_index) {

            const vector& vec     = in_vec[vec_index];
            const f32     x_pow_2 = (vec.x * vec.x); 
            const f32     y_pow_2 = (vec.y * vec.y); 
            
            out_mag[vec_index] = sqrtf(x_pow_2 + y_pow_2); 

        }
    }

    void
    vector_array_init(
        vector_array& vec_array,
        const buffer& buf) {


        vec_array.count      = buf.length / sizeof(vector);
        vec_array.vectors    = (vector*)buf.data;
        vec_array.magnitudes = (f32*)VirtualAlloc(
            NULL,
            sizeof(f32) * vec_array.count,
            MEM_COMMIT | MEM_RESERVE,
            PAGE_READWRITE
        );

        assert(vec_array.count      != 0);
        assert(vec_array.vectors    != NULL);
        assert(vec_array.magnitudes != NULL);
    }
    
    void
    vector_array_destroy(
        vector_array& vec_array) {

        assert(vec_array.count      != 0);
        assert(vec_array.vectors    != NULL);
        assert(vec_array.magnitudes != NULL);
    
        VirtualFree(
            (void*)vec_array.magnitudes,
            sizeof(f32) * vec_array.count,
            MEM_RELEASE
        );
        
        vec_array.vectors    = NULL;
        vec_array.magnitudes = NULL;
        vec_array.count      = 0;
    }
    
    void
    vector_array_process(
        vector_array& vec_array) {

        assert(vec_array.count      != 0);
        assert(vec_array.vectors    != NULL);
        assert(vec_array.magnitudes != NULL);
    
        vector_magnitude(
            vec_array.vectors,
            vec_array.count,
            vec_array.magnitudes
        );
    }
    
    void
    vector_class_array_init(
        vector_class_array& vec_array,
        const buffer& buf) {
       
        vec_array.count      = buf.length / sizeof(vector_class);
        vec_array.vectors    = (vector_class*)VirtualAlloc(NULL, sizeof(vector_class) * vec_array.count, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        vec_array.magnitudes =          (f32*)VirtualAlloc(NULL, sizeof(f32)          * vec_array.count, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        
        assert(vec_array.count      != 0);
        assert(vec_array.vectors    != NULL);
        assert(vec_array.magnitudes != NULL);
   
        f32* vec_data = (f32*)buf.data;
        u32 data_index = 0;
        for (
            u32 vec_index = 0;
            vec_index < vec_array.count;
            ++vec_index
        ) {
            vec_array.vectors[vec_index] = vector_class(
                vec_data[data_index++], 
                vec_data[data_index++]
            );
        }
    }

    void
    vector_class_array_destroy(
        vector_class_array& vec_array) {

        VirtualFree(vec_array.magnitudes, sizeof(vector_class) * vec_array.count, MEM_RELEASE);
        VirtualFree(vec_array.vectors   , sizeof(f32)          * vec_array.count, MEM_RELEASE);
        vec_array.count      = 0;
        vec_array.vectors    = NULL;           
        vec_array.magnitudes = NULL;

    }

    void
    vector_class_array_process(
        vector_class_array& vec_array) {

        for (
            u32 vec_index = 0;
            vec_index < vec_array.count;
            ++vec_index) {

            vec_array.magnitudes[vec_index] = vec_array.vectors[vec_index].magnitude();
        }
    }
};

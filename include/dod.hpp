#ifndef DOD_HPP
#define DOD_HPP

#include <Windows.h>
#include <cstdint>

namespace dod {

    using u8  = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    using s8  = int8_t;
    using s16 = int16_t;
    using s32 = int32_t;
    using s64 = int64_t;

    using f32 = float;
    using f64 = double;


    class vector_class {

    private:
        f32 _x;
        f32 _y;

    public:

        vector_class(const f32 x, const f32 y);
       
        f32 magnitude(void);
    };  

    struct vector {
        f32 x;
        f32 y;
    };

    void vector_magnitude(const vector* in_vec, const u32 in_count, f32* out_mag);

    struct buffer {
        char* data;
        u32   length;
    };

    void data_buffer_create_and_init (buffer& buf);
    void data_buffer_destroy         (buffer& buf);

    struct vector_array {
        vector* vectors;
        f32*    magnitudes;
        u32     count;
    };

    void vector_array_init    (vector_array& vec_array, const buffer& buf);
    void vector_array_destroy (vector_array& vec_array);
    void vector_array_process (vector_array& vec_array);


    struct vector_class_array {
        vector_class* vectors;
        f32*          magnitudes;
        u32           count;
    };

    void vector_class_array_init    (vector_class_array& vec_array, const buffer& buf);
    void vector_class_array_destroy (vector_class_array& vec_array);
    void vector_class_array_process (vector_class_array& vec_array);
};

#endif //DOD_HPP

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
};

#endif //DOD_HPP

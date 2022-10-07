//
// Created by maart on 4/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_AVX_H
#define I_COMPUTERGRAPHICS_AVX_H


#include <immintrin.h>

#ifndef SSE_AVX_EXTENSIONS
#define SSE_AVX_EXTENSIONS true
#endif
#define SET_DATA (true && SSE_AVX_EXTENSIONS)

#endif //I_COMPUTERGRAPHICS_AVX_H

//
// Created by maart on 4/10/2022.
//

#ifndef I_COMPUTERGRAPHICS_AVX_H
#define I_COMPUTERGRAPHICS_AVX_H


#include <immintrin.h>

#ifndef SSE_AVX_EXTENSIONS
#define SSE_AVX_EXTENSIONS false
#endif
#define SET_DATA (false && SSE_AVX_EXTENSIONS)

#endif //I_COMPUTERGRAPHICS_AVX_H

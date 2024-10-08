#ifndef GOL_H
#define GOL_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

    struct Cell {
        unsigned int species;
        float r;
        float g;
        float b;
    };

    typedef struct Cell Cell;

    extern const Cell golSpeciesSources[3];
    extern const Cell golDead;

    void golInit(unsigned int width, unsigned int height);

    void golTick();

    void golRenderString(const char* message);

    Cell* golFetch(unsigned int x, unsigned int y);

    Cell* golFetchPrev(unsigned int x, unsigned int y);

#ifdef __cplusplus
}
#endif

#endif

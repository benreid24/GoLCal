#ifndef GOL_H
#define GOL_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef unsigned char Cell;

    void golInit(unsigned int width, unsigned int height);

    void golTick();

    void golRenderString(const char* message);

    Cell* golFetch(unsigned int x, unsigned int y);

    Cell* golFetchPrev(unsigned int x, unsigned int y);

#ifdef __cplusplus
}
#endif

#endif

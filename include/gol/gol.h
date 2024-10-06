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

    Cell* golFetch(unsigned int x, unsigned int y);

#ifdef __cplusplus
}
#endif

#endif

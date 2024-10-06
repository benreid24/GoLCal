#include <gol/gol.h>

#include <cstring>

Cell* golCells         = NULL;
Cell* golPrevCells     = NULL;
unsigned int golWidth  = 0;
unsigned int golHeight = 0;

Cell* golFetch(unsigned int x, unsigned int y) { return &golCells[y * golWidth + x]; }

Cell* golFetchPrev(unsigned int x, unsigned int y) { return &golPrevCells[y * golWidth + x]; }

void golInit(unsigned int width, unsigned int height) {
    if (golCells) {
        free(golCells);
        free(golPrevCells);
    }

    const unsigned int len = width * height * sizeof(Cell);
    golCells               = malloc(len);
    golPrevCells           = malloc(len);
    memset(golCells, 0, len);
    memset(golPrevCells, 0, len);
    golWidth  = width;
    golHeight = height;

    // TODO - think about how to init cells with text rendering & remove this
    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            if ((x % 2) != (y % 2)) { *golFetch(x, y) = 1; }
        }
    }
}

void golTick() {
    // TODO - run one iteration step of GoL on golCells

    // swap cells
    Cell* tmp    = golCells;
    golCells     = golPrevCells;
    golPrevCells = tmp;
}

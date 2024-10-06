#include <gol/gol.h>

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
    golCells     = malloc(width * height * sizeof(Cell));
    golPrevCells = malloc(width * height * sizeof(Cell));
    golWidth     = width;
    golHeight    = height;

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

#include <deko3d.h>

void initDeko(uint32_t fbH, uint32_t fbW, uint32_t initialVBOSize, uint32_t VBOAlign, uint32_t initialIBOSize, uint32_t IBOAlign);
void exitDeko();
void render();
void drawElements();
void newFrame();
void commitVb(const void* data, uint32_t size, uint32_t alignment);
void allocVb(uint32_t size, uint32_t alignment);
void allocIb(uint32_t size, uint32_t alignment);
void commitIb(const void* data, uint32_t size, uint32_t alignment, int count);
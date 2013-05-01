#ifndef CUBE_H
#define CUBE_H

#include "object3d.h"

class Cube : public Object3D
{
public:
    Cube();
    ~Cube();

    virtual void draw();
};

#endif // CUBE_H

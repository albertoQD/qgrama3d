#include "cube.h"
#include <QtOpenGL>


Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::draw()
{
    glColor3f(color.redF(), color.greenF(), color.blueF());
    float npointX = ( length.x()/2 );
    float npointY = ( length.y()/2 );
    float npointZ = ( length.z()/2 );

    glBegin(GL_QUADS);

        glVertex3f( +npointX, +npointY, -npointZ);          // Top Right Of The Quad (Top)
        glVertex3f( -npointX, +npointY, -npointZ);          // Top Left Of The Quad (Top)
        glVertex3f( -npointX, +npointY, +npointZ);          // Bottom Left Of The Quad (Top)
        glVertex3f( +npointX, +npointY, +npointZ);          // Bottom Right Of The Quad (Top)

        glVertex3f( +npointX, -npointY, +npointZ);          // Top Right Of The Quad (Bottom)
        glVertex3f( -npointX, -npointY, +npointZ);          // Top Left Of The Quad (Bottom)
        glVertex3f( -npointX, -npointY, -npointZ);          // Bottom Left Of The Quad (Bottom)
        glVertex3f( +npointX, -npointY, -npointZ);          // Bottom Right Of The Quad (Bottom)

        glVertex3f( +npointX, +npointY, +npointZ);          // Top Right Of The Quad (Front)
        glVertex3f( -npointX, +npointY, +npointZ);          // Top Left Of The Quad (Front)
        glVertex3f( -npointX, -npointY, +npointZ);          // Bottom Left Of The Quad (Front)
        glVertex3f( +npointX, -npointY, +npointZ);          // Bottom Right Of The Quad (Front)

        glVertex3f( +npointX, -npointY, -npointZ);          // Bottom Left Of The Quad (Back)
        glVertex3f( -npointX, -npointY, -npointZ);          // Bottom Right Of The Quad (Back)
        glVertex3f( -npointX, +npointY, -npointZ);          // Top Right Of The Quad (Back)
        glVertex3f( +npointX, +npointY, -npointZ);          // Top Left Of The Quad (Back)

        glVertex3f( -npointX, +npointY, +npointZ);          // Top Right Of The Quad (Left)
        glVertex3f( -npointX, +npointY, -npointZ);          // Top Left Of The Quad (Left)
        glVertex3f( -npointX, -npointY, -npointZ);          // Bottom Left Of The Quad (Left)
        glVertex3f( -npointX, -npointY, +npointZ);          // Bottom Right Of The Quad (Left)

        glVertex3f( +npointX, +npointY, -npointZ);          // Top Right Of The Quad (Right)
        glVertex3f( +npointX, +npointY, +npointZ);          // Top Left Of The Quad (Right)
        glVertex3f( +npointX, -npointY, +npointZ);          // Bottom Left Of The Quad (Right)
        glVertex3f( +npointX, -npointY, -npointZ);          // Bottom Right Of The Quad (Right)

    glEnd();
}

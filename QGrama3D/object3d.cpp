#include "object3d.h"
#include <QtOpenGL>
#include <GL/glut.h>

Object3D::Object3D()
    : center(0.0, 0.0, 0.0)
    , color(125, 0, 0)
    , length(1, 1, 1)
    , selected(false)
    , label("New Object3D")
{
}

Object3D::~Object3D()
{
}

void Object3D::setColor(QColor _color)
{
    color = _color;
}

QColor Object3D::getColor() const
{
    return color;
}

void Object3D::setCenter(QVector3D _center)
{
    center = _center;
}

QVector3D Object3D::getCenter() const
{
    return center;
}

void Object3D::setLength(QVector3D _length)
{
    length = _length;
}

QVector3D Object3D::getLength() const
{
    return length;
}

void Object3D::drawSelected()
{
    float npointX = ( length.x()/2 ) + 0.03;
    float npointY = ( length.y()/2 ) + 0.03;
    float npointZ = ( length.z()/2 ) + 0.03;
    float x = (float) center.x();
    float y = (float) center.y();
    float z = (float) center.z();

    glDisable(GL_LIGHTING);
    glLineWidth(1.5);
    glBegin(GL_LINES);
        // FRONT
        glVertex3f( x+npointX, y-npointY, z+npointZ );
        glVertex3f( x+npointX, y+npointY, z+npointZ );

        glVertex3f( x-npointX, y+npointY, z+npointZ );
        glVertex3f( x-npointX, y-npointY, z+npointZ );

        glVertex3f( x+npointX, y-npointY, z+npointZ );
        glVertex3f( x-npointX, y-npointY, z+npointZ );

        glVertex3f( x+npointX, y+npointY, z+npointZ );
        glVertex3f( x-npointX, y+npointY, z+npointZ );

        // BACK

        glVertex3f( x+npointX, y-npointY, z-npointZ );
        glVertex3f( x+npointX, y+npointY, z-npointZ );

        glVertex3f( x-npointX, y+npointY, z-npointZ );
        glVertex3f( x-npointX, y-npointY, z-npointZ );

        glVertex3f( x+npointX, y-npointY, z-npointZ );
        glVertex3f( x-npointX, y-npointY, z-npointZ );

        glVertex3f( x+npointX, y+npointY, z-npointZ );
        glVertex3f( x-npointX, y+npointY, z-npointZ );

        // LEFT
        glVertex3f( x-npointX, y+npointY, z-npointZ );
        glVertex3f( x-npointX, y+npointY, z+npointZ );

        glVertex3f( x-npointX, y-npointY, z-npointZ );
        glVertex3f( x-npointX, y-npointY, z+npointZ );

        // RIGHT
        glVertex3f( x+npointX, y+npointY, z-npointZ );
        glVertex3f( x+npointX, y+npointY, z+npointZ );

        glVertex3f( x+npointX, y-npointY, z-npointZ );
        glVertex3f( x+npointX, y-npointY, z+npointZ );

    glEnd();

    glEnable(GL_LIGHTING);
    glLineWidth(1.0);
}

void Object3D::drawAxis()
{
    float npointX = ( length.x() *2 ) + 0.03;
    float npointY = ( length.y() *2 ) + 0.03;
    float npointZ = ( length.z() *2 ) + 0.03;
    float x = (float) center.x();
    float y = (float) center.y();
    float z = (float) center.z();

    glDisable(GL_LIGHTING);
    glLineWidth(2.0);
    glBegin(GL_LINES); // X axe
        glVertex3f( x, y, z );
        glVertex3f( x + npointX, y, z);
    glEnd();
    glBegin(GL_TRIANGLE_FAN); // the piramid for the arrow
        glVertex3f( x+npointX + 0.08, y, z ); // top of the piramid
        glVertex3f( x+npointX, y, z + 0.08 );
        glVertex3f( x+npointX, y - 0.08, z );
        glVertex3f( x+npointX, y, z - 0.08 );
        glVertex3f( x+npointX, y + 0.08, z );
        glVertex3f( x+npointX, y, z + 0.08 );
    glEnd();

    glBegin(GL_LINES); // Y axe
        glVertex3f( x, y, z );
        glVertex3f( x , y + npointY, z );
    glEnd();
    glBegin(GL_TRIANGLE_FAN); // the piramid for the arrow
        glVertex3f( x, y + npointY + 0.08, z ); // top of the piramid
        glVertex3f( x, y+npointY, z + 0.08 );
        glVertex3f( x + 0.08, y+npointY, z );
        glVertex3f( x, y+npointY, z - 0.08 );
        glVertex3f( x - 0.08, y+npointY, z );
        glVertex3f( x, y+npointY, z + 0.08 );
    glEnd();

    glBegin(GL_LINES); // Z axe
        glVertex3f( x, y, z );
        glVertex3f( x , y, z + npointZ );
    glEnd();
    glBegin(GL_TRIANGLE_FAN); // the piramid for the arrow
        glVertex3f( x, y, z + npointZ + 0.08 ); // top of the piramid
        glVertex3f( x - 0.08, y, z + npointZ );
        glVertex3f( x, y - 0.08, z + npointZ );
        glVertex3f( x + 0.08, y, z + npointZ );
        glVertex3f( x, y + 0.08, z + npointZ );
        glVertex3f( x - 0.08, y, z + npointZ );
    glEnd();

    glEnable(GL_LIGHTING);
    glLineWidth(1.0);
}

void Object3D::select()
{
    selected = true;
}

void Object3D::unselect()
{
    selected = false;
}

bool Object3D::isSelected()
{
    return selected;
}

QString Object3D::getLabel() const
{
    return label;
}

void Object3D::setLabel(QString _label)
{
    label = _label;
}

void Object3D::drawLabel()
{
    glDisable(GL_LIGHTING);
    glRasterPos3f(center.x() - (length.x()/2) , center.y() + (length.y()/2), center.z() + (length.z()/2) + 0.08);
    for (int i=0; i<label.size(); i+=1)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label.toStdString().c_str()[i]);
    }
    glEnable(GL_LIGHTING);
}

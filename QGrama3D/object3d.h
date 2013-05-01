#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <QColor>
#include <QVector3D>
#include <QSize>

class Object3D
{
public:
    Object3D();
    ~Object3D();

    void setColor(QColor);
    QColor getColor() const;
    virtual void setCenter(QVector3D);
    QVector3D getCenter() const;
    void setLength(QVector3D);
    QVector3D getLength() const;
    bool isSelected();
    void select();
    void unselect();
    QString getLabel() const;
    void setLabel(QString _label);

    virtual void draw() = 0;

    void drawSelected();
    void drawAxis();
    void drawLabel();

protected:
    QVector3D center;
    QColor color;
    QVector3D length;
    bool selected;
    QString label;
};

#endif // OBJECT3D_H

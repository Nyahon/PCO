#ifndef CALCULTHREAD_H
#define CALCULTHREAD_H

#include <QtWidgets>
#include <math.h>
#include <QImage>
#include <QThread>
#include "renderthread.h"
//Test
#define ColormapSize 512 // RenderThread::ColormapSize
class calculthread : public QThread
{
public:
    calculthread(bool *restart, bool *abort,
                 int pass, const int NumPasses, const int Limit, const int MaxIterations,
                 double centerX, double centerY,
                 double halfHeight, double halfWidth, double scaleFactor,
                 uint* colormap, QImage &image);


public:
    void run();

private:
    bool* restart;
    bool* abort;
    int pass;
    const int NumPasses, Limit, MaxIterations;
    double centerX, centerY,
            halfHeight, halfWidth,
            scaleFactor;
    uint* colormap;
    QImage &image;
};
#endif // CALCULTHREAD_H

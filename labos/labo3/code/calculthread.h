#ifndef CALCULTHREAD_H
#define CALCULTHREAD_H

#include <QtWidgets>
#include <math.h>
#include <QImage>
#include <QThread>
#include "renderthread.h"
//Test
#define ColormapSize 512 // RenderThread::ColormapSize

/*
 * This class implements the mathematical operations allowing the render of the mandelbrot courbe,
 * using the equation Z_n+1 = Z_n + C. The coloration is done accordingly to the number of passes (pass)
 * necessary for the point to go outside the radius predefined (Limit).
 * It allow the calculations to be parallelized in differents QThreads.
 */
class calculthread : public QThread
{
public:
    /*
     * this constructor as pour only task the initialisation of the differents parameter necessary to
     * do the maths. restart and abort are passed by pointer to allow the modification of them by
     * the controller to be applied to the runnings threads.
     * Qimage contains the image we print.
     */
    calculthread(bool *restart, bool *abort,
                 int pass, const int NumPasses, const int Limit, const int MaxIterations, const int pos, const int coresNumber,
                 double centerX, double centerY,
                 double halfHeight, double halfWidth, double scaleFactor,
                 uint* colormap, QImage &image);


public:
    void run();

private:
    bool* restart; //true if the user zooms or move
    bool* abort; //tue if we want to quit the thread
    int pass; // the current #pass (the higher the more precise render)
    const int NumPasses, Limit, MaxIterations, pos; // the values defining the precision of the render
    double centerX, centerY, //the differents values necessary for the calcul.
            halfHeight, halfWidth,
            scaleFactor,
            coresNumber;
    uint* colormap;
    QImage &image;
};
#endif // CALCULTHREAD_H

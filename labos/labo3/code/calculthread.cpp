#include "calculthread.h"
#include <iostream>

using namespace std;
/*
 * Render logic (T_Ni)
 * Need:
 *  bool restart
 *  bool abort
 *  int pass
 *  const int NumPasses
 *  const int Limit
 *  double centerX
 *  double centerY
 *  double halfHeight
 *  double halfWidth
 *  QImage
 */
calculthread::calculthread(bool *restart, bool *abort,
                           int pass, const int NumPasses, const int Limit, const int MaxIterations, const int pos, const int coresNumber,
                           double centerX, double centerY, double halfHeight, double halfWidth, double scaleFactor,
                           uint* colormap, QImage& image) :

                           restart(restart), abort(abort),
                           pass(pass), NumPasses(NumPasses), Limit(Limit), MaxIterations(MaxIterations), pos(pos), coresNumber(coresNumber),
                           centerX(centerX), centerY(centerY),  halfHeight(halfHeight), halfWidth(halfWidth), scaleFactor(scaleFactor),
                           colormap(colormap), image(image){

}


void calculthread::run(){

    //we start on the first line for the first thread, second for the second thread, ...
    //we increment by the number of running threads, which make each thread render L/N lines
    //of the image.
    for (int y = -halfHeight +pos; y < halfHeight  ; y=y+coresNumber) {
        if (*restart)
            break;
        if (*abort)
            return;

        //=====================MATH LOGIC=================================
        QRgb *scanLine = // + halfheight is here to normalize the value of the line (get it >=0)
                reinterpret_cast<QRgb *>(image.scanLine( y + halfHeight ));
        double ay =  centerY + ( y * scaleFactor) ;
        for (int x = -halfWidth; x < halfWidth; ++x) {
            double ax = centerX + (x * scaleFactor);
            double a1 = ax;
            double b1 = ay;
            int numIterations = 0;

            do {
                ++numIterations;
                double a2 = (a1 * a1) - (b1 * b1) + ax;
                double b2 = (2 * a1 * b1) + ay;
                if ((a2 * a2) + (b2 * b2) > Limit)
                    break;

                ++numIterations;
                a1 = (a2 * a2) - (b2 * b2) + ax;
                b1 = (2 * a2 * b2) + ay;
                if ((a1 * a1) + (b1 * b1) > Limit)
                    break;
            } while (numIterations < MaxIterations);

            //print the resulting calculations in image
            if (numIterations < MaxIterations) {
                *scanLine++ = colormap[numIterations % ColormapSize];
            } else {
                *scanLine++ = qRgb(0, 0, 0);
            }
        }
    }
    return;

}



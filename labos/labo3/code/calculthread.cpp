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
     //std::cout << "pos: " << pos << std::endl;
    //START THREAD LOGIC
    for (int y = -halfHeight +pos; y < halfHeight  ; y=y+coresNumber) {
        if (*restart)
            break;
        if (*abort)
            return;

        QRgb *scanLine =
                reinterpret_cast<QRgb *>(image.scanLine( y + halfHeight ));
        double ay =  centerY + ( y * scaleFactor) ; //-centerY almost work
       // ay = ay - centerX;
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

            if (numIterations < MaxIterations) {
                *scanLine++ = colormap[numIterations % ColormapSize];
            } else {
                *scanLine++ = qRgb(0, 0, 0);
            }
        }
    }
    return;

}



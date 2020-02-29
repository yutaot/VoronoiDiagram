/**
* @file vor.cpp
* Implementation of functions in the filler namespace.
*
*/
//included within  "vor.h" for template instantiation


/* vorDotDFS given as an example for PA2 */
animation filler::vorDotDFS(PNG& img, double density,
  int dotGrid,int dotSize, int frameFreq)
  {
    dotColorPicker a(dotGrid,dotSize);
    return vor<Stack>(img, density, a, frameFreq);
  }

  animation filler::vorSolidDFS(PNG& img, double density, int frameFreq)
  {
    /**
    * @todo Your code here!
    */
    solidColorPicker a;
    return vor<Stack>(img, density, a, frameFreq);
  }

  animation filler::vorFadeDFS(PNG& img, double density, double fadeFactor, int frameFreq)
  {
    /**
    * @todo Your code here!
    */
    fadeColorPicker a(fadeFactor);
    return vor<Stack>(img, density, a, frameFreq);
  }


  /* vorDotBFS given as an example for PA2 */
  animation filler::vorDotBFS(PNG& img, double density,
    int dotGrid,int dotSize, int frameFreq)
    {
      dotColorPicker a(dotGrid, dotSize);
      return vor<Queue>(img, density, a, frameFreq);
    }

    animation filler::vorSolidBFS(PNG& img, double density, int frameFreq)
    {
      /**
      * @todo Your code here!
      */
      solidColorPicker a;
      return vor<Queue>(img, density, a, frameFreq);
    }

    animation filler::vorFadeBFS(PNG& img, double density, double fadeFactor, int frameFreq)
    {
      /**
      * @todo Your code here!
      */
      fadeColorPicker a(fadeFactor);
      return vor<Queue>(img, density, a, frameFreq);
    }

    animation filler::vorCustomDFS(PNG& img, double density, int frameFreq)
    {
        /**
         * @todo Your code here!
         */
         customColorPicker a;
         return vor<Stack>(img, density, a, frameFreq);
    }

    animation filler::vorCustomBFS(PNG& img, double density, int frameFreq)
    {
        /**
         * @todo Your code here!
         */
         customColorPicker a;
         return vor<Queue>(img, density, a, frameFreq);
    }


    template <template <class T> class OrderingStructure>
    animation filler::vor(PNG& img, double density, colorPicker& fillColor,
      int frameFreq)
      {

        /**
        * @todo You need to implement this function!
        *
        * This is a general description of a space filling algorithm, where
        * the space is partitioned into a set of regions each color of which
        * is determined by the color of a point
        * chosen from an original image. We call those original points
        * "centers." (See pictures in the specification.)
        *
        * The algorithm requires ordering structures used to orchestrate
        * the sequence of points filled. This structure type info is passed to the
        * fill algorithm via its template parameter. For a breadth-first fill,
        * we use Queues, and for a depth-first fill, we use Stacks. Function
        * vorDotDFS provides an example call to function vor.
        *
        * The algorithm includes the following steps:
        * 1) you will first select a random set
        * of coordinates (and their colors) to use as centers from which to
        * begin the fill. (this function is in file vor_given.cpp -- for
        * testing purposes, you'll use regularly spaced points, rather than
        * random.)
        * 2) Initialize a structure to use to maintain a collection of
        * ordering structures
        *
        * 3) Initialize the fill: For each center c, in round-robin order,
        *     do the following:
        *     a)  add the center to its ordering structure. (every center
        *         its own!
        *     b)  mark the location of that center as processed (the way you
        *         do this is up to you!)
        *     c)  we have a choice to actually set the color of the pixel in
        *         the fill when we add or when we remove. In our test cases,
        *         we assume that you will change a color when a point is
        *         added to a structure. (this is mostly relevant for checking
        *         the animations.)
        *
        * 5) Complete the fill: Until all ordering structures (OS) are empty,
        *    do the following for each OS, in a round robin order, indexing
        *    the iterations by k (an integer distance from the center):
        *
        *      For each point less than or equal to distance k from its center:
        *      a)Remove the  point p from the ordering structure, and then...
        *
        *        i.    add p's unprocessed neighbors to the ordering structure if
        *              they are within the appropriate distance from the center. We
        *              describe this more carefully below. We call these the "valid"
        *              neighbors.
        *        ii.    use the colorPicker to set the new color of the valid neighbors.
        *        iii.    mark the valid neighbors as processed.
        *        iv.    as each neighbor is processed, if it is an appropriate
        *              frame, send the current PNG to the
        *              animation (as described below).
        *
        *      b) When implementing your breadth-first and depth-first fills,
        *            you will need to explore neighboring pixels in some order.
        *
        *        For this assignment, each pixel p has *up to* 8 neighbors, consisting of
        *        the 8 pixels who share an edge with p. (We leave it to
        *        you to describe those 8 pixel locations, relative to the location
        *        of p.)
        *
        *        While the order in which you examine neighbors does not matter
        *        for a proper fill, you must use the same order as we do for
        *        your animations to come out like ours!
        *
        *        The order you should put
        *        neighboring pixels **ONTO** the queue or stack is as follows:
        *        ** UP(-y), UPLEFT(-x,-y), LEFT(-x), LEFTDOWN(-x,+y), DOWN(+y),
        *        DOWNRIGHT(+x,+y), RIGHT(+x), RIGHTUP(+x,-y)**
        *
        *        If you do them in a different order, your fill may
        *        still work correctly, but your animations will be different
        *        from the grading scripts!
        *
        *        TWO IMPORTANT NOTES:
        *        1) *UP* here means towards the top of the image, so since an image has
        *        smaller y coordinates at the top, this is in the *negative y*
        *        direction. Similarly, *DOWN* means in the *positive y*
        *        direction.
        *        2) not all of the 8 neighbors will be processed at every iteration of the
        *        while loop. You must assure that all vertices distance k or less
        *        from the center are processed (colored and put on the queue) before
        *        ANY whose distance is *greater than* k. k is a non-negative integer.
        *        Finally, distance is the standard Euclidean distance  (computed
        *        using the Pythagorean theorem). It is this requirement that assures
        *        that the fill grows outward from the center in the shape of a circle,
        *        rather than a diamond or a square.
        *
        *      c) For every g pixels filled, **starting at the gth pixel**, you
        *        must add a frame to the animation, where g = frameFreq.
        *
        *        For example, if frameFreq is 4, then after the 4th pixel has
        *        been filled you should add a frame to the animation, then again
        *        after the 8th pixel, etc.  You must only add frames for the
        *        number of pixels that have been filled, not the number that
        *        have been checked. So if frameFreq is set to 1, a pixel should
        *        be filled every frame.
        *      d) Finally, as you leave the function, send one last frame to the
        *        animation. This frame will be the final result of the fill, and
        *        it will be the one we test against.
        */



        /* Your code here. As a point of reference, we used three different helper
        * functions to complete this code. You may add as many as you wish, since
        * we will be grading vor.h. File "vor_given.cpp also includes the function
        * used to generate the original set of centers.
        */

        animation anim;

        int height = img.height();
        int width = img.width();

        PNG dummyPNG(width, height);

        vector<center> setOfCoor = randSample(img, density);
        vector<OrderingStructure<point>> collectionOfOS;
        collectionOfOS.resize(setOfCoor.size());

        // for (int i = 0; i < setOfCoor.size(); i++) {
        //   OrderingStructure<point> os;
        //   collectionOfOS.push_back(os);
        // }

        vector<vector<bool>> processed;
        // processed.resize(width);
        for (int i = 0; i < width + 1; i++) {
          vector<bool> vector;
          for (int j = 0; j < height + 1; j++) {
            vector.push_back(false);
          }
          processed.push_back(vector);
        }

        int g = 0;

        for (int i = 0; i < setOfCoor.size(); i++) {
          // setOfCoor[i].color = *(img.getPixel(setOfCoor[i].x, setOfCoor[i].y));
          point centerPoint = point(setOfCoor[i]);
          // point p(setOfCoor[i]);
          if (processed[centerPoint.x][centerPoint.y]) {
            continue;
          }
          processed[centerPoint.x][centerPoint.y] = true;
          HSLAPixel cPixel = fillColor(centerPoint);
          HSLAPixel * centerPixel = img.getPixel(centerPoint.x, centerPoint.y);
          * centerPixel = cPixel;
          // setOfCoor[i].color = fillColor(centerPoint); // may not need

          HSLAPixel * p = dummyPNG.getPixel(centerPoint.x, centerPoint.y);
          * p = cPixel;

          collectionOfOS[i].add(centerPoint);
          g++;
          if (g % frameFreq == 0) {
            anim.addFrame(dummyPNG);
          }
        }

        while (!isAllEmpty(collectionOfOS)) {
          for (int i = 0; i < collectionOfOS.size(); i++) {

            if (collectionOfOS[i].isEmpty()) {
              continue;
            }

            int currLevel = collectionOfOS[i].peek().level;

            while (!collectionOfOS[i].isEmpty() && collectionOfOS[i].peek().level == currLevel) {

              point currPoint = collectionOfOS[i].remove();

              if (withInImg(currPoint.x, currPoint.y - 1, height, width)) {
                point upPoint = point(currPoint.x, currPoint.y - 1, currPoint.c, currPoint.level + 1);
                if (processed[upPoint.x][upPoint.y] == false && distC(upPoint.x, upPoint.y, upPoint.c) <= currPoint.level + 1) {
                  processed[upPoint.x][upPoint.y] = true;
                  HSLAPixel fillcolor = fillColor(upPoint);
                  // HSLAPixel * upPointPixel = img.getPixel(upPoint.x, upPoint.y);
                  // * upPointPixel = fillcolor;
                  collectionOfOS[i].add(upPoint);

                  HSLAPixel * p = dummyPNG.getPixel(upPoint.x, upPoint.y);
                  * p = fillcolor;

                  g++;
                  if (g % frameFreq == 0) {
                    anim.addFrame(dummyPNG);
                  }
                }
              }

              if (withInImg(currPoint.x - 1, currPoint.y - 1, height, width)) {
                point upLeftPoint = point(currPoint.x - 1, currPoint.y - 1, currPoint.c, currPoint.level + 1);
                if (processed[upLeftPoint.x][upLeftPoint.y] == false && distC(upLeftPoint.x, upLeftPoint.y, upLeftPoint.c) <= currPoint.level + 1) {
                  processed[upLeftPoint.x][upLeftPoint.y] = true;
                  HSLAPixel fillcolor = fillColor(upLeftPoint);
                  // HSLAPixel * upLeftPointPixel = img.getPixel(upLeftPoint.x, upLeftPoint.y);
                  // * upLeftPointPixel = fillcolor;
                  collectionOfOS[i].add(upLeftPoint);

                  HSLAPixel * p = dummyPNG.getPixel(upLeftPoint.x, upLeftPoint.y);
                  * p = fillcolor;

                  g++;
                  if (g % frameFreq == 0) {
                    anim.addFrame(dummyPNG);
                  }
                }
              }

              if (withInImg(currPoint.x - 1, currPoint.y, height, width)) {
                point leftPoint = point(currPoint.x - 1, currPoint.y, currPoint.c, currPoint.level + 1);
                if (processed[leftPoint.x][leftPoint.y] == false && distC(leftPoint.x, leftPoint.y, leftPoint.c) <= currPoint.level + 1) {
                  processed[leftPoint.x][leftPoint.y] = true;
                  HSLAPixel fillcolor = fillColor(leftPoint);
                  // HSLAPixel * leftPointPixel = img.getPixel(leftPoint.x, leftPoint.y);
                  // * leftPointPixel = fillcolor;
                  collectionOfOS[i].add(leftPoint);

                  HSLAPixel * p = dummyPNG.getPixel(leftPoint.x, leftPoint.y);
                  * p = fillcolor;

                  g++;
                  if (g % frameFreq == 0) {
                    anim.addFrame(dummyPNG);
                  }
                }
              }

              if (withInImg(currPoint.x - 1, currPoint.y + 1, height, width)) {
                point leftDownPoint = point(currPoint.x - 1, currPoint.y + 1, currPoint.c, currPoint.level + 1);
                if (processed[leftDownPoint.x][leftDownPoint.y] == false && distC(leftDownPoint.x, leftDownPoint.y, leftDownPoint.c) <= currPoint.level + 1) {
                  processed[leftDownPoint.x][leftDownPoint.y] = true;
                  HSLAPixel fillcolor = fillColor(leftDownPoint);
                  // HSLAPixel * leftDownPointPixel = img.getPixel(leftDownPoint.x, leftDownPoint.y);
                  // * leftDownPointPixel = fillcolor;
                  collectionOfOS[i].add(leftDownPoint);

                  HSLAPixel * p = dummyPNG.getPixel(leftDownPoint.x, leftDownPoint.y);
                  * p = fillcolor;

                  g++;
                  if (g % frameFreq == 0) {
                    anim.addFrame(dummyPNG);
                  }
                }
              }

              if (withInImg(currPoint.x, currPoint.y + 1, height, width)) {
                point downPoint = point(currPoint.x, currPoint.y + 1, currPoint.c, currPoint.level + 1);
                if (processed[downPoint.x][downPoint.y] == false && distC(downPoint.x, downPoint.y, downPoint.c) <= currPoint.level + 1) {
                  processed[downPoint.x][downPoint.y] = true;
                  HSLAPixel fillcolor = fillColor(downPoint);
                  // HSLAPixel * downPointPixel = img.getPixel(downPoint.x, downPoint.y);
                  // * downPointPixel = fillcolor;
                  collectionOfOS[i].add(downPoint);

                  HSLAPixel * p = dummyPNG.getPixel(downPoint.x, downPoint.y);
                  * p = fillcolor;

                  g++;
                  if (g % frameFreq == 0) {
                    anim.addFrame(dummyPNG);
                  }
                }
              }

              if (withInImg(currPoint.x + 1, currPoint.y + 1, height, width)) {
                point downRightPoint = point(currPoint.x + 1, currPoint.y + 1, currPoint.c, currPoint.level + 1);
                if (processed[downRightPoint.x][downRightPoint.y] == false && distC(downRightPoint.x, downRightPoint.y, downRightPoint.c) <= currPoint.level + 1) {
                  processed[downRightPoint.x][downRightPoint.y] = true;
                  HSLAPixel fillcolor = fillColor(downRightPoint);
                  // HSLAPixel * downRightPointPixel = img.getPixel(downRightPoint.x, downRightPoint.y);
                  // * downRightPointPixel = fillcolor;
                  collectionOfOS[i].add(downRightPoint);

                  HSLAPixel * p = dummyPNG.getPixel(downRightPoint.x, downRightPoint.y);
                  * p = fillcolor;

                  g++;
                  if (g % frameFreq == 0) {
                    anim.addFrame(dummyPNG);
                  }
                }
              }

              if (withInImg(currPoint.x + 1, currPoint.y, height, width)) {
                point rightPoint = point(currPoint.x + 1, currPoint.y, currPoint.c, currPoint.level + 1);
                if (processed[rightPoint.x][rightPoint.y] == false && distC(rightPoint.x, rightPoint.y, rightPoint.c) <= currPoint.level + 1) {
                  processed[rightPoint.x][rightPoint.y] = true;
                  HSLAPixel fillcolor = fillColor(rightPoint);
                  // HSLAPixel * rightPointPixel = img.getPixel(rightPoint.x, rightPoint.y);
                  // * rightPointPixel = fillcolor;
                  collectionOfOS[i].add(rightPoint);

                  HSLAPixel * p = dummyPNG.getPixel(rightPoint.x, rightPoint.y);
                  * p = fillcolor;

                  g++;
                  if (g % frameFreq == 0) {
                    anim.addFrame(dummyPNG);
                  }
                }
              }

              if (withInImg(currPoint.x + 1, currPoint.y - 1, height, width)) {
                point rightUpPoint = point(currPoint.x + 1, currPoint.y - 1, currPoint.c, currPoint.level + 1);
                if (processed[rightUpPoint.x][rightUpPoint.y] == false && distC(rightUpPoint.x, rightUpPoint.y, rightUpPoint.c) <= currPoint.level + 1) {
                  processed[rightUpPoint.x][rightUpPoint.y] = true;
                  HSLAPixel fillcolor = fillColor(rightUpPoint);
                  // HSLAPixel * rightUpPointPixel = img.getPixel(rightUpPoint.x, rightUpPoint.y);
                  // * rightUpPointPixel = fillcolor;
                  collectionOfOS[i].add(rightUpPoint);

                  HSLAPixel * p = dummyPNG.getPixel(rightUpPoint.x, rightUpPoint.y);
                  * p = fillcolor;

                  g++;
                  if (g % frameFreq == 0) {
                    anim.addFrame(dummyPNG);
                  }
                }
              }
            }
          }
        }
        img = dummyPNG;
        anim.addFrame(dummyPNG);
        return anim;
      }

      bool filler::withInImg(int x, int y, int height, int width) {
        return (0 <= x && x < width && 0 <= y && y < height);
      }

      double filler::distC(int x, int y, center c) {
        int centerX = c.x;
        int centerY = c.y;
        return sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
      }

      template <template <class T> class OrderingStructure>
      bool filler::isAllEmpty(vector<OrderingStructure<point>> vector) {
        for (int i = 0; i < vector.size(); i++) {
          if (!vector[i].isEmpty()) {
            return false;
          }
        }
        return true;
      }

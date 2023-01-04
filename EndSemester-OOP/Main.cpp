#include "Util.h"


void run(int stage) {
    VideoCapture video(0);
    Mat frame;
    video.set(3, 1280);
    video.set(4, 720);

    while (true)
    {
#pragma omp parallel 
        {
#pragma omp task1 
            {
                video.read(frame);
                Util::temp = frame;

            }
#pragma omp task2 
            {
                switch (stage) 
                {
                case 1:
                    Util::image = Util::addContour(Util::temp); break;
                case 2:
                    Util::image = Util::detectCircle(Util::temp); break; 
                }

            }
        }

        imshow("img", Util::image);
        waitKey(10);
    }

}


void main() {



    Util::init();
    run(1);




}




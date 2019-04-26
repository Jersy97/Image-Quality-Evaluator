#include "brisque.h"

double psnr(Mat image_ref, Mat image_obj)
{
	Mat s1;
    absdiff(image_ref, image_obj, s1);       // |I1 - I2|
    s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
    s1 = s1.mul(s1);           // |I1 - I2|^2

    Scalar s = sum(s1);         // sum elements per channel

    double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels

    if( sse <= 1e-10) // for small values return zero
        return 0;
    else
    {
        double  mse =sse /(double)(image_ref.channels() * image_ref.total());
        double psnr = 10.0*log10((255*255)/mse);
        return psnr;
    }
}

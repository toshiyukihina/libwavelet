/*
   Copyright (c) 2009 Toshiyuki Hina

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

   $Id: wavelet_cs.h 8 2009-01-12 14:07:38Z t_hina777 $
*/

#ifndef __LIBWAVELET_WAVELET_CS_H__
#define __LIBWAVELET_WAVELET_CS_H__

BEGIN_NS_WAVELET

template <int begin, int end>
struct WaveletCS 
{
    enum 
    { 
        BEGIN = begin,
        END = end
    };

    static int Size() { return END - BEGIN + 1; }
};

#define GABOR2_CS_BEGIN (-5)
#define GABOR2_CS_END (5)
#define GABOR4_CS_BEGIN (-8)
#define GABOR4_CS_END (8)
#define GABOR8_CS_BEGIN (-18)
#define GABOR8_CS_END (18)
#define MEXICANHAT_CS_BEGIN (-4)
#define MEXICANHAT_CS_END (4)
#define FRENCHHAT_CS_BEGIN (-3)
#define FRENCHHAT_CS_END (3)
#define SHANNON_CS_BEGIN (-16)
#define SHANNON_CS_END (16)
#define HAAR_CS_BEGIN (0)
#define HAAR_CS_END (1)

typedef WaveletCS<GABOR2_CS_BEGIN, GABOR2_CS_END> CSGabor2;
typedef WaveletCS<GABOR4_CS_BEGIN, GABOR4_CS_END> CSGabor4;
typedef WaveletCS<GABOR8_CS_BEGIN, GABOR8_CS_END> CSGabor8;
typedef WaveletCS<MEXICANHAT_CS_BEGIN, MEXICANHAT_CS_END> CSMexicanHat;
typedef WaveletCS<FRENCHHAT_CS_BEGIN, FRENCHHAT_CS_END> CSFrenchHat;
typedef WaveletCS<SHANNON_CS_BEGIN, SHANNON_CS_END> CSShannon;
typedef WaveletCS<HAAR_CS_BEGIN, HAAR_CS_END> CSHaar;

END_NS_WAVELET

#endif /* __LIBWAVELET_WAVELET_CS_H__ */

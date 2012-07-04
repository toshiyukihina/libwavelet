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

   $Id: wavelet_functor.h 9 2009-01-12 14:10:00Z t_hina777 $
*/

#ifndef __LIBWAVELET_WAVELET_FUNCTOR_H__
#define __LIBWAVELET_WAVELET_FUNCTOR_H__

#include <vector>

BEGIN_NS_WAVELET

inline WaveletUnit<WAVELET_TYPE_GABOR2>::Unit
WaveletFunction(const double x, Int2Type<WAVELET_TYPE_GABOR2>) {
    typedef WaveletUnit<WAVELET_TYPE_GABOR2>::Unit Unit;
    double temp = std::exp(-x * x / 2.0 / 2.0);
    if (x > WTK_PI * 3 / 2 || x < -WTK_PI * 3 / 2)
        temp = 0.0;
    return Unit(temp * std::cos(x), -temp * std::sin(x));
}

inline WaveletUnit<WAVELET_TYPE_GABOR4>::Unit
WaveletFunction(const double x, Int2Type<WAVELET_TYPE_GABOR4>) {
    typedef WaveletUnit<WAVELET_TYPE_GABOR4>::Unit Unit;
    double temp = std::exp(-x * x / 4.0 / 4.0);
    if (x > WTK_PI * 5 / 2 || x < -WTK_PI * 5 / 2)
        temp = 0.0;
    return Unit(temp * std::cos(x), -temp * std::sin(x));
}

inline WaveletUnit<WAVELET_TYPE_GABOR8>::Unit
WaveletFunction(const double x, Int2Type<WAVELET_TYPE_GABOR8>) {
    typedef WaveletUnit<WAVELET_TYPE_GABOR8>::Unit Unit;
    double temp = std::exp(-x * x / 8.0 / 8.0);
    if (x > WTK_PI * 11 / 2 || x < -WTK_PI * 11 / 2)
        temp = 0.0;
    return Unit(temp * std::cos(x), -temp * std::sin(x));
}

inline WaveletUnit<WAVELET_TYPE_MEXICANHAT>::Unit
WaveletFunction(const double x, Int2Type<WAVELET_TYPE_MEXICANHAT>) {
    typedef WaveletUnit<WAVELET_TYPE_MEXICANHAT>::Unit Unit;
    Unit result = (1 - 2 * x * x) * std::exp(-x * x);
    return result;
}

inline WaveletUnit<WAVELET_TYPE_FRENCHHAT>::Unit
WaveletFunction(const double x, Int2Type<WAVELET_TYPE_FRENCHHAT>) {
    typedef WaveletUnit<WAVELET_TYPE_FRENCHHAT>::Unit Unit;
    Unit result;
    if (x >= -1.0 && x < 1.0) result = 1.0;
    else if (x >= -3.0 && x < -1.0) result = -0.5;
    else if (x >= 1.0 && x < 3.0) result = -0.5;
    else result = 0.0;
    return result;
}

inline WaveletUnit<WAVELET_TYPE_SHANNON>::Unit
WaveletFunction(const double x, Int2Type<WAVELET_TYPE_SHANNON>) {
    typedef WaveletUnit<WAVELET_TYPE_SHANNON>::Unit Unit;
    Unit result;
    if (x > WTK_PI * 5 || x < -WTK_PI * 5) result = 0.0;
    else if (x == 0.0) result = 1.0;
    else result = 2 * std::sin(WTK_PI * 2 * x) / (WTK_PI * 2 * x) - std::sin(WTK_PI * x) / (WTK_PI * x);
    return result;
}

inline WaveletUnit<WAVELET_TYPE_HAAR>::Unit
WaveletFunction(const double x, Int2Type<WAVELET_TYPE_HAAR>) {
    typedef WaveletUnit<WAVELET_TYPE_HAAR>::Unit Unit;
    Unit result;
    if (x >= 0.0 && x < 0.5) result = 1.0;
    else if (x >= 0.5 && x < 1.0) result = -1.0;
    else result = 0.0;
    return result;
}

struct FunctorBase {};

template <class _UnitType, class _CS>
struct WaveletFunctor : public FunctorBase
{
    typedef _UnitType UnitType;
    typedef typename _UnitType::Unit Unit;
    typedef typename _UnitType::Traits::UnitAggregator UnitAggregator;
    typedef _CS CS;

    void operator()(const double a, UnitAggregator& ua) {
        int begin = (int)(a * CS::BEGIN);
        int end = (int)(a * CS::END);
        int size = end - begin + 1;
        for (int i = 0; i < size; i++) {
            Unit u = WaveletFunction((begin + i) / a, Int2Type<UnitType::WAVELET_TYPE>());
            ua.push_back(u);
        }
    }
};

typedef WaveletFunctor<UnitGabor2, CSGabor2> FunctorGabor2;
typedef WaveletFunctor<UnitGabor4, CSGabor4> FunctorGabor4;
typedef WaveletFunctor<UnitGabor8, CSGabor8> FunctorGabor8;
typedef WaveletFunctor<UnitMexicanHat, CSMexicanHat> FunctorMexicanHat;
typedef WaveletFunctor<UnitFrenchHat, CSFrenchHat> FunctorFrenchHat;
typedef WaveletFunctor<UnitShannon, CSShannon> FunctorShannon;
typedef WaveletFunctor<UnitHaar, CSHaar> FunctorHaar;

END_NS_WAVELET

#endif // __LIBWAVELET_WAVELET_FUNCTOR_H__

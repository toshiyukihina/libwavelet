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

   $Id: wavelet_type.h 8 2009-01-12 14:07:38Z t_hina777 $
*/

#ifndef __LIBWAVELET_WAVELET_TYPE_H__
#define __LIBWAVELET_WAVELET_TYPE_H__

#include <complex>
#include <vector>

BEGIN_NS_WAVELET

enum WaveletType {
    WAVELET_TYPE_GABOR2 = 0,
    WAVELET_TYPE_GABOR4,
    WAVELET_TYPE_GABOR8,
    WAVELET_TYPE_MEXICANHAT,
    WAVELET_TYPE_FRENCHHAT,
    WAVELET_TYPE_SHANNON,
    WAVELET_TYPE_HAAR,
    WAVELET_TYPES
};

enum UnitType 
{
    UNIT_REAL,
    UNIT_COMPLEX,
    UNITS
};

template <UnitType>
struct UnitTraits;

template <>
struct UnitTraits<UNIT_REAL> {
    typedef double Unit;
    typedef std::vector<Unit> UnitAggregator;
};

template <>
struct UnitTraits<UNIT_COMPLEX> {
    typedef std::complex<double> Unit;
    typedef std::vector<Unit> UnitAggregator;
};

typedef UnitTraits<UNIT_REAL> TraitsReal;
typedef UnitTraits<UNIT_COMPLEX> TraitsComplex;


template <WaveletType>
struct WaveletUnit;

template <>
struct WaveletUnit<WAVELET_TYPE_GABOR2> {
    enum { WAVELET_TYPE = WAVELET_TYPE_GABOR2 };
    typedef UnitTraits<UNIT_COMPLEX> Traits;
    typedef Traits::Unit Unit;
};

template <>
struct WaveletUnit<WAVELET_TYPE_GABOR4> {
    enum { WAVELET_TYPE = WAVELET_TYPE_GABOR4 };
    typedef UnitTraits<UNIT_COMPLEX> Traits;
    typedef Traits::Unit Unit;
};

template <>
struct WaveletUnit<WAVELET_TYPE_GABOR8> {
    enum { WAVELET_TYPE = WAVELET_TYPE_GABOR8 };
    typedef UnitTraits<UNIT_COMPLEX> Traits;
    typedef Traits::Unit Unit;
};

template <>
struct WaveletUnit<WAVELET_TYPE_MEXICANHAT> {
    enum { WAVELET_TYPE = WAVELET_TYPE_MEXICANHAT };
    typedef UnitTraits<UNIT_REAL> Traits;
    typedef Traits::Unit Unit;
};

template <>
struct WaveletUnit<WAVELET_TYPE_FRENCHHAT> {
    enum { WAVELET_TYPE = WAVELET_TYPE_FRENCHHAT };
    typedef UnitTraits<UNIT_REAL> Traits;
    typedef Traits::Unit Unit;
};

template <>
struct WaveletUnit<WAVELET_TYPE_SHANNON> {
    enum { WAVELET_TYPE = WAVELET_TYPE_SHANNON };
    typedef UnitTraits<UNIT_REAL> Traits;
    typedef Traits::Unit Unit;
};

template <>
struct WaveletUnit<WAVELET_TYPE_HAAR> {
    enum { WAVELET_TYPE = WAVELET_TYPE_HAAR };
    typedef UnitTraits<UNIT_REAL> Traits;
    typedef Traits::Unit Unit;
};

typedef WaveletUnit<WAVELET_TYPE_GABOR2> UnitGabor2;
typedef WaveletUnit<WAVELET_TYPE_GABOR4> UnitGabor4;
typedef WaveletUnit<WAVELET_TYPE_GABOR8> UnitGabor8;
typedef WaveletUnit<WAVELET_TYPE_MEXICANHAT> UnitMexicanHat;
typedef WaveletUnit<WAVELET_TYPE_FRENCHHAT> UnitFrenchHat;
typedef WaveletUnit<WAVELET_TYPE_SHANNON> UnitShannon;
typedef WaveletUnit<WAVELET_TYPE_HAAR> UnitHaar;

END_NS_WAVELET

#endif // __LIBWAVELET_WAVELET_TYPE_H__

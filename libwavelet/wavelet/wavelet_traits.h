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

   $Id: wavelet_traits.h 8 2009-01-12 14:07:38Z t_hina777 $
*/

#ifndef __LIBWAVELET_WAVELET_TRAITS_H__
#define __LIBWAVELET_WAVELET_TRAITS_H__

BEGIN_NS_WAVELET

template <WaveletType>
struct WaveletTraits;

template <>
struct WaveletTraits<WAVELET_TYPE_GABOR2> {
    typedef Int2Type<WAVELET_TYPE_GABOR2> Tag;
    typedef WaveletUnit<WAVELET_TYPE_GABOR2> UnitType;
};

template <>
struct WaveletTraits<WAVELET_TYPE_GABOR4> {
    typedef Int2Type<WAVELET_TYPE_GABOR4> Tag;
    typedef WaveletUnit<WAVELET_TYPE_GABOR4> UnitType;
};

template <>
struct WaveletTraits<WAVELET_TYPE_GABOR8> {
    typedef Int2Type<WAVELET_TYPE_GABOR8> Tag;
    typedef WaveletUnit<WAVELET_TYPE_GABOR8> UnitType;
};

template <>
struct WaveletTraits<WAVELET_TYPE_MEXICANHAT> {
    typedef Int2Type<WAVELET_TYPE_MEXICANHAT> Tag;
    typedef WaveletUnit<WAVELET_TYPE_MEXICANHAT> UnitType;
};

template <>
struct WaveletTraits<WAVELET_TYPE_FRENCHHAT> {
    typedef Int2Type<WAVELET_TYPE_FRENCHHAT> Tag;
    typedef WaveletUnit<WAVELET_TYPE_FRENCHHAT> UnitType;
};

template <>
struct WaveletTraits<WAVELET_TYPE_SHANNON> {
    typedef Int2Type<WAVELET_TYPE_SHANNON> Tag;
    typedef WaveletUnit<WAVELET_TYPE_SHANNON> UnitType;
};

template <>
struct WaveletTraits<WAVELET_TYPE_HAAR> {
    typedef Int2Type<WAVELET_TYPE_HAAR> Tag;
    typedef WaveletUnit<WAVELET_TYPE_HAAR> UnitType;
};

typedef WaveletTraits<WAVELET_TYPE_GABOR2> TraitsGabor2;
typedef WaveletTraits<WAVELET_TYPE_GABOR4> TraitsGabor4;
typedef WaveletTraits<WAVELET_TYPE_GABOR8> TraitsGabor8;
typedef WaveletTraits<WAVELET_TYPE_MEXICANHAT> TraitsMexicanHat;
typedef WaveletTraits<WAVELET_TYPE_FRENCHHAT> TraitsFrenchHat;
typedef WaveletTraits<WAVELET_TYPE_SHANNON> TraitsShannon;
typedef WaveletTraits<WAVELET_TYPE_HAAR> TraitsHaar;


END_NS_WAVELET

#endif // __LIBWAVELET_WAVELET_TRAITS_H__

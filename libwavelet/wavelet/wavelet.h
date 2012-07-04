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

   $Id: wavelet.h 8 2009-01-12 14:07:38Z t_hina777 $
*/

#ifndef __LIBWAVELET_WAVELET_H__
#define __LIBWAVELET_WAVELET_H__

#include <string>
#include <wavelet/wavelet_macros.h>

BEGIN_NS_WAVELET

namespace details {

    inline double
    Norm(const double& value) { 
        return value; 
    }

    inline double 
    Norm(const std::complex<double>& value) { 
        return std::norm(value); 
    }

} // namespace detail 


typedef double (*DataSourceListener)(const int index, void* arg);


template <class _Traits, class _Functor>
class Wavelet
{
    typedef _Functor Functor;
    typedef typename _Functor::CS CS;
    typedef typename _Traits::UnitType::Unit Unit;
    typedef typename _Functor::UnitAggregator Mother;

public:
    Wavelet(DataSourceListener listener, void* arg) 
        : m_a(0.0f), m_listener(listener), m_arg(arg)
    {
        //STATIC_CHECK(CS::BEGIN < CS::END, CompactSupportChecker);
        if (!m_listener) 
            THROWS_WAVELET_EXCEPTION();
    }

    virtual ~Wavelet() { /* do nothing */ }

    void
    ScaleProcess(const double a) { 
        m_a = a;
        m_mother.clear();
        m_functor(m_a, m_mother);
    }

    double 
    ShiftProcess(const int b) {
        int begin = (int)(m_a * CS::BEGIN);
        int end = (int)(m_a * CS::END);

        Unit temp = 0;
        int index = 0;
        for (int i = begin + b; i <= end + b; i++) {
            temp += ((*m_listener)(i, m_arg) * m_mother[index]);
            if ((unsigned int)index < m_mother.size() - 1)
                index++;
        }

        return details::Norm(temp) / std::sqrt(m_a);
    }

private:
    double m_a;
    Mother m_mother;
    Functor m_functor;
    DataSourceListener m_listener;
    void* m_arg;
};


typedef Wavelet<TraitsGabor2, FunctorGabor2> WaveletGabor2;
typedef Wavelet<TraitsGabor4, FunctorGabor4> WaveletGabor4;
typedef Wavelet<TraitsGabor8, FunctorGabor8> WaveletGabor8;
typedef Wavelet<TraitsMexicanHat, FunctorMexicanHat> WaveletMexicanHat;
typedef Wavelet<TraitsFrenchHat, FunctorFrenchHat> WaveletFrenchHat;
typedef Wavelet<TraitsShannon, FunctorShannon> WaveletShannon;
typedef Wavelet<TraitsHaar, FunctorHaar> WaveletHaar;

END_NS_WAVELET

#endif // __WTK_WAVELET_H__


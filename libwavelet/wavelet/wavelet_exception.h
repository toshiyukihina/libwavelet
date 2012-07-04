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

   $Id: wavelet_exception.h 8 2009-01-12 14:07:38Z t_hina777 $
*/

#ifndef __LIBWAVELET_WAVELET_EXCEPTION_H__
#define __LIBWAVELET_WAVELET_EXCEPTION_H__

#include <string>
#include <stdexcept>
#include <wavelet/wavelet_macros.h>

BEGIN_NS_WAVELET

class RuntimeException : public std::runtime_error 
{
 public:
    enum { INVALID_LINE = -1 };

    RuntimeException(const std::string& msg) 
        : runtime_error(msg), m_line(INVALID_LINE) {}

    RuntimeException(const std::string& msg, const std::string& file, const int line)
        : runtime_error(msg), m_file(file), m_line(line) {}

    virtual ~RuntimeException() throw() {}

    int GetLine() const { return m_line; }
    std::string GetFile() const { return m_file; }
    std::string GetCause() const { return what(); }

 private:
    std::string m_file;
    int m_line;
};

class WaveletException : public RuntimeException
{
 public:
    WaveletException() 
        : RuntimeException(ERROR_MESSAGE) {}

    WaveletException(const std::string& file, const int line)
        : RuntimeException(ERROR_MESSAGE, file, line) {}

    virtual ~WaveletException() throw() {}

 private:
    static const char* ERROR_MESSAGE;
};

class WaveletProcessorException : public RuntimeException
{
 public:
    WaveletProcessorException() 
        : RuntimeException(ERROR_MESSAGE) {}

    WaveletProcessorException(const std::string& file, const int line) 
        : RuntimeException(ERROR_MESSAGE, file, line) {}
    
    virtual ~WaveletProcessorException() throw() {}

 private:
    static const char* ERROR_MESSAGE;
};


#define THROWS_WAVELET_EXCEPTION() throw WaveletException(__FILE__, __LINE__)
#define THROWS_WAVELET_PROCESSOR_EXCEPTION() throw WaveletProcessorException(__FILE__, __LINE__)

END_NS_WAVELET

#endif // __LIBWAVELET_WAVELET_EXCEPTION_H__

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

   $Id: wavelet_processor.h 8 2009-01-12 14:07:38Z t_hina777 $
*/

#ifndef __LIBWAVELET_WAVELET_PROCESSOR_H__
#define __LIBWAVELET_WAVELET_PROCESSOR_H__

#include <new>
#include <memory>

BEGIN_NS_WAVELET

enum WaveletProcessorEvent 
{
    EVENT_STARTED,
    EVENT_REVOKED,
    EVENT_DONE, 
    EVENT_SCALED,
    EVENTS
};

class WaveletProcessorBase 
{
    enum { DEFAULT_LEVEL = 1 };
    enum { DEFAULT_DIVISION = 1 };

protected:
    enum State 
    {
        STATE_IDLE,
        STATE_BUSY,
        STATE_HALT,
        STATES
    };

    char* StateToString(State s);
    void SetState(const State s);

public:
    WaveletProcessorBase() 
        : m_level(DEFAULT_LEVEL)
        , m_div(DEFAULT_DIVISION)
        , m_state(STATE_IDLE)
    {}

    virtual ~WaveletProcessorBase() {}

    virtual void Start() = 0;

    virtual void Stop() = 0;

    State GetState() const { return m_state; }

    void SetLevel(const int level) { m_level = level; }

    int GetLevel() const { return m_level; }

    void SetDivision(const int div) { m_div = div; }

    int GetDivision() const { return m_div; }

private:
    int m_level;
    int m_div;
    State m_state;
};

inline char* 
WaveletProcessorEventToString(WaveletProcessorEvent e) {
    switch (e) 
    {
    case EVENT_STARTED:
        return "EVENT_STARTED";
    case EVENT_REVOKED:
        return "EVENT_REVOKED";
    case EVENT_DONE: 
        return "EVENT_DONE";
    case EVENT_SCALED:
        return "EVENT_SCALED";
    default:
        return "EVENT_<UNKNOWN>";
    }
}

inline char* 
WaveletProcessorBase::StateToString(State s) {
    switch (s)
    {
    case STATE_IDLE:
        return "STATE_IDLE";
    case STATE_BUSY:
        return "STATE_BUSY";
    case STATE_HALT:
        return "STATE_HALT";
    default:
        return "STATE_<Unknown>";
    }
}

inline void 
WaveletProcessorBase::SetState(const State s) 
{
    if (s != m_state) {
        m_state = s;
    }
}


template <
    class _WaveletT, 
    class _DataSourceT, 
    class _DataListenerT = void (*)(double),
    class _EventListenerT = void (*)(int)
    >
class WaveletProcessor 
    : public WaveletProcessorBase
{
    typedef _WaveletT WaveletType;
    typedef std::auto_ptr<WaveletType> WaveletPtr;
    typedef _DataSourceT DataSourceType;
    typedef _DataListenerT DataListenerType;
    typedef _EventListenerT EventListenerType;
    typedef typename DataSourceType::iterator Iterator;
    typedef typename DataSourceType::const_iterator ConstIterator;

public:
    WaveletProcessor(const DataSourceType& source, 
                     DataListenerType data_listener, 
                     EventListenerType event_listener)
        : WaveletProcessorBase()
        , m_data_source(source)
        , m_data_listener(data_listener)
        , m_event_listener(event_listener)
    {
        WaveletPtr wavelet(new WaveletType(DataSourceListener, this));
        m_wavelet = wavelet;
    }

    virtual ~WaveletProcessor() { /* do nothing */ }

    void Start();

    void Stop();

private:
    WaveletPtr m_wavelet;
    const DataSourceType& m_data_source;
    DataListenerType m_data_listener;
    EventListenerType m_event_listener;

    const DataSourceType& GetDataSource() const 
    { return m_data_source; }

    static double DataSourceListener(const int index, void* arg);
};


template <
    class _WaveletT, 
    class _DataSourceT, 
    class _DataListenerT,
    class _EventListenerT
    >
inline double
WaveletProcessor<_WaveletT, _DataSourceT, _DataListenerT, _EventListenerT>::DataSourceListener(const int index, void* arg) 
{
    typedef WaveletProcessor<
        WaveletType, 
        DataSourceType, 
        DataListenerType,
        EventListenerType> WaveletProcessorType;

    WaveletProcessorType* self 
        = reinterpret_cast<WaveletProcessorType*>(arg);

    const DataSourceType& source = self->GetDataSource();
    if (index < 0 || (unsigned int)index >= source.size())
        return 0.0;
    ConstIterator iter = source.begin();

    return *(iter + index);
}

template <
    class _WaveletT, 
    class _DataSourceT, 
    class _DataListenerT,
    class _EventListenerT
    >
inline void
WaveletProcessor<_WaveletT, _DataSourceT, _DataListenerT, _EventListenerT>::Start() 
{
    switch (GetState()) {
    case STATE_IDLE: /* fall through */
    case STATE_HALT:
        SetState(STATE_BUSY);
        break;
    case STATE_BUSY: /* fall through */
    default:
        THROWS_WAVELET_PROCESSOR_EXCEPTION();
        break;
    }

    m_event_listener(EVENT_STARTED);

    int level = GetLevel();
    int div = GetDivision();
    for (int i = 0; i < div * level; i++) {
        double a = std::pow(2.0, (double)i / div);
        m_wavelet->ScaleProcess(a);

        m_event_listener(EVENT_SCALED);

        int b;
        ConstIterator iter;
        for (iter = GetDataSource().begin(), b = 0; 
             iter != GetDataSource().end(); 
             iter++, b++) 
        {
            double value = m_wavelet->ShiftProcess(b);
            if (GetState() == STATE_HALT) {
                m_event_listener(EVENT_REVOKED);
                THROWS_WAVELET_PROCESSOR_EXCEPTION();
            }
            m_data_listener(value);
        }
    }
    SetState(STATE_IDLE);
    m_event_listener(EVENT_DONE);
}

template <
    class _WaveletT, 
    class _DataSourceT, 
    class _DataListenerT,
    class _EventListenerT
    >
inline void
WaveletProcessor<_WaveletT, _DataSourceT, _DataListenerT, _EventListenerT>::Stop() 
{
    switch (GetState()) {
    case STATE_BUSY:
        SetState(STATE_HALT);
        break;
    case STATE_IDLE: /* fall through */
    case STATE_HALT:
    default:
        /* do nothing */
        break;
    }
}

END_NS_WAVELET

#endif // __LIBWAVELET_WAVELET_PROCESSOR_H__

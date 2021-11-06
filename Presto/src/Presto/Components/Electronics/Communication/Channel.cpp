#include "prestopch.h"
#include "Channel.h"
#include "Presto/Components/Electronics/Communication/Signals/ISignal.h"

namespace Presto
{

    void Channel::Send(ISignal* signal)
    {
        m_Signal = signal;
    }

    ISignal* Channel::Read()
    {
        return m_Signal;
    }

}
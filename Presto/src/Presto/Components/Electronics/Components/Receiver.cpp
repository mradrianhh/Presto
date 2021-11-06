#include "prestopch.h"
#include "Receiver.h"

namespace Presto
{
    void Receiver::Receive()
    {
        std::cout << "Receiving" << std::endl;
        while (true)
        {
            m_Signal = Read();
        }
    }

    ISignal* Receiver::Read()
    {
        return m_Channel->Read();
    }

}
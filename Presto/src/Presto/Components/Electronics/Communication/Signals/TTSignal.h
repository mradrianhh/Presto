#pragma once

#include "Presto/Components/Electronics/Communication/Signals/ISignal.h"

namespace Presto
{

	class TTSignal : public ISignal
	{
	public:
		TTSignal(float* value = 0) : m_Value(value) {}
		~TTSignal() = default;

		inline float* GetValue()
		{
			return m_Value;
		}

		SIGNAL_CLASS_TYPE(SignalType::TT_SIGNAL)
		SIGNAL_CLASS_CATEGORY(SignalCategory::INPUT)
	private:
		float* m_Value;
	};

}
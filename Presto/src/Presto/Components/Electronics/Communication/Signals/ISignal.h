#pragma once

#include <string>

namespace Presto
{

	enum class SignalType
	{
		TT_SIGNAL,
		LT_SIGNAL
	};

	enum class SignalCategory
	{
		INPUT,
		OUTPUT
	};

#define SIGNAL_CLASS_TYPE(type) static SignalType GetStaticSignalType() {return type; }\
								virtual SignalType GetSignalType() const override { return GetStaticSignalType(); }\
								virtual const char* GetName() const override { return #type; }

#define SIGNAL_CLASS_CATEGORY(category) virtual SignalCategory GetCategory() const override { return category; }

	class ISignal
	{
	public:
		virtual ~ISignal() = default;

		virtual SignalType GetSignalType() const = 0;
		virtual const char* GetName() const = 0;
		virtual SignalCategory GetCategory() const = 0;
		virtual std::string ToString() const { return GetName(); }
	};

}
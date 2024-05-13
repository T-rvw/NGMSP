#include "SampleApp.h"

#include <Core/Core.h>
#include <RHI/RHI.h>

using namespace ow;

class HelloWorldSample : public SampleBase
{
public:
	virtual ~HelloWorldSample()
	{
	}

private:
	XYZ m_a;
	XYZW m_b;
	Color m_c;
	LinearColor m_d;
};

DEFINE_SAMPLE(HelloWorldSample);
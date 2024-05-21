#include "SampleApp.h"

#include <Core/Core.h>
#include <RHI/RHI.h>

using namespace ow;

class HelloWorldSample : public SampleBase
{
public:
	virtual ~HelloWorldSample()
	{
		m_e.GetDirection();
	}

private:
	Float3 m_a;
	Float4 m_b;
	Color m_c;
	LinearColor m_d;
	Ray m_e;
	Quaternion m_g;
	Matrix4x4 m_f;
};

DEFINE_SAMPLE(HelloWorldSample);
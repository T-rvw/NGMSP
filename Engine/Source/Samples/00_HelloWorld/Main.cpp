#include "Engine.h"

enum class AA
{
	A,
	B,
	C
};

int main()
{
	constexpr int a = ow::EnumCount<AA>();
	constexpr auto b = ow::EnumName<AA>(AA::C);

	return 0;
}
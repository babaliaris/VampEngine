#include "VampAssert.h"

int main()
{
	VAMP_ASSERT(1, "This should not be visible");
	VAMP_ASSERT(0, "This should fail");
	return 0;
}
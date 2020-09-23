# VampTest

### A Simple unit testing framework to help with the development of VampEngine.

## How to use.
1. `#define VAMP_TEST_ENTRY` before including VampTest.h
2. Include VampTest.h in a .cpp file.
3. Create Your test using the `VAMP_TEST(case_name, test_name)`.
   Multiple .cpp files are not supported! All your tests must be defined inside a single .cpp file!!
   
   
## Example
```c++
#define VAMP_TEST_ENTRY
#include "VampTest.h"


VAMP_TEST(failures , equal)
{
	VAMP_TEST_EQUAL(0, 1);
}

VAMP_TEST(failures, not_equal)
{
	VAMP_TEST_NOTEQUAL(1, 1);
}

VAMP_TEST(failures, tru)
{
	VAMP_TEST_TRUE(0);
}

VAMP_TEST(failures, fals)
{
	VAMP_TEST_FALSE(1);
}



VAMP_TEST(successes, equal)
{
	VAMP_TEST_EQUAL(1, 1);
}

VAMP_TEST(successes, not_equal)
{
	VAMP_TEST_NOTEQUAL(1, 0);
}

VAMP_TEST(successes, tru)
{
	VAMP_TEST_TRUE(1);
}

VAMP_TEST(successes, fals)
{
	VAMP_TEST_FALSE(0);
}
```

## Running Tests

```bash
VampTest.exe (Without Parameters) => Run ALL TESTS.
VampTest.exe --list	          => List All Tests.
VampTest.exe --list case_name	  => List All Tests of that specific case.
VampTest.exe case_name		  => Run All Tests of that specific case.
VampTest.exe case_name.test_name  => Run a specific test.
```

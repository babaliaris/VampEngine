#include "VampLogger.h"

int main()
{

	VAMP_INFO("Info: %d, %s\n", 10, "whats up");

	VAMP_ERROR("Error: %d, %s\n", 10, "whats up");
	VAMP_WARN("Warn: %d, %s\n", 10, "whats up");
	VAMP_TRACE("Trace: %d, %s\n", 10, "whats up");

	VAMP_PRINT("%s", "Simple Print, ");
	VAMP_PRINT_GREEN("%s", "green, ");
	VAMP_PRINT_RED("%s", "red, ");
	VAMP_PRINT_YELLOW("%s", "yellow ");
	VAMP_PRINT_BLUE("%s", "blue ");
	VAMP_PRINT_PINK("%s", "pink ");
	VAMP_PRINT_CYAN("%s", "cyan\n\n");

	printf("Normal Text\n");

	return getchar();
}
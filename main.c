#include <stdio.h>
#include "simple_shell.h"

int main(void) {
	env();
	custom_exit();
	handle_path();
	simple_shell02();
	simple_shell();
	
	return 0;
}

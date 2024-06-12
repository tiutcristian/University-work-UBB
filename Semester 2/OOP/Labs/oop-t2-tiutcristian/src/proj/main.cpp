#include "UI.h"
#include "Device.h"

int main()
{
	Device d;
	UI ui(d);
	ui.run();
	return 0;
}
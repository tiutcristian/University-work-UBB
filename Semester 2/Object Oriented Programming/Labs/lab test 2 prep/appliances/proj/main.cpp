#include "UI.h"
#include "Service.h"

int main()
{
	Service	service;
	UI ui(service);
	ui.runUI();
	return 0;
}
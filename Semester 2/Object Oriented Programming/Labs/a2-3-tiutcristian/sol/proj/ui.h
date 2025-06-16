#pragma once
#include "controller.h"

typedef struct
{
	Service* serv;
} UI;

/// <summary>
/// Creates a UI.
/// </summary>
/// <param name="s">Pointer to the service.</param>
/// <returns>Pointer to the UI.</returns>
UI* createUI(Service* s);


/// <summary>
/// Destroys a given UI.
/// </summary>
/// <param name="ui">Pointer to the UI.</param>
void destroyUI(UI* ui);

/// <summary>
/// Starts the UI.
/// </summary>
/// <param name="ui">Pointer to the UI.</param>
void startUI(UI* ui);

#pragma once

/*
 * presentation.h
 * Presentation layer for the Qt inventory management interface.
 */

/*
 * Purpose: Renders and runs the complete Qt inventory interface.
 * Parameters: inventoryFilePath - CSV path used by load and save actions.
 * Return value: None.
 */
void renderUI(const char* inventoryFilePath);

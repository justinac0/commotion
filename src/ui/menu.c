#include <raylib.h>
#include <stdio.h>

#include "menu.h"

#define MENU_WIDTH 196
#define MENU_PADDING 10

#define MAX_TEXT_SIZE 20

void draw_menu(Body* target) {
	if (!target) return;

	DrawRectangle(SCREEN_WIDTH - MENU_WIDTH, 0, MENU_WIDTH, SCREEN_HEIGHT, (Color){.r=120,.g=120,.b=120,.a=120});

	int currentY = MENU_PADDING;

	char value[MAX_TEXT_SIZE];

	snprintf(value, MAX_TEXT_SIZE, "%p", target);
	draw_text_field("Pointer Address", value, &currentY);

	snprintf(value, MAX_TEXT_SIZE, "%f", target->state.position.x);
	draw_text_field("Position X", value, &currentY);

	snprintf(value, MAX_TEXT_SIZE, "%f", target->state.position.y);
	draw_text_field("Position Y", value, &currentY);

	snprintf(value, MAX_TEXT_SIZE, "%f", target->state.velocity.x);
	draw_text_field("Velocity X", value, &currentY);

	snprintf(value, MAX_TEXT_SIZE, "%f", target->state.velocity.y);
	draw_text_field("Velocity Y", value, &currentY);

	snprintf(value, MAX_TEXT_SIZE, "%f", target->state.acceleration.x);
	draw_text_field("Acceleration X", value, &currentY);

	snprintf(value, MAX_TEXT_SIZE, "%f", target->state.acceleration.y);
	draw_text_field("Acceleration Y", value, &currentY);
}

#define TEXT_SIZE 18
#define TEXT_HEIGHT (TEXT_SIZE + MENU_PADDING)
#define TEXT_FIELD_HEIGHT (2 * TEXT_HEIGHT)

void draw_text_field(const char* label, const char* value, int* currentY) {
	const int x = SCREEN_WIDTH - MENU_WIDTH + MENU_PADDING;
	const int y = *currentY;

	*currentY += TEXT_FIELD_HEIGHT;

	DrawText(label, x, y, TEXT_SIZE + 2, MAGENTA);
	DrawText(value, x, y + TEXT_HEIGHT, TEXT_SIZE, WHITE);
}

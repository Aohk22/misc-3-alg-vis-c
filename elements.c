#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef VIZ_ELEMENTS_H
#define VIZ_ELEMENTS_H

typedef struct {
	int *arr;
	int len;
	Vector2 base;
	Vector2 rectSize;
	Vector2 textOffset;
	int textSize;
} ArrayElm;

ArrayElm *newArrayElement(int *arr, int len, Vector2 size, Vector2 base, int fontSz) {
	ArrayElm *pArrElm = (ArrayElm *)malloc(sizeof(ArrayElm));

	pArrElm->arr = arr;
	pArrElm->len = len;
	pArrElm->base = base;
	pArrElm->rectSize = size;
	pArrElm->textOffset = (Vector2) {
		.x = ((size.x - fontSz) / 2.) + 3,
		.y = ((size.y - fontSz) / 2.) + 3,
	};
	pArrElm->textSize = fontSz;

	return pArrElm;
}

void drawArray(ArrayElm *elm, uint8_t highlight, Vector2 pointers, int padding) {
	for (int i = 0; i < elm->len; i++) {
		char text[10];

		sprintf(text, "%d", elm->arr[i]);

		Vector2 curPosition = { 
			.x = elm->base.x + (elm->rectSize.x + padding) * i,
			.y = elm->base.y 
		};

		Vector2 textPosition = {
			.x = curPosition.x + elm->textOffset.x,
			.y = curPosition.y + elm->textOffset.y
		};

		Color c = (highlight && (i == pointers.x || i == pointers.y)) ? RED : GREEN;

		DrawRectangleV(curPosition, elm->rectSize, BLUE);
		DrawText(text, textPosition.x, textPosition.y, elm->textSize, c);
	}
}

#endif

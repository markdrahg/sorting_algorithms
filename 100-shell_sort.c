#include "deck.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compare_cards(const void *a, const void *b)
{
	const card_t *card_a = (*(const deck_node_t **)a)->card;
	const card_t *card_b = (*(const deck_node_t **)b)->card;

	int value_cmp = strcmp(card_a->value, card_b->value);
	if (value_cmp != 0)
		return value_cmp;

	return card_a->kind - card_b->kind;
}

void sort_deck(deck_node_t **deck)
{
	size_t i;
	size_t deck_size = 52;
	deck_node_t *deck_array[52];
	deck_node_t *current = *deck;

	qsort(deck_array, deck_size, sizeof(deck_node_t *), compare_cards);

	if (!current)
	{
		return;
	}

	for (i = 0; i < deck_size; ++i)
	{
		if (!current)
		{
			fprintf(stderr, "Error: Deck has less than 52 cards\n");
			exit(EXIT_FAILURE);
		}
		deck_array[i] = current;
		current = current->next;
	}

	for (i = 0; i < deck_size; ++i)
	{
		deck_array[i]->prev = (i == 0) ? NULL : deck_array[i - 1];
		deck_array[i]->next = (i == deck_size - 1) ? NULL : deck_array[i + 1];
	}

	*deck = deck_array[0];
}

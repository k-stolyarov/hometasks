#include "structures.h"
#include <stdlib.h>

void append_line_to_list(Line * const line_to_add, Line ** const list_head)
{
	if (*list_head != NULL)
	{
		(*list_head)->next = line_to_add;
	}
	*list_head = line_to_add;
}
/******************************************************************************
 * alist.c
 *
 * A minimal array list/queue/stack for embedded code.
 * This list is so minimal that is doesn't even store the data. Instead it only
 * handles indexes in an array.
 * The type used for the indexes is used-defined. For instance, you can use
 * uint8_t to save a few bytes.
 *
 *
 * This code is released under the MIT license.
 *
 * Copyright (c) 2019 Daniel Guerrero Miralles.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "alist.h"

#define WRAP(l, i) ((i) % l->size)

void alist_init(struct alist *l, ALIST_INDEX_T items)
{
	assert(l);
	l->size = items;
	l->head = 0;
	l->count = 0;
}

ALIST_INDEX_T alist_add(struct alist *l)
{
	assert(l);
	assert(l->count < l->size);
	ALIST_INDEX_T pos = WRAP(l, l->head + l->count);
	l->count++;
	return pos;
}

ALIST_INDEX_T alist_next(struct alist *l, ALIST_INDEX_T i)
{
	assert(l);
	assert(i - l->head < l->count);
	return WRAP(l, i + 1);
}

ALIST_INDEX_T alist_at(struct alist *l, size_t pos)
{
	assert(l);
	assert(pos < l->count);
	return WRAP(l, l->head + pos);
}

ALIST_INDEX_T alist_rm_first(struct alist *l)
{
	assert(l);
	assert(l->count <= l->size);	
	assert(0 < l->count);
	ALIST_INDEX_T first = l->head;
	l->head = WRAP(l, l->head + 1);
	l->count--;
	return first;
}

ALIST_INDEX_T alist_rm_last(struct alist *l)
{
	assert(l);
	assert(l->count <= l->size);	
	assert(0 < l->count);
	ALIST_INDEX_T last = WRAP(l, l->head + l->count - 1);
	l->count--;
	return last;
}

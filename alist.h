/******************************************************************************
 * alist.h
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

#ifndef AQUILES_ALIST_H_
#define AQUILES_ALIST_H_

#ifndef ALIST_INDEX_T
#define ALIST_INDEX_T size_t
#endif

struct alist {
	ALIST_INDEX_T size;
	ALIST_INDEX_T head;
	ALIST_INDEX_T count;
};

#define alist_is_empty(l) (0 == (l)->count)
#define alist_is_full(l) ((l)->count == (l)->size)
#define alist_count(l) ((l)->count)
#define alist_first(l) alist_at(l,0)
#define alist_last(l) alist_at(l,(l)->count-1)

void alist_init(struct alist *l, ALIST_INDEX_T count);
ALIST_INDEX_T alist_add(struct alist *l);
ALIST_INDEX_T alist_at(struct alist *l, size_t pos);
ALIST_INDEX_T alist_next(struct alist *l, ALIST_INDEX_T i);
ALIST_INDEX_T alist_rm_first(struct alist *l);
ALIST_INDEX_T alist_rm_last(struct alist *l);

/* STACK */

#define alist_push(l) alist_add(l)
#define alist_pop(l) alist_rm_last(l)
#define alist_top(l) alist_last(l)

/* QUEUE */

#define alist_enqueue(l) alist_add(l)
#define alist_dequeue(l) alist_rm_first(l)
#define alist_front(l) alist_first(l)

#endif /*AQUILES_ALIST_H_*/

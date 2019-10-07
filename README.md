alist
=====

A minimal list for embedded code

The goal of this code is to provide a list implementation for code that must 
run on **very** memory-constrained devices, typical of embedded code.

Because of this, the overhead has been kept to the bare minimum: the most 
compact list possible uses just 3 bytes.

The way I achieved this is by not storing pointers or data. The list just keeps
track of used indexes to an external array (where you should put the actual 
data). This has the side benefit of allowing the list code to be type-safe, 
with cost zero.

Compiling
----------

To compile and run the test just type 

```sh
make && ./test
```

in the command line.

Using
-----

Look at the code in [`test.c`](./test.c) for an example of how to use the code. 

A few details you have to keep in mind while using it:

* Always, **always**, check if a list is full before addind a new item. The 
code will fail an assertion (and die rather noisily) if you fail to do so.

* Always, and I mean **always**, check if the list has data before accessing it.

* The default index type is `size_t`, which on a typical embedded CPU will take
4 bytes. If your lists are small, you can change it to `uint_8` or `uit16_t` to
save space. To do so, just `#define` the desired type befor including the 
library, like this:

```C
#define ALIST_INDEX_T uint8_t
#include "alist.h"

// ... your code here ...
```

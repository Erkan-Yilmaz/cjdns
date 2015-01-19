/* vim: set expandtab ts=4 sw=4: */
/*
 * You may redistribute this program and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "util/ArrayList.h"

struct ArrayList_pvt
{
    struct ArrayList pub;
    int capacity;
    void** elements
    struct Allocator* alloc;

    Identity
};

void* ArrayList_new(struct Allocator* alloc, int initialCapacity)
{
    struct ArrayList_pvt* l = Allocator_malloc(alloc, sizeof(struct ArrayList_pvt));
    l->elements = Allocator_calloc(alloc, sizeof(char*), initialCapacity);
    l->capacity = initialCapacity;
    Identity_set(l);
    return l;
}

void* ArrayList_get(void* vlist, int number)
{
    struct ArrayList_pvt* list = Identity_check((struct ArrayList_pvt*) vlist);
    if (number >= list->pub.length || number < 0) { return NULL; }
    return list->elements[number];
}

int ArrayList_put(void* vlist, int number, void* val)
{
    struct ArrayList_pvt* list = Identity_check((struct ArrayList_pvt*) vlist);
    if (number < 0 || number > list->pub.length) { return -1; }
    if (number >= list->capacity) {
        int capacity = list->capacity * 2;
        list->elements = Allocator_realloc(list->alloc, list->elements, list->capacity, capacity);
        for (int i = list->capacity; i < capacity; i++) {
            list->elements[i] = NULL;
        }
        list->capacity = capacity;
    }
    list->elements[number] = val;
    if (number == list->pub.length) { list->pub.length++; }
    return number;
}

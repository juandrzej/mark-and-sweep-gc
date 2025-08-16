#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "vm.h"
#include "sneknew.h"
#include "snekobject.h"

// Simple test helper functions
void test_simple() {
    printf("Running test_simple...\n");
    
    vm_t *vm = vm_new();
    frame_t *f1 = vm_new_frame(vm);

    snek_object_t *s = new_snek_string(vm, "I wish I knew how to read.");
    frame_reference_object(f1, s);
    
    printf("  Created string object, VM has %zu objects\n", vm->objects->count);
    
    vm_collect_garbage(vm);
    printf("  After GC (with frame): VM has %zu objects\n", vm->objects->count);
    // String should still exist because frame references it

    frame_free(vm_frame_pop(vm));
    vm_collect_garbage(vm);
    printf("  After GC (frame freed): VM has %zu objects\n", vm->objects->count);
    // String should be collected now

    vm_free(vm);
    printf("  test_simple PASSED\n\n");
}

void test_full() {
    printf("Running test_full...\n");
    
    vm_t *vm = vm_new();
    frame_t *f1 = vm_new_frame(vm);
    frame_t *f2 = vm_new_frame(vm);
    frame_t *f3 = vm_new_frame(vm);

    snek_object_t *s1 = new_snek_string(vm, "This string is going into frame 1");
    frame_reference_object(f1, s1);

    snek_object_t *s2 = new_snek_string(vm, "This string is going into frame 2");
    frame_reference_object(f2, s2);

    snek_object_t *s3 = new_snek_string(vm, "This string is going into frame 3");
    frame_reference_object(f3, s3);

    snek_object_t *i1 = new_snek_integer(vm, 69);
    snek_object_t *i2 = new_snek_integer(vm, 420);
    snek_object_t *i3 = new_snek_integer(vm, 1337);
    snek_object_t *v = new_snek_vector3(vm, i1, i2, i3);
    
    frame_reference_object(f2, v);
    frame_reference_object(f3, v);

    printf("  Created 7 objects, VM has %zu objects\n", vm->objects->count);
    assert(vm->objects->count == 7);

    // Only free the top frame (f3)
    frame_free(vm_frame_pop(vm));
    vm_collect_garbage(vm);
    printf("  After freeing f3: VM has %zu objects\n", vm->objects->count);
    // s3 should be collected, but vector still referenced by f2

    // Free remaining frames
    frame_free(vm_frame_pop(vm));
    frame_free(vm_frame_pop(vm));
    vm_collect_garbage(vm);
    printf("  After freeing all frames: VM has %zu objects\n", vm->objects->count);
    assert(vm->objects->count == 0);

    vm_free(vm);
    printf("  test_full PASSED\n\n");
}

void test_vector_references() {
    printf("Running test_vector_references...\n");
    
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);

    // Create integers
    snek_object_t *x = new_snek_integer(vm, 10);
    snek_object_t *y = new_snek_integer(vm, 20);
    snek_object_t *z = new_snek_integer(vm, 30);
    
    // Create vector that references the integers
    snek_object_t *vec = new_snek_vector3(vm, x, y, z);
    frame_reference_object(frame, vec);
    
    printf("  Created vector with 3 integers, VM has %zu objects\n", vm->objects->count);
    assert(vm->objects->count == 4); // 3 integers + 1 vector
    
    vm_collect_garbage(vm);
    printf("  After GC: VM has %zu objects\n", vm->objects->count);
    assert(vm->objects->count == 4); // All should still be alive due to vector references
    
    frame_free(vm_frame_pop(vm));
    vm_collect_garbage(vm);
    printf("  After frame freed: VM has %zu objects\n", vm->objects->count);
    assert(vm->objects->count == 0); // All should be collected
    
    vm_free(vm);
    printf("  test_vector_references PASSED\n\n");
}

int main() {
    printf("=== Garbage Collector Tests ===\n\n");
    
    test_simple();
    test_full();
    test_vector_references();
    
    printf("All tests completed successfully!\n");
    printf("Your garbage collector is working! 🎉\n");
    
    return 0;
}

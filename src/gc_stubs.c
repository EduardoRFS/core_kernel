#define CAML_INTERNALS
#include <caml/memory.h>
#include <caml/gc_ctrl.h>
#include <caml/domain_state.h>
#include <caml/shared_heap.h>

static intnat minor_words(void)
{
  return (intnat) (Caml_state->stat_minor_words +
            (double) (Caml_state->young_end - Caml_state->young_ptr));
}

static intnat promoted_words(void)
{
  return ((intnat) Caml_state->stat_promoted_words);
}

CAMLprim value core_kernel_gc_minor_words(value unit __attribute__((unused)))
{
  return Val_long(minor_words());
}

static intnat major_words(void)
{
  return (intnat) (Caml_state->stat_major_words + (double) Caml_state->allocated_words);
}

CAMLprim value core_kernel_gc_major_words(value unit __attribute__((unused)))
{
  return Val_long(major_words());
}

CAMLprim value core_kernel_gc_promoted_words(value unit __attribute__((unused)))
{
  return Val_long(promoted_words());
}

CAMLprim value core_kernel_gc_minor_collections(value unit __attribute__((unused)))
{
  return Val_long(Caml_state->stat_minor_collections);
}

CAMLprim value core_kernel_gc_major_collections(value unit __attribute__((unused)))
{
  return Val_long(Caml_state->stat_major_collections);
}

CAMLprim value core_kernel_gc_heap_words(value unit __attribute__((unused)))
{
  return Val_long(Wsize_bsize(caml_heap_size(Caml_state->shared_heap)));
}

CAMLprim value core_kernel_gc_heap_chunks(value unit __attribute__((unused)))
{
  return Val_long(0);
}

CAMLprim value core_kernel_gc_compactions(value unit __attribute__((unused)))
{
  return Val_long(0);
}

CAMLprim value core_kernel_gc_top_heap_words(value unit __attribute__((unused)))
{
  return Val_long(caml_top_heap_words(Caml_state->shared_heap));
}

CAMLprim value core_kernel_gc_major_plus_minor_words(value unit __attribute__((unused)))
{
  return Val_long(minor_words() + major_words());
}

CAMLprim value core_kernel_gc_allocated_words(value unit __attribute__((unused)))
{
  return Val_long(minor_words() + major_words() - promoted_words());
}

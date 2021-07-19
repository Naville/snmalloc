#pragma once

#include "../backend/backend.h"
#include "../mem/corealloc.h"
#include "../mem/pool.h"
#include "../mem/slaballocator.h"
#include "commonconfig.h"

namespace snmalloc
{
  /**
   * A single fixed address range allocator configuration
   */
  template<SNMALLOC_CONCEPT(ConceptPAL) PAL>
  class FixedGlobals final : public BackendAllocator<PAL, true>
  {
  public:
    using GlobalPoolState = PoolState<CoreAllocator<FixedGlobals>>;

  private:
    using Backend = BackendAllocator<PAL, true>;
    inline static ChunkAllocatorState slab_allocator_state;

    inline static GlobalPoolState alloc_pool;

  public:
    static ChunkAllocatorState&
    get_slab_allocator_state(typename Backend::LocalState*)
    {
      return slab_allocator_state;
    }

    static GlobalPoolState& pool()
    {
      return alloc_pool;
    }

    static constexpr Flags Options{};

    // This needs to be a forward reference as the
    // thread local state will need to know about this.
    // This may allocate, so must be called once a thread
    // local allocator exists.
    static void register_clean_up()
    {
      snmalloc::register_clean_up();
    }

    static void
    init(typename Backend::LocalState* local_state, void* base, size_t length)
    {
      Backend::init(local_state, base, length);
    }
  };
}
# Engine Service

## Job System

Job system accepts tickets and jobs.
Job can be anything that can be performed asynchronously.
Ticket is a job with a specified set of conditions, each of these must be completed
before the job can be executed.
For example to remove a block we need to first ensure a given chunk is present.
If it's not present we need to create a remove block job with a condition that this chunk is present.

```c++

void set_block_at(BlockPosition position, BlockState state)
{
  if (m_chunk_system.is_loaded(position)) {
    return m_chunk_system.set_block_at(position, state);
  }

  m_job_system.when<ChunkIsLoaded>(position).invoke([this, position, state]() {
    m_chunk_system.set_block_at(position, state);
  });
}
```

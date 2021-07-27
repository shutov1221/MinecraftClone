#pragma once
#include "Chunk.h"
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ChunkThreads
{
public:
	ChunkThreads(size_t);
	bool CalculateChunks(const std::vector<Chunk_ptr>& chunks);
private:
	std::vector< std::thread > chunk_makers;
	std::vector< std::thread > mesh_makers;
	// the task queue
	std::queue< std::function<void()> > create_chunk_tasks;
	std::queue< std::function<void()> > create_mesh_tasks;

	std::mutex chunk_mutex;
	std::mutex mesh_mutex;
	std::condition_variable condition_create_chunk;
	std::condition_variable condition_calculate_mesh;

	bool stop;
};

inline ChunkThreads::ChunkThreads(size_t threads)
	: stop(false)
{
    for (size_t i = 0; i < threads; ++i)
        chunk_makers.emplace_back(
            [this]
            {
                for (;;)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->chunk_mutex);
                        this->condition_create_chunk.wait(lock,
                            [this] { return this->stop || !this->create_chunk_tasks.empty(); });
                        if (this->stop && this->create_chunk_tasks.empty())
                            return;
                        task = std::move(this->create_chunk_tasks.front());
                        this->create_chunk_tasks.pop();
                    }

                    task();
                }
            }
            );
}

bool ChunkThreads::CalculateChunks(const std::vector<Chunk_ptr>& chunks) {
	return true;
}


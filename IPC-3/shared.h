#ifndef SHARED_ARRAY_H
#define SHARED_ARRAY_H

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <string>
#include <stdexcept>

class shared_array {
    std::string shm_name;
    std::string sem_name;
    int shm_fd;
    int* data;
    size_t n;
    size_t bytes;
    sem_t* semaphore;

public:
    shared_array(const std::string& name, size_t count);
    ~shared_array();

    int& operator[](size_t i);
    size_t size() const;
    sem_t* get_semaphore();
};

#endif

shared_array::shared_array(const std::string& name, size_t count)
    : shm_fd(-1), data(nullptr), n(count), semaphore(nullptr)
{
    if (count == 0 || count > 1000000000)
        throw std::runtime_error("invalid size");

    shm_name = "/" + name;
    sem_name = "/sem_" + name;
    bytes = n * sizeof(int);

    shm_fd = shm_open(shm_name.c_str(), O_RDWR | O_CREAT | O_EXCL, 0664);
    if (shm_fd != -1) {
        if (ftruncate(shm_fd, bytes) == -1)
            throw std::runtime_error("truncate failed");
    } else {
        shm_fd = shm_open(shm_name.c_str(), O_RDWR, 0664);
        if (shm_fd == -1)
            throw std::runtime_error("open failed");
    }

    void* mem = mmap(nullptr, bytes, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (mem == MAP_FAILED)
        throw std::runtime_error("mmap failed");

    data = static_cast<int*>(mem);

    semaphore = sem_open(sem_name.c_str(), O_CREAT, 0664, 1);
    if (semaphore == SEM_FAILED)
        throw std::runtime_error("sem failed");
}

shared_array::~shared_array() {
    if (data) munmap(data, bytes);
    if (shm_fd != -1) close(shm_fd);
    if (semaphore) sem_close(semaphore);
    shm_unlink(shm_name.c_str());
}

int& shared_array::operator[](size_t i) {
    if (i >= n) throw std::out_of_range("index");
    return data[i];
}

size_t shared_array::size() const { return n; }
sem_t* shared_array::get_semaphore() { return semaphore; }


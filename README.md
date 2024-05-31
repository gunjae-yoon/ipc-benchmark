# IPC Benchmark
Copyright(c) 2024 Gunjae Yoon (rnswo42b@gmail.com)

## Introduction
This benchmark evaluates the performance of IPC(Inter-process communication) manners implemented by C/C++.

## Benchmarks and Measurements
Benchmark      | Description
---------------|----------------------------------------------------
shm_branch     | Create shared memory per subscribers
shm_trunk      | Create a single shared memory, and create lists in this shared memory per subscribers
mqueue         | Create message queue per subscribes

## Libraries
Library | Language | Version | Notes
--------|----------|---------|-------------------
[Boost](https://github.com/boostorg/boost) | C++ | v1.85.0 | Used to create shared {memory, mutex, condition}

## Test Environment
Category       | Spec
---------------|----------------------------------------------------
OS             | Ubuntu 22.04.4 LTS
CPU            | 13th Gen Intel(R) Core(TM) i7-13700K
Memory         | 64GB (DDR4)
Compiler       | GCC 11.4.0
Standard       | C++17

## Test Result
```bash
ipc-benchmark version: 0.0.1 (updated: 2024/05/31 10:29:32, hash: a3706c9)
test targets: 10
	test result of ipc_benchmark::branch::Performance is   223,802,709 nanoseconds
	test result of ipc_benchmark::trunk::Performance  is   570,630,920 nanoseconds
	test result of ipc_benchmark::mqueue::Performance is    43,832,714 nanoseconds
test targets: 20
	test result of ipc_benchmark::branch::Performance is   447,529,466 nanoseconds
	test result of ipc_benchmark::trunk::Performance  is 1,178,316,008 nanoseconds
	test result of ipc_benchmark::mqueue::Performance is    92,646,727 nanoseconds
test targets: 30
	test result of ipc_benchmark::branch::Performance is   665,735,607 nanoseconds
	test result of ipc_benchmark::trunk::Performance  is 1,812,611,246 nanoseconds
	test result of ipc_benchmark::mqueue::Performance is   135,302,118 nanoseconds
test targets: 40
	test result of ipc_benchmark::branch::Performance is   889,166,020 nanoseconds
	test result of ipc_benchmark::trunk::Performance  is 2,422,761,509 nanoseconds
	test result of ipc_benchmark::mqueue::Performance is   193,605,859 nanoseconds
test targets: 50
	test result of ipc_benchmark::branch::Performance is 1,115,428,209 nanoseconds
	test result of ipc_benchmark::trunk::Performance  is 3,062,809,376 nanoseconds
	test result of ipc_benchmark::mqueue::Performance is   246,181,892 nanoseconds
test targets: 60
	test result of ipc_benchmark::branch::Performance is 1,331,181,700 nanoseconds
	test result of ipc_benchmark::trunk::Performance  is 3,703,433,281 nanoseconds
	test result of ipc_benchmark::mqueue::Performance is   248,373,058 nanoseconds
test targets: 70
	test result of ipc_benchmark::branch::Performance is 1,544,887,182 nanoseconds
	test result of ipc_benchmark::trunk::Performance  is 4,342,669,194 nanoseconds
	test result of ipc_benchmark::mqueue::Performance is   286,893,108 nanoseconds
test targets: 80
	test result of ipc_benchmark::branch::Performance is 1,767,845,793 nanoseconds
	test result of ipc_benchmark::trunk::Performance  is 5,184,878,050 nanoseconds
	test result of ipc_benchmark::mqueue::Performance is   335,694,997 nanoseconds
test targets: 90
	test result of ipc_benchmark::branch::Performance is 1,985,886,943 nanoseconds
	test result of ipc_benchmark::trunk::Performance  is 5,634,920,888 nanoseconds
	test result of ipc_benchmark::mqueue::Performance is   375,314,558 nanoseconds
test targets: 100
	test result of ipc_benchmark::branch::Performance is 2,209,781,887 nanoseconds
	test result of ipc_benchmark::trunk::Performance  is 6,347,755,309 nanoseconds
	test result of ipc_benchmark::mqueue::Performance is   415,308,396 nanoseconds
```

## Conclusion
POSIX message queue was faster than shared memory due to the following reasons:

### 1. Synchronization Overhead:
- **Message Queues**: POSIX message queue handle synchronization internally. They provide built-in mechanisms to ensure safe communication between processes, which can be more efficient than manually implementing synchronization mechanisms.
- **Shared Memory**: When using shared memory, you need to implement your own synchronization (e.g., using mutexes or semaphores) to manage concurrent access. This can introduce additional overhead and complexity, potentially making shared memory slower if not handled optimally.

### 2. Kernel Management:
- **Message Queues**: The operating system kernel manages the message queue, including handling the synchronization and data transfer between processes. This can lead to efficient and optimized handling of inter-process communication (IPC) without user-space intervention.
- **Shared Memory**: With shared memory, the kernel only provides the mechanism to share memory between processes. The actual data management and synchronization are left to user-space, which may not be as efficient as the kernel-managed operations.

### 3. Ease of Use:
- **Message Queues**: They provide a simple API for sending and receiving messages, which can be easier and quicker to use correctly than setting up shared memory regions and managing synchronization.
- **Shared Memory**: While powerful and flexible, shared memory requires more boilerplate code and careful handling of synchronization primitives, which can introduce bugs and performance issues if not implemented correctly.

### 4. Communication Model:
- **Message Queues**: They follow a message-passing model, which can be more suitable for certain types of applications that involve discrete messages or commands. This model can lead to more predictable and efficient data transfers.
- **Shared Memory**: It follows a shared-memory model, which is suitable for large data transfers or complex data structures. However, for small, frequent messages, the overhead of synchronization can make it less efficient than message queue.

### 5. Overhead of Memory Management:
- **Message Queues**: The kernel manages the memory for message queue, which can be optimized for the specific task of message passing.
- **Shared Memory**: The application is responsible for managing the memory, which can lead to inefficiencies if not handled properly.

In summary, POSIX message queue can be faster than shared memory for scenarios where the synchronization overhead and complexity of shared memory outweigh the benefits. The kernel-level management and built-in synchronization of message queue can provide more efficient inter-process communication for certain use cases. However, shared memory can still be the preferred choice for applications that require sharing large amounts of data with minimal synchronization overhead.

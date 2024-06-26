## 索引
1. [linux的常见命令](#说一下linux的常见命令)
2. [如果访问网络不通通常会用哪些命令来查找问题列出排查的顺序和命令](#如果访问网络不通通常会用哪些命令来查找问题列出排查的顺序和命令)
3. [线程和进程的区别](#线程和进程的区别)
4. [如何讲进程绑定到某一个cpu核上跑怎么实现](#如何讲进程绑定到某一个cpu核上跑怎么实现)
5. [进程间通信的方式](#进程间通信的方式)
6. [说一下共享内存的特点，如何确定数据的边界，如何提高共享内存的并发](#说一下共享内存的特点如何确定数据的边界如何提高共享内存的并发)
7. [什么是硬中断和软中断，什么是中断的上半部和下半部，中断里能否用sleep函数，中断内如何加锁](#什么是硬中断和软中断什么是中断的上半部和下半部中断里能否用sleep函数中断内如何加锁)
8. [freertos 和 linux的区别](#freertos-和-linux的区别)
9. [linux 如何实现完全公平调度](#linux-如何实现完全公平调度)

### 说一下linux的常见命令
文件操作
ls cd pwd cp mv rm mkdir touch chmod find grep echo cat tail head
系统监控
df du ps kill top uptime
网络管理
ping 
ifconfig 
netstat - 显示网络连接、路由表、接口统计等网络信息
traceroute - 显示数据包到达主机所经过的路由
ssh
scp
curl
ip - 用于显示或管理路由、设备、策略路由和隧道

### 如果访问网络不通，通常会用哪些命令来查找问题，列出排查的顺序和命令
1. 检查网络接口状态
首先确认网络接口（例如以太网卡、Wi-Fi）是否启动，并且配置了正确的IP地址。
使用命令 `ip addr` 或 `ifconfig`

2. 测试与本地网络的连接
确认设备是否能够连接到本地网络或路由器。
使用命令 `ping 本地网关 192。168.1.1`

3. 测试外部连接
测试设备是否能连接到外部网络，通常是通过ping公共服务器或DNS解析。
使用 `ping google.com` 或 `ping 8.8.8.8`

4. 检查 DNS 解析
确认系统的DNS服务是否正常工作。
使用 `nslookup google.com`

5. 检查路由表
确认数据包是否被正确路由到目的地。
使用 `ip route` 或 `route`

6. 检查防火墙设置
确认本地防火墙设置是否阻止了出站或入站的网络连接。
使用 `iptable -L` 或者 `ufw status`

7. 使用跟踪路由
如果之前的步骤都没有发现问题，使用跟踪路由来查看数据包到达远程主机的路径。
使用 `traceroute google.com`

### 线程和进程的区别
1. 定义
进程：进程是操作系统进行资源分配和调度的一个独立单位，是应用程序的一个实例。进程至少包含一个线程，拥有自己的虚拟地址空间、代码、数据和系统资源（如文件句柄、信号等）。
线程：线程是进程内的一个执行路径，是CPU调度和执行的最小单位。线程在进程的虚拟地址空间中运行，并共享相同进程的资源和数据。
2. 资源分配和共享
进程：每个进程拥有自己独立的地址空间，一个进程崩溃不会直接影响到其他进程。进程间通信（IPC）需要特定的机制，如管道、消息队列、共享内存等。
线程：同一进程内的所有线程共享进程的地址空间和资源，如内存、数据、文件句柄等。线程之间的数据共享和通信更简单，但也更容易出现如数据同步和死锁等并发问题。
3. 开销和性能
进程：创建新进程的资源开销较大，涉及复制父进程的资源、地址空间等。进程切换的开销也比线程切换要大，因为涉及更多的内存和资源状态。
线程：线程的创建和销毁、上下文切换的开销相对较小，因为线程共享大部分进程资源。线程启动速度快，效率高。
4. 控制和安全
进程：由于进程间相互独立，系统的稳定性更好。一个进程崩溃通常不会影响到其他进程。
线程：线程由于共享同一进程中的资源，一个线程的错误可能影响整个进程的稳定性。此外，线程程序设计需要仔细处理资源的同步和互斥，以避免死锁等问题。
5. 应用场景
进程：适用于需要独立运行和资源独立管理的应用，如多任务操作系统中同时运行多个不同的应用程序。
线程：适用于需要执行多个任务而又要求快速响应和资源共享的场景，如Web服务器处理多个用户请求，或者在一个应用程序中执行多个并行任务。

### 如何讲进程绑定到某一个CPU核上跑，怎么实现
将进程绑定到特定的CPU核上运行，称为CPU亲和性（CPU affinity）设置。这可以帮助提高程序性能，因为它减少了进程在多个CPU核之间迁移时带来的缓存失效和调度开销。在Linux系统中，可以使用多种工具和方法来设置CPU亲和性。

使用 taskset 命令
taskset 是最常用的设置CPU亲和性的工具。它提供了一个简单的命令行接口来设置或获取进程或线程的CPU亲和性。

设置进程的CPU亲和性：

```bash
taskset -c [cores] [command]
```
其中 [cores] 是CPU核心的编号，从0开始。例如，如果你想让一个进程只在第一个核（核心0）上运行：

```bash
taskset -c 0 [command]
```
设置已运行进程的CPU亲和性：

```bash
taskset -cp [cores] [pid]
```
其中 [pid] 是进程ID。例如，要将进程ID为1234的进程绑定到CPU核心0上：

```bash
taskset -cp 0 1234
```

#### 使用 sched_setaffinity 调用
在编写C或C++程序时，可以直接在代码中调用 sched_setaffinity 函数来设置进程或线程的CPU亲和性。这提供了更灵活的控制方式。

示例代码：
```c
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>

int main() {
    cpu_set_t set;
    CPU_ZERO(&set);        // 清空CPU集
    CPU_SET(0, &set);      // 添加CPU 0

    // 设置当前进程的亲和性
    if (sched_setaffinity(0, sizeof(cpu_set_t), &set) == -1) {
        perror("sched_setaffinity");
        return 1;
    }

    // 现在，当前进程将只在CPU 0上运行
    while (1) {
        // 模拟持续运行的进程
    }
    return 0;
}
```
这个程序将当前进程绑定到CPU核心0上。
其他方法
+ 使用系统调度器配置：在某些系统中，如实时操作系统或使用特定的系统管理工具（如numactl），也可能有设置CPU亲和性的方法。
+ 在虚拟化环境中：在使用虚拟化技术（如VMware, KVM等）时，也可以在虚拟机管理器中设置虚拟机的CPU亲和性。

### 进程间通信的方式
+ 网络应用：套接字是网络服务中最常用的IPC形式，适用于不同机器上的进程间通信。例如，Web服务器和客户端之间的通信大多采用TCP或UDP套接字。
+ 分布式系统：在复杂的分布式系统中，如微服务架构，套接字用于服务之间的消息传递和数据共享。

2. 消息队列：
+ 解耦和异步处理：在需要将消息发送者和接收者解耦的系统中，消息队列提供了一种有效的方法。例如，电子商务平台可能使用消息队列处理订单、支付和物流更新，以提高系统的响应性和扩展性。
+ 系统间通信：在多个系统或应用之间同步信息时，消息队列可以作为缓冲区，确保数据不会因为处理延迟而丢失。

3. 共享内存：
+ 性能敏感的应用：在对性能要求极高的应用中，如实时系统或高频交易系统，共享内存是首选，因为它几乎不引入额外的时间延迟。
+ 多媒体处理：在视频编辑和处理软件中，共享内存用于快速交换大量数据。

4. 信号量和共享内存的组合：
+ 资源管理：在需要多个进程共同访问和管理资源（如打印机队列或数据库缓存）时，信号量用于同步访问，防止资源冲突。

5. 信号 (Signals)：
+ 简单通知：信号用于操作系统或应用程序中，以通知进程发生了某些事件（如终止请求或外部条件变化）。

6. 内存映射文件：
+ 大数据交换：当进程需要交换大量数据时，内存映射文件是一个有效的选择。例如，在需要处理大型数据集的科学计算应用中常见。

7. 条件变量和互斥锁：
线程同步：虽然这些通常用于线程间的通信，但它们也可以用于属于同一父进程的不同进程之间的同步，尤其是在使用轻量级进程（如Linux中的线程）时。

### 说一下共享内存的特点，如何确定数据的边界，如何提高共享内存的并发
#### 共享内存的特点
+ 高效性：由于省去了数据复制的步骤，共享内存通常是所有IPC机制中最快的。
+ 直接访问：进程可以如访问自己的局部变量那样直接对共享内存区进行读写操作。
+ 灵活性：程序员必须自行设计数据结构以适应共享内存，这提供了很高的灵活性但也增加了复杂性。
+ 复杂的同步需求：由于多个进程可能同时读写共享内存，必须仔细设计同步机制以防止数据竞争和不一致。
#### 确定数据的边界
在使用共享内存时，确定数据的边界是关键的。这通常涉及到以下方面：

+ 数据结构设计：在共享内存中使用明确的数据结构（如结构体），并确保每个进程都遵循这一结构来访问数据。
+ 对齐和大小：确保共享内存中的数据结构在不同的系统和编译器中具有一致的对齐和大小，这可以通过在结构体中使用固定大小的类型（如stdint.h中定义的int32_t、int64_t等）和使用编译器指令（如#pragma pack）来控制结构体的对齐。

#### 提高共享内存的并发
要提高共享内存的并发能力，关键是使用有效的同步机制：

1. 互斥锁（Mutexes）：使用互斥锁保护对共享内存的访问。任何时候，只允许一个进程写入共享内存。
2. 读写锁（RW Locks）：如果读操作远多于写操作，使用读写锁可以提高效率。读写锁允许多个读者同时访问共享内存，但写者访问时必须独占。
3. 信号量（Semaphores）：可以用来控制对共享内存的并发访问，特别是在处理生产者-消费者问题时很有效。
4. 原子操作：对于简单的数据更新，使用原子操作（如__sync_add_and_fetch等GCC内建函数）可以避免引入显式的锁机制。
5. 无锁编程（Lock-Free Programming）：设计无锁的数据结构，如无锁队列，可以极大提高并发性。这通常需要利用原子操作和精心设计的算法来确保数据一致性。

### 什么是硬中断和软中断，什么是中断的上半部和下半部，中断里能否用sleep函数，中断内如何加锁

#### 硬中断和软中断
+ 硬中断（Hardware Interrupt）：

硬中断通常由硬件设备产生，用于通知CPU有紧急事件需要处理，例如硬件设备完成数据传输。
硬中断可以由任何外部设备触发，如网络卡、磁盘、键盘等。
它们通常在非常低的操作系统层次上处理，需要快速响应，因为它们直接与硬件的物理行为相关联。

+ 软中断（Software Interrupt）：

软中断，也称为软件中断，通常是操作系统内核产生的中断，用于处理程序执行中的异常情况，或操作系统服务请求，比如系统调用。
软中断也可以用来处理或延续硬中断的工作，它们不直接由硬件触发，而是由系统内部或其他中断处理程序触发。

#### 中断的上半部和下半部
+ 上半部（Top Half）：

上半部是中断处理的第一部分，也称为中断处理程序（Interrupt Handler）。
它响应硬件中断，执行必要的最小处理，然后迅速返回。上半部的处理是立即的，并且在中断上下文中运行，因此它不能睡眠或执行其他可能导致阻塞的操作。

+ 下半部（Bottom Half）：

由于上半部需要快速执行且不能进行耗时操作，下半部用来处理上半部中断处理留下的任务。
下半部可以延迟执行，不在中断上下文中运行，可以安全地执行较长的处理任务，包括可能阻塞的操作。
下半部的实现方法包括任务队列、工作队列、软中断（Softirqs）和任务下半部（Tasklets）等。

#### 中断中使用sleep函数
在中断处理的上半部中，绝对不能使用sleep或任何其他可能导致阻塞的函数。因为中断处理程序必须快速完成且不能被阻塞。
在中断的下半部，可以使用可能导致阻塞的函数，如sleep，因为下半部不在中断上下文中运行。

#### 中断内如何加锁
在中断处理程序中，尤其是上半部中，不能使用普通的互斥锁（如mutex），因为这些锁在尝试锁定时如果锁已被占用，会导致线程睡眠，这在中断上下文中是不允许的。
应使用**自旋锁（spinlocks）或序列锁（seqlocks）**等特殊类型的锁。自旋锁在尝试获取锁时会持续循环检查而不是睡眠，适合于上半部中断处理中使用。
在中断的下半部，可以使用普通锁机制，因为下半部允许睡眠和阻塞。
总之，理解中断的不同类型和处理方式对于开发低级别的驱动程序或进行系统级优化至关重要。正确地处理中断可以显著提高系统的性能和响应速度

### freertos 和 linux的区别
#### FreeRTOS
FreeRTOS 是一个开源的、小型的、可裁剪的实时操作系统（RTOS）。它专为微控制器和小型微处理器设计，广泛用于嵌入式设备和物联网（IoT）设备中。

+ 资源占用小：FreeRTOS可以在极少的内存中运行（几百到几千字节的RAM，和简单的几KB ROM）。
+ 实时性：提供了实时任务调度，支持多任务处理，能够保证关键任务的及时响应。
+ 简单的API：提供简单直接的API来管理任务、信号量、队列等。
+ 可裁剪性：核心功能十分精简，可以根据需要添加或剥离组件。
+ 专用性：适用于资源受限的单片机和微控制器。

#### Linux
Linux 是一个功能强大的通用操作系统，基于Unix。它支持广泛的硬件架构，适用于个人电脑、服务器、移动设备甚至嵌入式系统。

+ 功能全面：提供了完整的多用户、多任务、设备驱动、网络功能、图形界面等。
+ 资源需求相对较高：相对于FreeRTOS，Linux需要更多的内存和处理能力（至少数百MB内存和较复杂的CPU架构）。
+ 非实时操作系统：标准的Linux内核不是实时的，尽管有实时补丁（如PREEMPT_RT）可以增强其实时性能。
+ 复杂性高：Linux系统的复杂性远高于FreeRTOS，包括内核、用户空间、系统调用、多种文件系统等。

#### 主要区别
+ 目标硬件：FreeRTOS主要面向低功耗、低资源的微控制器；Linux则面向从嵌入式系统到高性能服务器的广泛设备。
+ 系统复杂性：Linux提供的特性和功能要比FreeRTOS多得多，因此系统更为复杂。
+ 实时性：FreeRTOS是一个实时操作系统，适合需要快速和确定的响应时间的应用；而Linux则适用于需要复杂处理和多功能集成的环境，虽然可以通过扩展成为实时系统，但默认情况下不是。
+ 开发和维护：在FreeRTOS上开发通常要求对硬件有更深入的了解，而Linux则提供了更多的抽象和资源，有助于处理复杂的应用程序。
#### 应用场景
+ FreeRTOS：适用于家用电器、工业控制、汽车电子、简单的物联网设备等。
+ Linux：适用于需要复杂操作、高级接口和高度互动性的应用，如个人计算机、商业服务器、复杂的嵌入式系统等。

### linux 如何实现完全公平调度
#### CFS的核心概念
1. 虚拟运行时间（Virtual Runtime，vruntime）：

每个进程都有一个vruntime表示该进程的CPU使用时间。CFS尝试平衡每个进程的vruntime，使得所有进程都有机会公平地运行。
vruntime的计算基于进程的权重，权重低的进程消耗vruntime较慢，从而获得较长的CPU时间。

2. 红黑树：

CFS使用一种红黑树（一种自平衡二叉查找树）来存储所有可运行的进程。这使得查找下一个应该运行的进程（即vruntime最小的进程）非常高效。

#### CFS的工作流程
1. 选择下一个任务：
调度器选择vruntime值最小的任务作为下一个运行的任务，这确保了公平性。
2. 任务切换：
当前运行的任务在阻塞、完成或需要调度时（如时间片用尽），CFS会触发任务切换。
更新当前任务的vruntime，并将其重新放入红黑树中的合适位置。
3. 睡眠和唤醒：

当任务进入睡眠状态时，它会从调度器的红黑树中移除。
被唤醒的任务会根据其vruntime被插入到红黑树中合适的位置。
4. 负载平衡：

在多处理器系统中，CFS还会负责负载平衡，即尝试平均分配任务到各个CPU核心，以避免某个核心过载而其他核心空闲的情况。
#### 实现公平性的技术手段
+ 时间片的动态调整：CFS不使用固定的时间片，而是根据系统负载动态调整每个任务的时间片。
+ 权重与优先级：虽然CFS主要关注公平性，但它仍支持不同的优先级。通过调整每个任务的权重，高优先级任务会获得更多的CPU时间。
+ 优化的唤醒逻辑：为了减少延迟，CFS尽可能地在任务被唤醒时立即运行它，特别是对于交互式任务。
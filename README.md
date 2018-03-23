# Single Source Shortest Path Problem

#### 一. Preface
1. The Intel® Xeon Phi™ Processor Architecture:    
Xeon Phi 7210: 32 tiles / 64 cores (+ 6 tiles / 12 cores for yield recovery)
<img src="https://software.intel.com/sites/default/files/managed/aa/e0/c02-f02-1024x1063.png" width="300">

2. Official release: max memory bandwidth 102 GB/s.


#### 二. nodes:
(在Xu基础上,将每个64B的结构体内容全部填充, 避免编译器的优化. 实验结果表明将内容
填充完成的计算和只有一个整数的计算, 带宽相差非常大, 可能是: 计算时间增加或
其他原因)

1. nodes/sum-all.cc: 200 GB/s, 顺序扫描内存块, 并将内存块中存储的整形数相加.

2. nodes/sum-rank.cc: 157 GB/s, 使用一个数组来遍历内存块的索引a[index[i]], 即
访问a[]中元素之前, 需要先在index[]中找到数组a[]中的位置. index[]中存放的数据为
一个连续的实数序列.

3. sum-rank-random.cc: 41 GB/s, 与(2)中类似, 扫描内存中的数组a[index[i]], 不同的
是index[]中存储的是一个随机的实数序列.

#### 三. nodes-with-neighbors
1. sum-cont-type.cc:

2. sum-uncont-type-rank.cc: 

3. sum-uncont-type-with-neighbors.cc: 15 GB/s, 顺序扫描内存块中'图顶点', 并累加
其邻居所存储的数据.

4. sum-uncont-type-with-neighbors-rank.cc: 13 GB/s, 随机访问内存块中'图顶点', 并
累加其邻居所存储的数据.

5. sum-uncont-type-with-neighbors-random-rank.cc: 


#### 四. nodes-with-neighbors-prefetch
改动: 通过编译选项`-O3 –xmic-avx512 –qopt-prefetch=<n>`指导编译器预取

1. 在源代码prefetch.cc中使用指示语句:
  	预取方法    |       带宽      | 注释 
	------------------|-----------------|-----------
	 without prefetch |  10 - 16 GB/s   | 无
	 \_MM\_HINT\_T0   |       30 GB/s   | 无
	 \_MM\_HINT\_T1   |       33 GB/s   | 无
	 \_MM\_HINT\_T2   |       34 GB/s   | 无
	 \_MM\_HINT\_NTA  |       20 GB/s   | 无

2. 使用编译选项:    
O3 –xmic-avx512 –qopt-prefetch=<n>:    
	预取方法 |    带宽       | 注释 
	---------|---------------|-----------
	n = 0    | 10 - 16 GB/s  | 无
	n = 2    |  16 GB/s      | 无
	n = 3    | 10 - 14 GB/s  | 无
	n = 4    | 同上          | 无
	n = 5    | 26 - 30 GB/s  | 无

- 0    This is the default and if you omit the –qopt-prefetch option, then no auto-prefetching is done by the compiler    
- 2    This is the default if you use only –qopt-prefetch with no explicit “<n>” argument. Insert prefetches for direct references where the compiler thinks the hardware prefetcher may not be able to handle it    
- 3    Prefetching is turned on for all direct memory references without regard to the hardware prefetcher    
- 4    Same as n=3 (currently)    
- 5    Additional prefetching for all indirect references (Intel® Advanced Vector Extensions 512 (Intel® AVX-512) and above)    
    - Indirect prefetches (hint 1) is done using AVX512-PF gatherpf instructions on Knights Landing (not all cases, but a subset)    
    - Extra prefetches issued for strided vector accesses (hint 0) to cover all cache-lines`


#### 五. 基于Xu 版本上的改动
1. nodes/中局部变量rep: 1000 -->1, 原因是怀疑并行的位置会导致进程间共享第一个
进程读入的数据, 实际上读入的次数可能少于rep=1000. (在nodes-with-neighbors中由于
每个线程扫描内存相距较远, 经测试发现rep=1或1000, 带宽变化不大.)

2. nodes/sum-all.cc nodes/sum-rank.cc中计算内存直接乘以64, 当扫描的内存区域没有
对齐或对齐出错时, 内存区域实际上只能乘以数组中单个元素的大小.

3. `int a[maxn] __attribute__((aligned(64)));` 对齐出错. 我估计Xu的原意是想将
数组中a[]中每个元素对齐为64B, 但对齐多用于对齐结构体或成员变量. 并且在函数main()
中, 在计算内存块memory大小时, 乘了64, 说明Xu 的原意是想将其对齐, 或者没想将其
对齐为64B, 但违反了(2)中的计算出错.

4. nodes/sum-rank.cc 中对扫描的内存计算漏掉了rank[]数组, 可能造成计算的带宽
不准确.

5. nodes-with-neighbors/sum-uncont-type-with-neighbors.cc 中计算memory, 去除了
` * 4`, 想不出来为什么需要` * 4`.

/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_SCHED_STAT_H
#define _LINUX_SCHED_STAT_H

#include <linux/percpu.h>
#include <linux/kconfig.h>

/*
 * Various counters maintained by the scheduler and fork(),
 * exposed via /proc, sys.c or used by drivers via these APIs.
 *
 * ( Note that all these values are aquired without locking,
 *   so they can only be relied on in narrow circumstances. )
 */

extern unsigned long total_forks;
extern int nr_threads;
DECLARE_PER_CPU(unsigned long, process_counts);
extern int nr_processes(void);
extern unsigned int nr_running(void);
extern bool single_task_running(void);
extern unsigned long nr_iowait(void);
extern unsigned long nr_iowait_cpu(int cpu);

#ifdef CONFIG_SMP
extern void sched_update_nr_prod(int cpu, long delta, bool inc);
extern unsigned int sched_get_cpu_util(int cpu);
extern u64 sched_get_cpu_last_busy_time(int cpu);
#else
static inline void sched_update_nr_prod(int cpu, long delta, bool inc)
{
}
static inline unsigned int sched_get_cpu_util(int cpu)
{
	return 0;
}
static inline u64 sched_get_cpu_last_busy_time(int cpu)
{
	return 0;
}
#endif

static inline int sched_info_on(void)
{
	return IS_ENABLED(CONFIG_SCHED_INFO);
}

#ifdef CONFIG_SCHEDSTATS
void force_schedstat_enabled(void);
#endif

#endif /* _LINUX_SCHED_STAT_H */

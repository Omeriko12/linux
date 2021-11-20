#ifndef _NICMEM_H
#define _NICMEM_H

#include <linux/highmem.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <net/dst.h>
#include <net/sock.h>
#include <net/nicmem.h>

struct net_device *get_netdev_for_sock(struct sock *sk);

#endif	/* _NICMEM_H */

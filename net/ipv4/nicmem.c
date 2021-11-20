#include <linux/highmem.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <net/dst.h>
#include <net/sock.h>
#include <net/nicmem.h>

/* We assume that the socket is already connected */
struct net_device *get_netdev_for_sock(struct sock *sk)
{
	printk("entered get_netdev_for_sock");
	struct dst_entry *dst = sk_dst_get(sk);
	struct net_device *netdev = NULL;

	if (likely(dst)) {
		netdev = netdev_sk_get_lowest_dev(dst->dev, sk);
		dev_hold(netdev);
	}

	dst_release(dst);

	return netdev;
}

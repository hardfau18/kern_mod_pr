#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/net_tstamp.h>
#include <linux/netdevice.h>
#include <linux/u64_stats_sync.h>
#include <net/rtnetlink.h>

#define DRV_NAME "dummy"

static int what_init(struct net_device *dev) { return 0; }

static void dummy_dev_uninit(struct net_device *dev) {}

static const struct net_device_ops dummy_netdev_ops = {
    .ndo_init = what_init,
    .ndo_uninit = dummy_dev_uninit,
};

static void dummy_setup(struct net_device *dev) {
  ether_setup(dev);
  dev->netdev_ops = &dummy_netdev_ops;
  eth_hw_addr_random(dev);
}

struct net_device *dev_dummy;
static struct rtnl_link_ops dummy_link_ops __read_mostly = {
    .kind = DRV_NAME,
    .setup = dummy_setup,
};

static int __init dummy_init_one(void) {
  int err;

  down_write(&pernet_ops_rwsem);
  rtnl_lock();
  rtnl_link_register(&dummy_link_ops);
  dev_dummy = alloc_netdev(0, "dummy%d", NET_NAME_ENUM, dummy_setup);
  if (!dev_dummy)
    return -ENOMEM;

  err = register_netdevice(dev_dummy);
  if (err < 0)
    goto err;
  return 0;

err:
  free_netdev(dev_dummy);
  return err;
}

static void __exit dummy_cleanup_module(void) {
  unregister_netdev(dev_dummy);
  free_netdev(dev_dummy);
}

module_init(dummy_init_one);
module_exit(dummy_cleanup_module);
MODULE_LICENSE("GPL");

#include<linux/types.h>
#include<linux/netdevice.h>

static int start_here(void);
static void end_here(void);
static void cpmac_init(struct net_device*);

struct cpmac_priv{
    uint8_t status;
};

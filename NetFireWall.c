#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/skbuff.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

#include "KernelMsgHandler.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xsc");

extern struct sock *nlsk;

/************ pre routing ***************/
static struct nf_hook_ops nfho_pre_routing;

unsigned int nf_hook_pre_routing(
    void *priv,
    struct sk_buff *skb,
    const struct nf_hook_state *state
) {
    return NF_DROP;
}

static void nfw_register_pre_routing(void) {
    nfho_pre_routing.hook = nf_hook_pre_routing;
    nfho_pre_routing.pf = PF_INET;
    nfho_pre_routing.hooknum = NF_INET_PRE_ROUTING;
    nfho_pre_routing.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho_pre_routing);
}

/************ local in ***************/
static struct nf_hook_ops nfho_local_in;

unsigned int nf_hook_local_in(
    void *priv,
    struct sk_buff *skb,
    const struct nf_hook_state *state
) {
    return NF_DROP;
}

static void nfw_register_local_in(void) {
    nfho_local_in.hook = nf_hook_local_in;
    nfho_local_in.pf = PF_INET;
    nfho_local_in.hooknum = NF_INET_LOCAL_IN;
    nfho_local_in.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho_local_in);
}

/************ forward ***************/
static struct nf_hook_ops nfho_forward;

unsigned int nf_hook_forward(
    void *priv,
    struct sk_buff *skb,
    const struct nf_hook_state *state
) {
    return NF_DROP;
}

static void nfw_register_forward(void) {
    nfho_forward.hook = nf_hook_forward;
    nfho_forward.pf = PF_INET;
    nfho_forward.hooknum = NF_INET_FORWARD;
    nfho_forward.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho_forward);
}

/************ local out ***************/
static struct nf_hook_ops nfho_local_out;

unsigned int nf_hook_local_out(
    void *priv,
    struct sk_buff *skb,
    const struct nf_hook_state *state
) {
    return NF_DROP;
}

static void nfw_register_local_out(void) {
    nfho_local_out.hook = nf_hook_local_out;
    nfho_local_out.pf = PF_INET;
    nfho_local_out.hooknum = NF_INET_LOCAL_OUT;
    nfho_local_out.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho_local_out);
}

/************ post routing ***************/
static struct nf_hook_ops nfho_post_routing;

unsigned int nf_hook_post_routing(
    void *priv,
    struct sk_buff *skb,
    const struct nf_hook_state *state
) {
    return NF_DROP;
}

static void nfw_register_post_routing(void) {
    nfho_post_routing.hook = nf_hook_post_routing;
    nfho_post_routing.pf = PF_INET;
    nfho_post_routing.hooknum = NF_INET_POST_ROUTING;
    nfho_post_routing.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho_post_routing);
}

/************ init netlink ***************/
struct netlink_kernel_cfg nl_nfw_cfg = {
	0,	//groups
	0,	//flags
	NULL,	//input
	NULL,	//cb_mutex
	NULL,	//bind
	NULL,	//unbind
	NULL,	//compare
};

static void netlink_init(void)
{
    printk("netlink of nfw module initializing...\n");
    nlsk = netlink_kernel_create(&init_net, NETLINK_NET_FIRE_WALL, &nl_nfw_cfg);
    if (!nlsk) {
        printk("can not create a netlink socket\n");
        return;
    }
    printk("netlink_kernel_create() success, nlsk = %p\n", nlsk);
}

static void netlink_release(void) {
    sock_release(nlsk->sk_socket);
    printk("Netlink test module exit!\n");
}

/************ module config ***************/
static int nfw_init(void) {
    printk("nfw opened ...\n");

    // register hook func
    nfw_register_pre_routing();
    nfw_register_local_in();
    nfw_register_forward();
    nfw_register_local_out();
    nfw_register_post_routing();

    // init netlink socket
    netlink_init();

    return 0;
}

static void nfw_exit(void)
{
    printk("nfw closed ...\n");

    // unregister hook func
    nf_unregister_net_hook(&init_net, &nfho_pre_routing);
    nf_unregister_net_hook(&init_net, &nfho_local_in);
    nf_unregister_net_hook(&init_net, &nfho_forward);
    nf_unregister_net_hook(&init_net, &nfho_local_out);
    nf_unregister_net_hook(&init_net, &nfho_post_routing);
    
    // release netlink socket
    netlink_release();
}

module_init(nfw_init);
module_exit(nfw_exit);

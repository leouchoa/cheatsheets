# Network Basic Commands

- To query a hostname from a DNS server: `nslookup` or `dig`.
- List and modify interfaces for the host: `ip link`
- List IPs addresses assigned to the interfaces: `ip addr`
- Assign the system with address `192.168.1.10/24`
to the network `eth0`: `ip addr add 192.168.1.10/24 dev eth0` (
only valid until reboot. If you want to persist, use the
`etc/network/interfaces` file)
- Show the existing routing config on a system: `route`.
It will display the Kernel routing table.
- Add a route: `ip route add <TARGET_NETWORK> via <ROUTING_HOST>`
- Check if ip forwarding is enabled on the host: modify the
`/proc/sys/net/ipv4/ip_forward` to have the entry `1` instead of `0`.

## How To Give a Host a Name

Modify the `/etc/hosts` to have the IP address and it's name. Example:

```bash
cat /etc/hosts
# 192.168.1.11 cool_website
# 192.168.1.12 cool_website_db
# 192.168.1.13 cool_website_ml_model
```

## How To Point a Machine To a DNS Server

In each machine, go to the `/etc/resolv.conf` and add the
DNS server hostname, along with it's IP address. Example:

```bash
cat /etc/resolv.conf
# nameserver 192.168.1.100
```

## Resolving Subdomains

Suppose you're at your company and want to ping the site
`web.mycompany.com`. But instead of writing `ping web.mycompany.com`
everytime you to simply use `ping web`. In that case go to
`etc/resolv.conf` and add `search mycompany.com`.

```bash
cat /etc/resolv.conf
# nameserver 192.168.1.100
# search mycompany.com
```

This works because the host excludes the domain and works
only with the subdomain. You can even put additional search domains:

```bash
cat /etc/resolv.conf
# nameserver 192.168.1.100
# search mycompany.com prod.mycompany.com
```

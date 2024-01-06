# Network Basic Commands

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

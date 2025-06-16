# Cisco IOS CLI commands

## DHCP configuration
```bash
<Enter>
enable
config t # configure terminal

ip dhcp pool <name_of_pool> # create a DHCP pool
network 192.168.0.0 255.255.255.0 # define the network
default-router 192.168.0.1 # define the default gateway
dns-server 192.168.0.3 # define the DNS server
exit # exit the DHCP pool configuration

exit # exit the configuration mode
copy running-config startup-config # save the configuration
```

## NAT configuration
```bash
<Enter>
enable
config t # configure terminal

interface FastEthernet 0/0 # enter the interface configuration mode
ip nat inside # define the inside interface
exit # exit the interface configuration mode

interface Serial 0/0/0 # enter the interface configuration mode
ip nat outside # define the outside interface
exit # exit the interface configuration mode

# create an access list, 0.0.0.31 specfies the mask of bits that can vary
access-list 1 permit 192.168.0.1 0.0.0.31 

# extended access list
ip access-list extended nat-internet
permit ip 192.168.0.0 0.0.0.255 193.231.20.0 0.0.0.255
permit ip 192.168.1.0 0.0.0.255 193.231.20.0 0.0.0.255
permit ip 192.168.2.0 0.0.0.255 193.231.20.0 0.0.0.255
permit ip 192.168.3.0 0.0.0.255 193.231.20.0 0.0.0.255

# define a pool of addresses to be allocated to the clients when NAT-ted.
ip nat pool ISP 193.226.40.1 193.226.40.1 netmask 255.255.255.252

# Define the NAT policy
ip nat inside source list 1 pool ISP overload # source and a NAT pool or single IP
# or
ip nat inside source list 1 interface Serial0/1/1 overload 

exit # exit the configuration mode
copy running-config startup-config # save the configuration
```
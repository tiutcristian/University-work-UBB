# Network creation flow

1. Compute subnets
2. Add the elements
    - Add routers (+ add interfaces)
    - Add switches
    - Connect them + add computers
3. Create the networks
    - establish the networks on routers  
        (through GUI on the corresponding interface)

3. DHCP configuration
    - establish the DHCP 
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

    - set PC connections to DHCP (wait for the IP to be assigned)

4. NAT configuration

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

    # define a pool of addresses to be allocated to the clients when NAT-ted.
    ip nat pool ISP 193.226.40.1 193.226.40.1 netmask 255.255.255.252

    # Define the NAT policy
    ip nat inside source list 1 pool ISP overload # source and a NAT pool or single IP

    exit # exit the configuration mode
    copy running-config startup-config # save the configuration
    ```

5. RIP configuration

    ```bash
    <Enter>
    enable
    config t # configure terminal

    router rip # enter the RIP configuration mode
    version 2 # set the RIP version
    network 192.168.0.0 # define the network
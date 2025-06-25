This is NetLink program sample.

### build NetLink sample

```shell
g++ -std=c++20 -Wall -I/usr/include/libnl3 \
    main.cpp -o netlink_sample \
    $(pkg-config --cflags --libs libnl-3.0 libnl-route-3.0)

./netlink_sample
# outputs like below
#
# Interface: lo, Index: 1
# Interface: tunl0, Index: 2
# Interface: gre0, Index: 3
# Interface: gretap0, Index: 4
# Interface: erspan0, Index: 5
# Interface: ip_vti0, Index: 6
# Interface: ip6_vti0, Index: 7
# Interface: sit0, Index: 8
# Interface: ip6tnl0, Index: 9
# Interface: ip6gre0, Index: 10
# Interface: eth0, Index: 19
```


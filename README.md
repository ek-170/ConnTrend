## What is ConnTrend?

**ConnTrend** is a lightweight command-line monitor that tracks how many ephemeral network ports your Linux host is really using—*in real time and across both TCP and UDP*.
By sampling the kernel’s Netlink data at a user-defined interval, ConnTrend records:

* the total size of the current ephemeral-port range
* how many ports are occupied, free, or held in critical states such as **TIME\_WAIT**
* fine-grained TCP state counts (ESTABLISHED, SYN, CLOSE\_WAIT, etc.) and UDP usage

Results are streamed to **CSV or JSON**, ready for quick grepping, long-term archiving, or dashboard visualization.
With this single tool you can:

* spot port-exhaustion incidents **before** outbound connections start failing
* distinguish whether the root cause is TIME\_WAIT buildup, SYN floods, application leaks, or heavy UDP traffic
* keep a concise time-series log that fits easily into existing observability stacks.

In short, ConnTrend turns low-level socket statistics into a clear, compact timeline—so you always know how close your system is to running out of ports.

### Usage

```shell
conntrend [FLAGS]

Required most-used flags
  -i, --interval_sec <int>        Sampling interval in seconds (default: 5)

Optional flags
  -d, --duration_sec <int>        Total run time in seconds. 0 → run until Ctrl-C
                                  (default: 60)
  -v                              vorbose output
  -o, --output <file path|->      Output file path or "-" for stdout (default: "-")
  -p, --protocol <tcp|udp|all>    Protocol(s) to count (default: all)
      --format <csv|json>         Output format (default: csv)
  -h, --help                      usage of ConnTrend

```

### Output

```csv
# conntrend 0.1  sampling=5s  duration=60s  range_init=32768-60999
# columns: epoch_ms,total_port,used,free,udp_used,tcp_used,time_wait,estab,syn,close_wait,last_ack,fin_wait
1750906800000,28232,156,28030,18,138,46,120,2,5,2,9
1750906805000,28232,159,28027,18,141,47,122,2,6,2,9
1750906810000,28232,162,28024,19,143,48,124,3,6,2,10
...
#
# summary: start_ms=1750906800000,end_ms=1750906860000,elapsed_sec=60,\
#          samples=12,peak_used=162,peak_time_wait=48,min_free=28024,\
#          min_total_port=28232,max_total_port=28232

```

### Development

```shell
make dbuild
make drun
```


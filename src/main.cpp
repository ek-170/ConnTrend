#ifdef __cplusplus
extern "C"
{
#endif

#include <netlink/netlink.h>

#ifdef __cplusplus
}
#endif

#include <iostream>
#include <optional>
#include <filesystem>
#include <cxxopts.hpp>

enum class Protocol
{
    TCP,
    UDP,
    All,
};

std::istream& operator>>(std::istream& is, Protocol& protocol) {
    std::string token;
    is >> token;
    if (token == "tcp") protocol = Protocol::TCP;
    else if (token == "udp") protocol = Protocol::UDP;
    else if (token == "all") protocol = Protocol::All;
    else is.setstate(std::ios::failbit);
    return is;
}

enum class Format
{
    CSV,
    JSON,
};

std::istream& operator>>(std::istream& is, Format& format) {
    std::string token;
    is >> token;
    if (token == "csv") format = Format::CSV;
    else if (token == "json") format = Format::JSON;
    else is.setstate(std::ios::failbit);
    return is;
}

class Option {
private:
    Protocol protocol{ Protocol::All };
    Format format{ Format::CSV };
    int interval{ 5 };
    int duration{ 60 };
    std::string output{ "" };
    bool verbose{ false };
public:
    Option () = default;

    Option(cxxopts::ParseResult result):
        protocol(result["protocol"].as<Protocol>()), 
        format(result["format"].as<Format>()), 
        interval(result["interval"].as<int>()), 
        duration(result["duration"].as<int>()), 
        output(result["output"].as<std::string>()), 
        verbose(result.count("verbose") > 0){}

    Protocol getProtocol() const { return protocol; }
    Format getFormat() const { return format; }
    int getInterval() const { return interval; }
    int getDuration() const { return duration; }
    std::string getOutput() const { return output; }
    bool getIsVerbose() const { return verbose; }

    friend std::ostream& operator<<(std::ostream& os, const Option& opt) {
        os << "Option {\n"
           << "  protocol: ";
        switch(opt.protocol) {
            case Protocol::TCP: os << "TCP"; break;
            case Protocol::UDP: os << "UDP"; break;
            case Protocol::All: os << "All"; break;
        }
        os << "\n  format: ";
        switch(opt.format) {
            case Format::CSV: os << "CSV"; break;
            case Format::JSON: os << "JSON"; break;
        }
        os << "\n  interval: " << opt.interval
           << "\n  duration: " << opt.duration
           << "\n  output: \"" << opt.output << "\""
           << "\n  verbose: " << std::boolalpha << opt.verbose
           << "\n}";
        return os;
    }
};

int main(int argc, char *argv[])
{

    cxxopts::Options options("netlink_example", "A simple example using netlink with cxxopts");

    options.add_options()
        ("h,help", "Show help")
        ("p,protocol", "Protocol to use. values \"tcp\", \"udp\", \"all\" are accepted)", cxxopts::value<Protocol>()->default_value("all"))
        ("i,interval", "Sampling interval in seconds", cxxopts::value<int>()->default_value("5"))
        ("d,duration", "Total run time in seconds. 0 → run until Ctrl-C", cxxopts::value<int>()->default_value("60"))
        ("o,output", "Output file path. if not provided, print to stdout", cxxopts::value<std::string>()->default_value(""))
        ("f,format", "Output format (CSV, JSON)", cxxopts::value<Format>()->default_value("csv"))
        ("v,verbose", "Enable verbose output");

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        return 0;
    }

    Option option(result);
    std::cout << option << std::endl;

    // netlink操作
    // struct nl_cache *route_alloc_cache();

    return 0;
}

// netlink_example.cpp
// libnl3 を使ってネットワークインターフェース一覧を取得するサンプル

#include <iostream>
#include <memory>
#include <stdexcept>

extern "C" {
#include <netlink/netlink.h>
#include <netlink/socket.h>
#include <netlink/cache.h>
#include <netlink/route/link.h>
}

namespace {

// RAII で管理する Netlink ソケットクラス
class NetlinkSocket {
 public:
  NetlinkSocket() {
    sock_.reset(nl_socket_alloc());
    if (!sock_) {
      throw std::runtime_error("Failed to allocate netlink socket");
    }
    if (nl_connect(sock_.get(), NETLINK_ROUTE) < 0) {
      throw std::runtime_error("Failed to connect netlink socket");
    }
  }

  // ソケット取得
  nl_sock *get() const { return sock_.get(); }

 private:
  struct NlSockDeleter {
    void operator()(nl_sock *sock) const noexcept {
      nl_socket_free(sock);
    }
  };

  std::unique_ptr<nl_sock, NlSockDeleter> sock_;
};

}  // namespace

int main() {
  try {
    NetlinkSocket nlSock;

    // インターフェース情報キャッシュ取得
    nl_cache *linkCache = nullptr;
    if (rtnl_link_alloc_cache(nlSock.get(), AF_UNSPEC, &linkCache) < 0) {
      std::cerr << "Failed to allocate link cache" << std::endl;
      return 1;
    }
    // キャッシュ自動解放
    std::unique_ptr<nl_cache, decltype(&nl_cache_free)> cachePtr(
        linkCache, &nl_cache_free);

    // インターフェース一覧を表示
    for (nl_object *obj = nl_cache_get_first(linkCache);
         obj;
         obj = nl_cache_get_next(obj)) {
      auto *link = reinterpret_cast<rtnl_link *>(obj);
      const char *name = rtnl_link_get_name(link);
      int index = rtnl_link_get_ifindex(link);
      std::cout << "Interface: " << (name ? name : "<unknown>")
                << ", Index: " << index << std::endl;
    }

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}

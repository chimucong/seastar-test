#include "seastar/core/app-template.hh"
#include "seastar/core/reactor.hh"

#include <dlfcn.h>
#include <iostream>
#include <assert.h>
// using dl_iterate_fn = int (*)(int (*callback)(struct dl_phdr_info *info, size_t size, void *data), void *data);
// int main1(int argc, char **argv)
// {
//   auto fn = dlsym(RTLD_NEXT, "dl_iterate_phdr");
//   std::cout << "dl_iterate_phdr: " << std::hex << fn << std::endl;
//   return 0;
// }
using dl_iterate_fn = int (*)(int (*callback)(struct dl_phdr_info *info, size_t size, void *data), void *data);

[[gnu::no_sanitize_address]] static dl_iterate_fn dl_iterate_phdr_org()
{
  std::cout << "dl_iterate_phdr_org()" << std::endl;
  static dl_iterate_fn org = [] {
    std::cout << "lambda()" << std::endl;
    auto org = (dl_iterate_fn)dlsym(RTLD_NEXT, "dl_iterate_phdr");
    assert(org);
    return org;
  }();
  return org;
}

int main1(int argc, char **argv)
{
  auto fn = dl_iterate_phdr_org();
  auto fn1 = dl_iterate_phdr_org();
  std::cout << "fn: " << std::hex << (void *)fn << std::endl;
  return 0;
}

int main(int argc, char **argv)
{
  main1(argc, argv);
  seastar::app_template app;
  // app.add_options()(
  //     "mkkey", "generate a new secret key. "
  //              "This is normally used in combination with --mkfs")(
  //     "mkfs", "create a [new] data directory")(
  //     "debug", "enable debug output on all loggers");
  // app.run(argc, argv, [] {
  //         std::cout << "Hello world\n";
  //         return seastar::make_ready_future<>();
  // });
  return app.run(argc, argv, [] {
    std::cout << "Hello world\n";
    return seastar::make_ready_future<>();
  });
}
#include <Geode/Geode.hpp>
#include <Geode/loader/Mod.hpp>
#include <Geode/loader/Loader.hpp>

using namespace geode::prelude;

$on_mod(Loaded) {
    auto baseAddr = geode::base::get();

    #if defined(GEODE_IS_WINDOWS)

    // Windows patches
    Mod::get()->patch(
        reinterpret_cast<void*>(baseAddr + 0x32E240),
        { 0xB2, 0x01 }
    );

    Mod::get()->patch(
        reinterpret_cast<void*>(baseAddr + 0x32E0A3),
        { 0x41 }
    );

    #elif defined(GEODE_IS_IOS)

    Mod::get()->patch(
        reinterpret_cast<void*>(baseAddr + 0x24cdd1),
        { 0xac }
    );

    Mod::get()->patch(
        reinterpret_cast<void*>(baseAddr + 0x24cf84),
        { 0x21 }
    );

    #endif
}
#pragma once

#include <vector>

#include "devices/State.h"

namespace wml {
  namespace devices {
    namespace constructorOptions {
      struct ConnectionOptions {
        functions::R<void> onConnection = functions::none;
        functions::R<bool> enabled = functions::trueConst;
      };
    } // ns structs

    template <typename T>
    struct Connection {
      T *original;
      T *final;
      functions::R<void> onConnection;
      functions::R<bool> enabled;

      Connection(T *original, T *final, constructorOptions::ConnectionOptions opt = {}) :
        original(original),
        final(final),
        onConnection(opt.onConnection),
        enabled(opt.enabled) {};
    };
  } // ns devices
} // ns wml

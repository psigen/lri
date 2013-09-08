#include <stdint.h>
#include <vector>

#ifndef SRC_SHARED_PROTO_HELPRS_H
#define SRC_SHARED_PROTO_HELPRS_H

// Serializes a Protobuf message with a 32-bit length prefix to a provided
// buffer.
template <typename T>
SerializeWithLength(const T& message, std::vector<uint8_t>* buffer) {
}

#endif  // SRC_SHARED_PROTO_HELPRS_H

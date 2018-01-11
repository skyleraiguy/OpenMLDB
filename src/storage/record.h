//
// record.h
// Copyright (C) 2017 4paradigm.com
// Author wangtaize
// Date 2017-11-24
//

#ifndef RTIDB_RECORD_H
#define RTIDB_RECORD_H

#include "storage/segment.h"

namespace rtidb {
namespace storage {

const static uint32_t DATA_BLOCK_BYTE_SIZE = sizeof(DataBlock);
const static uint32_t KEY_ENTRY_BYTE_SIZE = sizeof(KeyEntry);
const static uint32_t SKIPLIST_HEADER_BYTE_SIZE = 12 * 8 + 8 + 8 + 16;

static inline uint32_t GetRecordSize(uint32_t value_size) {
    return value_size + DATA_BLOCK_BYTE_SIZE;
}

// the input height which is the height of skiplist node 
static inline uint32_t GetRecordPkIdxSize(uint8_t height, uint32_t key_size) {
    // slice key 16
    // height 8
    // value pointer 8
    return height * 8 + 8 + 8 + 16 + KEY_ENTRY_BYTE_SIZE + SKIPLIST_HEADER_BYTE_SIZE+ key_size;
}

static inline uint32_t GetRecordTsIdxSize(uint8_t height) {
    return height * 8 + 8 + 8 + 8;
}

}
}
#endif


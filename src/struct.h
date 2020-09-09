#pragma once

#include "types.h"
#include <map>

namespace bpftrace {

struct Bitfield
{
  bool operator==(const Bitfield &other) const;
  bool operator!=(const Bitfield &other) const;

  // Read `read_bytes` bytes starting from this field's offset
  size_t read_bytes;
  // Then rshift the resulting value by `access_rshift` to get field value
  size_t access_rshift;
  // Then logical AND `mask` to mask out everything but this bitfield
  size_t mask;
};

struct Field
{
  SizedType type;
  ssize_t offset;

  bool is_bitfield;
  Bitfield bitfield;
};

using FieldsMap = std::map<std::string, Field>;
using TupleFields = std::vector<Field>;

struct Struct
{
  int size; // in bytes
  FieldsMap fields;
};

struct Tuple
{
  size_t size; // in bytes
  int align;   // in bytes
  bool padded = false;
  TupleFields fields;

  static std::unique_ptr<Tuple> Create(std::vector<SizedType> fields);
  void Dump(std::ostream &os);
};

std::ostream &operator<<(std::ostream &os, const TupleFields &t);
} // namespace bpftrace

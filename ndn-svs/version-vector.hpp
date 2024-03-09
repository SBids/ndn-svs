/* -*- Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2012-2022 University of California, Los Angeles
 *
 * This file is part of ndn-svs, synchronization library for distributed realtime
 * applications for NDN.
 *
 * ndn-svs library is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation, in version 2.1 of the License.
 *
 * ndn-svs library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 */

#ifndef NDN_SVS_VERSION_VECTOR_HPP
#define NDN_SVS_VERSION_VECTOR_HPP

#include "common.hpp"

#include <map>

namespace ndn::svs {

class VersionVector
{
public:
  class Error : public std::runtime_error
  {
  public:
    using std::runtime_error::runtime_error;
  };

  using const_iterator = std::map<NodeID, SeqNo>::const_iterator;

  VersionVector() = default;

  /** Decode a version vector from ndn::Block */
  explicit
  VersionVector(const ndn::Block& encoded);

  /** Encode the version vector to a string */
  ndn::Block
  encode() const;

  /** Encode the version vector to a string */
  ndn::Block
  encodeAsStateVectorHash() const;

  /** Get a human-readable representation */
  std::string
  toStr() const;

  SeqNo
  set(const NodeID& nid, SeqNo seqNo)
  {
    m_map[nid] = seqNo;
    return seqNo;
  }

  SeqNo
  get(const NodeID& nid) const
  {
    auto elem = m_map.find(nid);
    return elem == m_map.end() ? 0 : elem->second;
  }

  const_iterator
  begin() const noexcept
  {
    return m_map.begin();
  }

  const_iterator
  end() const noexcept
  {
    return m_map.end();
  }

  bool
  has(const NodeID& nid) const
  {
    return m_map.find(nid) != end();
  }

private:
  std::map<NodeID, SeqNo> m_map;
  
  // Hash string into a 32-bit size_t
  boost::hash<std::string> URI_hash;
};

class VersionVectorHash
{
public:
  class Error : public std::runtime_error
  {
  public:
    using std::runtime_error::runtime_error;
  };

  using const_iterator = std::map<std::size_t, SeqNo>::const_iterator;

  VersionVectorHash() = default;

  /** Decode a version vector from ndn::Block */
  explicit
  VersionVectorHash(const ndn::Block& encoded);

  /** Encode the version vector to a string */
  ndn::Block
  encode() const;

  /** Get a human-readable representation */
  std::string
  toStr() const;

  SeqNo
  set(const std::size_t& hash, SeqNo seqNo)
  {
    m_map[hash] = seqNo;
    return seqNo;
  }

  SeqNo
  get(const std::size_t& hash) const
  {
    auto elem = m_map.find(hash);
    return elem == m_map.end() ? 0 : elem->second;
  }

  const_iterator
  begin() const noexcept
  {
    return m_map.begin();
  }

  const_iterator
  end() const noexcept
  {
    return m_map.end();
  }

  bool
  has(const std::size_t& hash) const
  {
    return m_map.find(hash) != end();
  }

private:
  std::map<std::size_t, SeqNo> m_map;
};

} // namespace ndn::svs


#endif // NDN_SVS_VERSION_VECTOR_HPP

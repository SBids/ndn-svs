/* -*- Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2012-2020 University of California, Los Angeles
 *
 * This file is part of SVS, synchronization library for distributed realtime
 * applications for NDN.
 *
 * SVS is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * SVS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * SVS, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "version-vector.hpp"

namespace ndn {
namespace svs {

VersionVector::VersionVector(std::string encoded) {
  int start = 0;
  for (size_t i = 0; i < encoded.size(); ++i) {
    if (encoded[i] == '_') {
      std::string str = encoded.substr(start, i - start);
      size_t cursor_1 = str.find("-");
      NodeID nid = unescape(str.substr(0, cursor_1));
      uint64_t seq = std::stoll(str.substr(cursor_1 + 1, i));
      set(nid, seq);
      start = i + 1;
    }
  }
}

std::string
VersionVector::encode() const
{
  std::string encoded = "";
  for (auto entry : m_umap) {
    encoded += (escape(entry.first) + "-" + to_string(entry.second) + "_");
  }
  return encoded;
}

} // namespace ndn
} // namespace svs

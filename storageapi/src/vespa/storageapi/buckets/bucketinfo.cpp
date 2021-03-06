// Copyright 2017 Yahoo Holdings. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.
#include "bucketinfo.h"
#include <vespa/vespalib/stllike/asciistream.h>
#include <vespa/vespalib/util/xmlstream.h>

namespace storage::api {

BucketInfo::BucketInfo()
    : _lastModified(0),
      _checksum(0),
      _docCount(0),
      _totDocSize(1),
      _metaCount(0),
      _usedFileSize(1),
      _ready(false),
      _active(false)
{}

BucketInfo::BucketInfo(uint32_t checksum, uint32_t docCount,
                       uint32_t totDocSize)
    : _lastModified(0),
      _checksum(checksum),
      _docCount(docCount),
      _totDocSize(totDocSize),
      _metaCount(docCount),
      _usedFileSize(totDocSize),
      _ready(false),
      _active(false)
{}

BucketInfo::BucketInfo(uint32_t checksum, uint32_t docCount,
                       uint32_t totDocSize, uint32_t metaCount,
                       uint32_t usedFileSize)
    : _lastModified(0),
      _checksum(checksum),
      _docCount(docCount),
      _totDocSize(totDocSize),
      _metaCount(metaCount),
      _usedFileSize(usedFileSize),
      _ready(false),
      _active(false)
{}

BucketInfo::BucketInfo(uint32_t checksum, uint32_t docCount,
                       uint32_t totDocSize, uint32_t metaCount,
                       uint32_t usedFileSize,
                       bool ready, bool active)
    : _lastModified(0),
      _checksum(checksum),
      _docCount(docCount),
      _totDocSize(totDocSize),
      _metaCount(metaCount),
      _usedFileSize(usedFileSize),
      _ready(ready),
      _active(active)
{}

BucketInfo::BucketInfo(uint32_t checksum, uint32_t docCount,
                       uint32_t totDocSize, uint32_t metaCount,
                       uint32_t usedFileSize,
                       bool ready, bool active, Timestamp lastModified)
    : _lastModified(lastModified),
      _checksum(checksum),
      _docCount(docCount),
      _totDocSize(totDocSize),
      _metaCount(metaCount),
      _usedFileSize(usedFileSize),
      _ready(ready),
      _active(active)
{}

BucketInfo::BucketInfo(const BucketInfo &) = default;
BucketInfo & BucketInfo::operator = (const BucketInfo &) = default;
BucketInfo::~BucketInfo() {}

bool
BucketInfo::operator==(const BucketInfo& info) const
{
    return (_checksum == info._checksum &&
            _docCount == info._docCount &&
            _totDocSize == info._totDocSize &&
            _metaCount == info._metaCount &&
            _usedFileSize == info._usedFileSize &&
            _ready == info._ready &&
            _active == info._active);
}

// TODO: add ready/active to printing
void
BucketInfo::print(vespalib::asciistream& out, const PrintProperties&) const
{
    out << "BucketInfo(";
    if (valid()) {
        out << "crc 0x" << vespalib::hex << _checksum << vespalib::dec
            << ", docCount " << _docCount
            << ", totDocSize " << _totDocSize;
        if (_totDocSize != _usedFileSize) {
            out << ", metaCount " << _metaCount
                << ", usedFileSize " << _usedFileSize;
        }
        out << ", ready " << (_ready ? "true" : "false")
            << ", active " << (_active ? "true" : "false");

        if (_lastModified != 0) {
            out << ", last modified " << _lastModified;
        }
    } else {
        out << "invalid";
    }
    out << ")";
}

void
BucketInfo::printXml(vespalib::XmlOutputStream& xos) const
{
    using namespace vespalib::xml;
    xos << XmlAttribute("checksum", _checksum, XmlAttribute::HEX)
        << XmlAttribute("docs", _docCount)
        << XmlAttribute("size", _totDocSize)
        << XmlAttribute("metacount", _metaCount)
        << XmlAttribute("usedfilesize", _usedFileSize)
        << XmlAttribute("ready", _ready)
        << XmlAttribute("active", _active)
        << XmlAttribute("lastmodified", _lastModified);
}

}

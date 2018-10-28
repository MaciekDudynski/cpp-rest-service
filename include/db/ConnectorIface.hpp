#pragma once

#include <bsoncxx/builder/stream/document.hpp>
#include <string>

namespace service::db
{
    class ConnectorIface
    {
      public:
        virtual ~ConnectorIface() = default;

        virtual void insertOneDocument( const std::string & collectionName, const bsoncxx::document::value & doc_value ) const = 0;
    };
} // namespace service::db

#pragma once

#include <map>
#include <string>

namespace service
{
    class ModelIface
    {
      public:
        virtual ~ModelIface() = default;

        virtual std::map< std::string, std::string > serialize() const = 0;

        virtual std::string tableName() const = 0;
    };
} // namespace service

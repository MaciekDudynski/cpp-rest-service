#include "db/Connector.hpp"

#include "db/ConnectionStringProviderIface.hpp"

#include <iostream>
#include <mongocxx/v_noabi/mongocxx/client.hpp>
#include <mongocxx/v_noabi/mongocxx/uri.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

namespace service::db
{
    Connector::Connector( std::unique_ptr< ConnectionStringProviderIface > connectionStringProvider )
    {
        std::cout << "DB connector is creating mongoDB driver instance..." << std::endl;
        _instance             = std::make_unique< mongocxx::instance >();
        auto connectionString = connectionStringProvider->connectionString();
        std::cout << "DB connector is creating mongoDB uri..." << std::endl;
        auto uri = mongocxx::uri( connectionString );
        std::cout << "DB connector is creating mongoDB pool..." << std::endl;
        _pool = std::make_unique< mongocxx::pool >( uri );

        /// test
        std::cout << "DB connector is testing connection to mongoDB..." << std::endl;
        try
        {
            auto client                        = _pool->acquire();
            auto db                            = client->database( "cpp-rest-service" );
            auto collection                    = db.collection( "users" );
            auto builder                       = bsoncxx::builder::stream::document{};
            bsoncxx::document::value doc_value = builder << "login"
                                                         << "test" << bsoncxx::builder::stream::finalize;
            auto found = collection.find_one( doc_value.view() ).value();
            std::cout << found.view()[ "login" ].get_utf8().value << std::endl;
        }
        catch( const std::exception & e )
        {
            std::cout << e.what() << std::endl;
        }
    }

    Connector::~Connector()
    {
    }

    void Connector::insertOneDocument( const std::string & collectionName, const bsoncxx::document::value & doc_value ) const
    {
        auto client     = _pool->acquire();
        auto db         = client->database( "cpp-rest-service" );
        auto collection = db.collection( collectionName );

        collection.insert_one( doc_value.view() );
    }

} // namespace service::db

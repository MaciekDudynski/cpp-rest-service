#include "db/Connector.hpp"

#include "db/ConnectionStringProviderIface.hpp"

#include <iostream>
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
        std::cout << "DB connector is creating mongoDB client..." << std::endl;
        _client = std::make_unique< mongocxx::client >( uri );
        /// test
        std::cout << "DB connector is testing connection to mongoDB..." << std::endl;
        _client->list_databases();
    }

    Connector::~Connector()
    {
    }

    void Connector::insertOneDocument( const std::string & collectionName, const bsoncxx::document::value & doc_value ) const
    {
        auto db         = _client->database( "cpp-rest-service" );
        auto collection = db.collection( collectionName );

        //auto builder                       = document{};
        //bsoncxx::document::value doc_value = builder << "name"
        //                                             << "MongoDB"
        //                                             << "type"
        //                                             << "database"
        //                                             << "count" << 1 << "versions" << open_array << "v3.2"
        //                                             << "v3.0"
        //                                             << "v2.6" << close_array << "info" << open_document << "x" << 203 << "y" << 102
        //                                             << close_document << finalize;

        /*bsoncxx::stdx::optional< mongocxx::result::insert_one > result =*/
        collection.insert_one( doc_value.view() );
    }

} // namespace service::db

#include "MongoHandler.h"

boost::thread_specific_ptr<mongocxx::client> MongoHandler::client;



MongoHandler::~MongoHandler() = default;

MongoHandler::MongoHandler()
{
    std::string mongoPort = "27017";
    std::string mongoServer = "localhost";
	std::string mongo = "mongodb://" + mongoServer + ":" + mongoPort;

    uri = mongocxx::uri(mongo);
    client.reset(new mongocxx::client(uri));
}

std::string MongoHandler::GetMoviesCollection()
{	
	std::string MoviesCollectionJson = "{\"links\":{\"self\":\"/films\"},\"films\":[ ";

    mongocxx::client& localClient = getClient();
    mongocxx::database db = localClient["MoviesDB"];
    mongocxx::collection coll = db["MoviesCollection"];

    mongocxx::cursor cursor = coll.find(document{} << finalize);
    for (auto doc : cursor)
    {
        MoviesCollectionJson += bsoncxx::to_json(doc) + ",";
    }
    MoviesCollectionJson.pop_back();
    return MoviesCollectionJson + "]}\n";
}

std::string MongoHandler::GetMovie(std::string &MovieId)
{
    std::string MovieJsonString = "";

    mongocxx::client& localClient = getClient();
    mongocxx::database db = localClient["MoviesDB"];
    mongocxx::collection coll = db["MoviesDetailed"];

    mongocxx::stdx::optional<bsoncxx::document::value> maybe_result = coll.find_one(document{} << "id" << MovieId << finalize);
	if(maybe_result) {
		MovieJsonString += bsoncxx::to_json(*maybe_result)+ "\n";
	}
	else
	{
		MovieJsonString = "";
	}

    return MovieJsonString;
	
}

void MongoHandler::AddRating(std::string& MovieId, std::string& Rating, std::string& UserId){
	mongocxx::client& localClient = getClient();
    mongocxx::database db = localClient["MoviesDB"];
    mongocxx::collection coll = db["MoviesDetailed"];
	std::string strRating = Rating == "1" ? "One" : Rating == "2" ? "Two" :  Rating == "3" ? "Three" :  Rating == "4" ? "Four" :
						Rating == "5" ? "Five" : Rating == "6" ? "Six" :  Rating == "7" ? "Seven" :  Rating == "8" ? "Eight" :  Rating == "9" ? "Nine" :  Rating == "10" ? "Ten" : "";
	mongocxx::stdx::optional<bsoncxx::document::value> maybe_result = coll.find_one(document{} << "id" << MovieId << "votes.Votes" << UserId << finalize); 
	if (maybe_result){
		// If already had voted - ignore for now
	}
	else{
		coll.update_one(document{} << "id" << MovieId << "votes.Stars" << strRating << finalize,
                        document{} << "$addToSet" << open_document <<
                        "votes.$.Votes" << UserId << close_document << finalize);
	}

	
	
}

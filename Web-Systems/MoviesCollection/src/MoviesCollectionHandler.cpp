#include "MoviesCollectionHandler.h"

const unsigned long MOVIE_PREFIX_SIZE = sizeof("/films/") - 1;

bool IsMoviesCollection(const std::string &path, const std::string &method)
{
    return path == "/films" && method == "GET";
}

bool IsMovie(const std::string &path, const std::string &method, std::string& MovieId)
{
    if (method == "GET" && path.find("/films/") == 0)
    {
        MovieId = path.substr(MOVIE_PREFIX_SIZE);
        return true;
    }
    return false;
}


bool IsMovieRate(const std::string& path, const std::string& method,
                std::string& MovieId, std::string& Rating)
{
    if (method == "POST" && path.find("/films/") == 0) {
        auto slashLeftPos = path.find('/', MOVIE_PREFIX_SIZE);
        auto slashRightPos = path.rfind('/');
        if (slashRightPos == slashLeftPos && slashLeftPos > MOVIE_PREFIX_SIZE) {
            MovieId = path.substr(MOVIE_PREFIX_SIZE, slashLeftPos - MOVIE_PREFIX_SIZE);
            Rating = path.substr(slashLeftPos + 1);
            return true;
        }
    }
    return false;
}



MoviesCollectionHandler::~MoviesCollectionHandler() = default;

MoviesCollectionHandler::MoviesCollectionHandler(fastcgi::ComponentContext *context)
{
   
    mongoHand = new MongoHandler();
}

void MoviesCollectionHandler::ScheduleRequest(fastcgi::Request *request)
{
    auto &path = request->getScriptName();
    auto &method = request->getRequestMethod();
	std::string UserId = request->hasArg("user") ? request->getArg("user") : "";

    request->setContentType("application/json");

    std::string MovieId, Rating;

    if (IsMoviesCollection(path, method))
    {
     RespondMoviesCollection(request);

    } 
	else if (IsMovie(path, method, MovieId))
    {
        if (!MovieId.empty())
        {
            RespondMovie(request, MovieId);
        } else
        {
            request->setStatus(404);
        }

    }
	else if (IsMovieRate(path, method, MovieId, Rating)){

		if (UserId != ""){
			RateMovie(request, MovieId, Rating, UserId);
		}
		else{
			std::string response = "Bad User\n";
			request->write(response.c_str(), response.size());
		}
		
	}
	else
    {
        request->setStatus(404);
    }
}

void MoviesCollectionHandler::RespondMoviesCollection(fastcgi::Request *request)
{
    std::string response;

    response = mongoHand->GetMoviesCollection();

    request->write(response.c_str(), response.size());

}

void MoviesCollectionHandler::RespondMovie(fastcgi::Request *request, std::string& MovieId)
{
    std::string response;

    response = mongoHand->GetMovie(MovieId);
	if (!response.empty()){
		request->write(response.c_str(), response.size());
	}
	else {
		request->setStatus(404);
	}
    

}

void MoviesCollectionHandler::RateMovie(fastcgi::Request *request, std::string& MovieId, std::string& Rating, std::string& UserId)
{   
    //Check if movie exists
    std::string response;

    response = mongoHand->GetMovie(MovieId);
    if (response.empty()){
        request->setStatus(404);
    }
    
    if (Rating != "1" && Rating != "2" && Rating != "3" && Rating != "4" && Rating != "5" && 
		Rating != "6" && Rating != "7" && Rating != "8" && Rating != "9" && Rating != "10") {
        request->setStatus(404);
    }
    else{
        mongoHand->AddRating(MovieId, Rating, UserId);
		request->setStatus(200);
    }
    
}


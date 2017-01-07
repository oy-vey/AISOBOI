#include <fastcgi2/config.h>
#include <fastcgi2/component.h>
#include <fastcgi2/handler.h>
#include <fastcgi2/request.h>
#include <vector>
#include <string>

#include "MongoHandler.h"


class MoviesCollectionHandler
{
public:



    MoviesCollectionHandler(fastcgi::ComponentContext *context);
    ~MoviesCollectionHandler();

    void ScheduleRequest(fastcgi::Request *request);

private:

    MongoHandler* mongoHand;

    void RespondMoviesCollection(fastcgi::Request *request);
    void RespondMovie(fastcgi::Request *request, std::string& MovieId);
	void RateMovie(fastcgi::Request *request, std::string& pollId, std::string& Rating, std::string& UserId);
};
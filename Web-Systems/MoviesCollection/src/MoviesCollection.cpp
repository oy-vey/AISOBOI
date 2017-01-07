#include <fastcgi2/component.h>
#include <fastcgi2/component_factory.h>
#include <fastcgi2/handler.h>
#include <fastcgi2/request.h>

#include "MoviesCollectionHandler.h"

class MoviesCollection : virtual public fastcgi::Component, virtual public fastcgi::Handler
{

public:
    MoviesCollection(fastcgi::ComponentContext *context) : fastcgi::Component(context)
    {
        MCHandle = new MoviesCollectionHandler(context);
    }

    virtual ~MoviesCollection()
    {}

public:
    virtual void onLoad()
    {}

    virtual void onUnload()
    {}

    virtual void handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context)
    {
        MCHandle->ScheduleRequest(request);
    }

private:
    MoviesCollectionHandler* MCHandle;

};

FCGIDAEMON_REGISTER_FACTORIES_BEGIN();
FCGIDAEMON_ADD_DEFAULT_FACTORY("service_factory", MoviesCollection);
FCGIDAEMON_REGISTER_FACTORIES_END();
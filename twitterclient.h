#ifndef TWITTERCLIENT_H
#define TWITTERCLIENT_H
#include <twitcurl.h>
#include <curl/curl.h>
#include <string>

class twitterClient
{
private:
    std::string ConsumerKey, ConsumerSecret, AccessTokenKey, AccessTokenSecret;

protected:
    twitCurl twitterObj;

public:
    twitterClient();
};

#endif // TWITTERCLIENT_H

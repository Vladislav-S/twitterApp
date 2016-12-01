#include "twitterclient.h"

twitterClient::twitterClient()
{
    ConsumerKey       = "";
    ConsumerSecret    = "";
    AccessTokenKey    = "";
    AccessTokenSecret = "";
    twitterObj.getOAuth().setConsumerKey(ConsumerKey);
    twitterObj.getOAuth().setConsumerSecret(ConsumerSecret);
    twitterObj.getOAuth().setOAuthTokenKey(AccessTokenKey);
    twitterObj.getOAuth().setOAuthTokenSecret(AccessTokenSecret);
}

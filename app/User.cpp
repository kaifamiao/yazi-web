#include <app/User.h>
using namespace yazi::app;

REGISTER_CLASS(User);
REGISTER_CLASS_METHOD(User, profile, void, const Request &, Response &);

void User::profile(const Request & req, Response & resp)
{
    Json json;
    json["uid"] = 1;
    json["name"] = "kitty";
    json["age"] = 18;
    json["gender"] = "female";
    resp.json(json.str());
}

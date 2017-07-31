#pragma once

#include <stdexcept>
#include <string>

#include <simple-web-server/server_http.hpp>
#include <simple-web-server/server_https.hpp>

namespace greyhound
{

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpsServer = SimpleWeb::Server<SimpleWeb::HTTPS>;
using Req = HttpServer::Request;
using Res = HttpServer::Response;
using ReqPtr = std::shared_ptr<Req>;
using ResPtr = std::shared_ptr<Res>;
using HttpStatusCode = SimpleWeb::StatusCode;

using Headers = SimpleWeb::CaseInsensitiveMultimap;

using Paths = std::vector<std::string>;

using Data = std::vector<char>;

class HttpError : public std::runtime_error
{
public:
    HttpError(std::string message)
        : std::runtime_error(message)
    { }

    HttpError(HttpStatusCode code, std::string message = "Unknown error")
        : std::runtime_error(message)
        , m_code(code)
    { }

    HttpStatusCode code() const { return m_code; }

private:
    const HttpStatusCode m_code =
        HttpStatusCode::server_error_internal_server_error;
};

class Http400 : public HttpError
{
public:
    Http400(std::string message) :
        HttpError(HttpStatusCode::client_error_bad_request, message)
    { }
};

} // namespace greyhound

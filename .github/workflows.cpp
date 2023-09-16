#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;

// Function to check service availability
void checkServiceAvailability(http_client& client)
{
    uri_builder builder(U("/calculator/greeting"));
    http_response response = client.request(methods::GET, builder.to_string()).get();

    if (response.status_code() == status_codes::OK)
    {
        std::cout << response.extract_string().get() << std::endl;
    }
    else
    {
        std::cout << "Service is not available" << std::endl;
    }
}

// Function to add two numbers
void addNumbers(http_client& client, int first, int second)
{
    uri_builder builder(U("/calculator/add"));
    json::value body;
    body[U("first")] = json::value::number(first);
    body[U("second")] = json::value::number(second);

    http_response response = client.request(methods::POST, builder.to_string(), body).get();

    if (response.status_code() == status_codes::OK)
    {
        json::value result = response.extract_json().get();
        std::cout << "Result of addition: " << result[U("result")].as_integer() << std::endl;
    }
    else
    {
        std::cout << "Failed to add numbers" << std::endl;
    }
}

// Function to subtract two numbers
void subtractNumbers(http_client& client, int first, int second)
{
    uri_builder builder(U("/calculator/subtract"));
    json::value body;
    body[U("first")] = json::value::number(first);
    body[U("second")] = json::value::number(second);

    http_response response = client.request(methods::POST, builder.to_string(), body).get();

    if (response.status_code() == status_codes::OK)
    {
        json::value result = response.extract_json().get();
        std::cout << "Result of subtraction: " << result[U("result")].as_integer() << std::endl;
    }
    else
    {
        std::cout << "Failed to subtract numbers" << std::endl;
    }
}

int main()
{
    http_client client(U("http://localhost:8080")); // Replace with the actual API URL

    checkServiceAvailability(client);
    addNumbers(client, 5, 3);
    subtractNumbers(client, 10, 4);

    return 0;
}

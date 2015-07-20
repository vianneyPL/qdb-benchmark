#pragma once

#include <bench/core/test_instance.hpp>

#include <filesystem>
#include <fstream>
#include <sstream>

namespace bench {
namespace report {

class jsonp {
public:
    void add_test(const test_instance& test)
    {
        std::ostringstream json;

        json 
            << "{" 
            << "\"name\":\"" << test.test_class.id << "\","
            << "\"description\":\"" << test.test_class.description << "\","
            << "\"content_size\":\"" << test.config.content_size << "\","
            << "\"threads\":[";

        for (unsigned i=0; i<test.result.threads.size(); i++)
        {
            auto& thread = test.result.threads[i];

            if (i > 0) json << ",";

            json << "{\"times\":[";

            for (unsigned j=0; j<thread.size(); j++)
            {
                if (j > 0) json << ",";
                json << thread[j].time;
            }

            json << "],\"iterations\":[";

            for (unsigned j=0; j<thread.size(); j++)
            {
                if (j > 0) json << ",";
                json << thread[j].iterations;
            }

            json << "]}";
        }

        json << "]}";

        test_jsons.push_back(json.str());
    }

    void save()
    {
        std::ofstream file;
        file.open("results.jsonp");
        file << "results=[";
        for (unsigned i=0; i<test_jsons.size(); i++)
        {
            if (i > 0) file << ",";
            file << test_jsons[i];
        }
        file << "]";
        file.close();
    }

private:
    std::vector<std::string> test_jsons;
};

}}
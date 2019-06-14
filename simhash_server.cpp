#include <unistd.h>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <string.h>
#include "Husky/ThreadPoolServer.hpp"
#include "Simhasher.hpp"

using namespace Husky;
using namespace Simhash;

const size_t PORT = 11201;
const size_t THREAD_NUMBER = 4;
const size_t QUEUE_MAX_SIZE = 256;
const char* const DICT_PATH = "./dict/jieba.dict.utf8";
const char* const MODEL_PATH = "./dict/hmm_model.utf8";
const char* const IDF_PATH = "./dict/idf.utf8";
const char* const STOP_WORDS_PATH = "./dict/stop_words.utf8";
const size_t TOP_N = 10;

class ReqHandler: public IRequestHandler
{
    public:
        ReqHandler(const string& dictPath, const string& modelPath, const string& idfPath, const string& stopwordsPath): _simasher(dictPath, modelPath, idfPath, stopwordsPath){};
        virtual ~ReqHandler(){};
    public:
        virtual bool do_GET(const HttpReqInfo& httpReq, string& strSnd) const
        {
            string s, n_str, s_str;
            size_t top_n;
            httpReq.GET("s", s_str);
            URLDecode(s_str, s);
            httpReq.GET("n", n_str);
            top_n = n_str.length() ? atoi(n_str.c_str())  : TOP_N;

            uint64_t u64;
            vector<pair<string ,double> > res;
            bool ok = _simasher.make(s, top_n, u64);
            _simasher.extract(s, res, top_n);

            stringstream res_ss;
            res_ss<<res; 
            string res_str = res_ss.str();

            stringstream u64_ss;
            u64_ss<<u64; 
            string u64_str = u64_ss.str();

            strSnd = u64_str+"\n"+res_str;
            return ok;
        }

        virtual bool do_POST(const HttpReqInfo& httpReq, string& strSnd) const
        {
            string n_str;
            size_t top_n;
            httpReq.GET("n", n_str);
            top_n = n_str.length() ? atoi(n_str.c_str()) : TOP_N;
            
            const string& s = httpReq.getBody();
            uint64_t u64;
            vector<pair<string ,double> > res;
            bool ok = _simasher.make(s, top_n, u64);
            _simasher.extract(s, res, top_n);

            stringstream res_ss;
            res_ss<<res; 
            string res_str = res_ss.str();

            stringstream u64_ss;
            u64_ss<<u64; 
            string u64_str = u64_ss.str();

            strSnd = u64_str+"\n"+res_str;
            return ok;
        }
    private:
        Simhasher _simasher;
};

int main(int argc, char* argv[])
{
    ReqHandler reqHandler(DICT_PATH, MODEL_PATH, IDF_PATH, STOP_WORDS_PATH);
    ThreadPoolServer server(THREAD_NUMBER, QUEUE_MAX_SIZE, PORT, reqHandler);
    server.start();
    return EXIT_SUCCESS;
}


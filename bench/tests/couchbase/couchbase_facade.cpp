#include <bench/tests/couchbase/couchbase_facade.hpp>

#include <cassert>
#include <iostream>
#include <stdexcept>

namespace bench
{
namespace tests
{
namespace couchbase
{

// couchbase callbacks
// may their api be damned
namespace detail
{
lcb_error_t _last_error;
std::string _last_result;
std::condition_variable _cv;
std::mutex _lock;
bool _ready = false;

void cb_get_callback(lcb_t instance, int cbtype, const lcb_RESPBASE * rb)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    const lcb_RESPGET * resp = (const lcb_RESPGET *)rb;
    _last_error = resp->rc;
    if (_last_error == LCB_SUCCESS)
    {
        _last_result = std::string(static_cast<const char *>(resp->value), resp->nvalue);
    }
    _ready = true;
    _cv.notify_one();
}
void cb_put_callback(lcb_t instance, int cbtype, const lcb_RESPBASE * rb)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    const lcb_RESPGET * resp = (const lcb_RESPGET *)rb;
    _last_error = resp->rc;
    _ready = true;
    _cv.notify_one();
}
void cb_rm_callback(lcb_t instance, int cbtype, const lcb_RESPBASE * rb)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    const lcb_RESPGET * resp = (const lcb_RESPGET *)rb;
    _last_error = resp->rc;
    _ready = true;
    _cv.notify_one();
}
} // namespace detail

couchbase_facade::couchbase_facade()
{
}

couchbase_facade::~couchbase_facade()
{
    lcb_destroy(_instance);
}

void couchbase_facade::connect(const std::string & cluster_uri)
{
    assert(lcb_version_g >= 0x020506 && "This example requires 2.5.6 or greater");

    lcb_create_st crst;
    memset(&crst, 0, sizeof(crst));
    crst.version = 3;
    crst.v.v3.connstr = cluster_uri.c_str();
    auto err = lcb_create(&_instance, &crst);
    if (err != LCB_SUCCESS)
    {
        std::cout << "Error while creating\n";
        throw std::runtime_error(lcb_strerror(NULL, err));
    }
    err = lcb_connect(_instance);
    if (err != LCB_SUCCESS)
    {
        std::cout << "Error while connecting\n";
        throw std::runtime_error(lcb_strerror(NULL, err));
    }
    lcb_wait3(_instance, LCB_WAIT_DEFAULT);
    err = lcb_get_bootstrap_status(_instance);
    if (err != LCB_SUCCESS)
    {
        std::cout << "Error while checking boostrap\n";
        throw std::runtime_error(lcb_strerror(NULL, err));
    }

    lcb_install_callback3(_instance, LCB_CALLBACK_GET, detail::cb_get_callback);
    lcb_install_callback3(_instance, LCB_CALLBACK_STORE, detail::cb_put_callback);
    lcb_install_callback3(_instance, LCB_CALLBACK_REMOVE, detail::cb_rm_callback);
}

void couchbase_facade::remove(const std::string & alias)
{
    lcb_CMDREMOVE cmd = {0};
    LCB_CMD_SET_KEY(&cmd, alias.c_str(), alias.length());
    auto err = lcb_remove3(_instance, NULL, &cmd);
    if (err != LCB_SUCCESS)
    {
        throw std::runtime_error(lcb_strerror(NULL, err));
    }
    {
        std::unique_lock<std::mutex> lk(detail::_lock);
        detail::_cv.wait(lk, [] { return detail::_ready; });
        detail::_ready = false;
        if (detail::_last_error != LCB_SUCCESS)
        {
            throw std::runtime_error(lcb_strerror(NULL, detail::_last_error));
        }
    }
}

void couchbase_facade::blob_put(const std::string & alias, const std::string & content)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    lcb_CMDSTORE cmd = {0};
    LCB_CMD_SET_KEY(&cmd, alias.c_str(), alias.length());
    LCB_CMD_SET_VALUE(&cmd, content.c_str(), content.length());
    cmd.operation = LCB_ADD;
    auto err = lcb_store3(_instance, NULL, &cmd);
    if (err != LCB_SUCCESS)
    {
        throw std::runtime_error(lcb_strerror(NULL, err));
    }
    {
        std::unique_lock<std::mutex> lk(detail::_lock);
        detail::_cv.wait(lk, [] { return detail::_ready; });
        detail::_ready = false;
        if (detail::_last_error != LCB_SUCCESS)
        {
            throw std::runtime_error(lcb_strerror(NULL, detail::_last_error));
        }
    }
}

void couchbase_facade::blob_update(const std::string & alias, const std::string & content)
{
    lcb_CMDSTORE cmd = {0};
    LCB_CMD_SET_KEY(&cmd, alias.c_str(), alias.length());
    LCB_CMD_SET_VALUE(&cmd, content.c_str(), content.length());
    cmd.operation = LCB_SET;
    auto err = lcb_store3(_instance, NULL, &cmd);
    if (err != LCB_SUCCESS)
    {
        throw std::runtime_error(lcb_strerror(NULL, err));
    }
    {
        std::unique_lock<std::mutex> lk(detail::_lock);
        detail::_cv.wait(lk, [] { return detail::_ready; });
        detail::_ready = false;
        if (detail::_last_error != LCB_SUCCESS)
        {
            throw std::runtime_error(lcb_strerror(NULL, detail::_last_error));
        }
    }
}

std::string couchbase_facade::blob_get(const std::string & alias)
{
    std::string result;
    lcb_CMDGET cmd = {0};
    LCB_CMD_SET_KEY(&cmd, alias.c_str(), alias.length());
    auto err = lcb_get3(_instance, NULL, &cmd);
    if (err != LCB_SUCCESS)
    {
        throw std::runtime_error(lcb_strerror(NULL, err));
    }
    {
        std::unique_lock<std::mutex> lk(detail::_lock);
        detail::_cv.wait(lk, [] { return detail::_ready; });
        detail::_ready = false;
        if (detail::_last_error != LCB_SUCCESS)
        {
            throw std::runtime_error(lcb_strerror(NULL, detail::_last_error));
        }
        result = detail::_last_result;
    }
    return result;
}

} // namespace couchbase
} // namespace tests
} // namespace bench

#include <snmp/session.hpp>

#include <snmp/exceptions.hpp>

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include <cassert>
#include <memory>
#include <stdexcept>

static_assert(sizeof(snmp::oid::subid_type) == sizeof(::oid), "");

bool snmp::session::_initialized = false;

struct pdu_deleter
{
    void operator()(::snmp_pdu * pdu)
    {
        snmp_free_pdu(pdu);
    }
};

static ::snmp_session * cast_session(void * session)
{
    return static_cast<::snmp_session *>(session);
}

static void save_variable(std::map<snmp::oid, snmp::variant> & variables, ::variable_list * var)
{
    snmp::oid oid(var->name, var->name_length);

    switch (var->type)
    {
    case ASN_OCTET_STR:
        variables[oid] = std::string(reinterpret_cast<char *>(var->val.string), var->val_len);
        break;

    case ASN_INTEGER:
        variables[oid] = *var->val.integer;
        break;

    case ASN_OBJECT_ID:
        variables[oid] = snmp::oid(var->val.objid, var->val_len / sizeof(snmp::oid::subid_type));
        break;
    }
}

static std::unique_ptr<::snmp_pdu, pdu_deleter> perform_request(::snmp_session * session, ::snmp_pdu * request)
{
    struct snmp_pdu * unsafe_response;
    auto status = snmp_synch_response(session, request, &unsafe_response);

    std::unique_ptr<::snmp_pdu, pdu_deleter> response(unsafe_response);

    if (status != STAT_SUCCESS) throw snmp::session_error(session);
    if (response->errstat != SNMP_ERR_NOERROR) throw snmp::protocol_error(response->errstat);

    return response;
}

void snmp::session::open(const std::string & peername, const std::string & community)
{
    if (!_initialized)
    {
        init_snmp("snmpapp");
        shutdown_snmp_logging();
        _initialized = true;
    }

    ::snmp_session session;
    snmp_sess_init(&session);
    session.peername = const_cast<char *>(peername.c_str());
    session.version = SNMP_VERSION_1;
    session.community = reinterpret_cast<u_char *>(const_cast<char *>(community.c_str()));
    session.community_len = community.size();

    _ss = snmp_open(&session);
    if (!_ss) throw std::runtime_error("Failed to open SNMP session");
}

std::map<snmp::oid, snmp::variant> snmp::session::walk(oid root)
{
    std::map<snmp::oid, snmp::variant> variables;

    oid current_oid = root;
    while (current_oid.starts_with(root))
    {
        auto request = snmp_pdu_create(SNMP_MSG_GETNEXT);
        snmp_add_null_var(request, current_oid.data(), current_oid.size());

        auto response = perform_request(cast_session(_ss), request);

        auto var = response->variables;
        assert(var->next_variable == nullptr);

        save_variable(variables, var);

        current_oid = oid(var->name, var->name_length);
    }

    return variables;
}

void snmp::session::get_bulk(std::map<snmp::oid, snmp::variant> & variables)
{
    auto request = snmp_pdu_create(SNMP_MSG_GET);

    for (auto var : variables)
    {
        snmp_add_null_var(request, var.first.data(), var.first.size());
    }

    auto response = perform_request(cast_session(_ss), request);

    for (auto var = response->variables; var; var = var->next_variable)
    {
        save_variable(variables, var);
    }
}

void snmp::session::close()
{
    snmp_close(static_cast<::snmp_session *>(cast_session(_ss)));
}

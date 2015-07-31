#include <bench/probes/all_probes.hpp>
#include <bench/probes/qdb/node_status.hpp>

bench::probe_class_collection bench::probes::get_all_probes()
{
    return {new qdb::node_status::probe_class()};
}

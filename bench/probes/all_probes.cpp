#include <bench/probes/all_probes.hpp>
#include <bench/probes/qdb/node_memory.hpp>

bench::probe_collection bench::probes::get_all_probes()
{
    return {new qdb::node_memory::probe_class()};
}

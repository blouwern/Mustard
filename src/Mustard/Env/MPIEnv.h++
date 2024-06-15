#pragma once

#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/Env/CLI/CLI.h++"
#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "mpi.h"

#include <concepts>
#include <functional>
#include <optional>
#include <ostream>
#include <string>
#include <type_traits>
#include <vector>

namespace Mustard::Env {

class MPIEnv : public BasicEnv,
               public Memory::PassiveSingleton<MPIEnv> {
public:
    MPIEnv(int argc, char* argv[],
           std::optional<std::reference_wrapper<CLI::CLI<>>> cli = {},
           enum VerboseLevel verboseLevel = {},
           bool printWelcomeMessage = true);
    virtual ~MPIEnv();

    using PassiveSingleton<MPIEnv>::Instance;
    using PassiveSingleton<MPIEnv>::Available;
    using PassiveSingleton<MPIEnv>::Expired;
    using PassiveSingleton<MPIEnv>::Instantiated;
    static auto Initialized() -> auto { return Instantiated(); }
    static auto Finalized() -> auto { return Expired(); }

    auto MPIThreadSupport() const -> const auto& { return fMPIThreadSupport; }

    auto CommWorldRank() const -> const auto& { return fCommWorldRank; }
    auto CommWorldSize() const -> const auto& { return fCommWorldSize; }
    auto OnCommWorldMaster() const -> auto { return CommWorldRank() == 0; }
    auto OnCommWorldWorker() const -> auto { return CommWorldRank() != 0; }
    auto Sequential() const -> auto { return CommWorldSize() == 1; }
    auto Parallel() const -> auto { return CommWorldSize() != 1; }

    auto CommNode() const -> const auto& { return fCommNode; }
    auto CommNodeRank() const -> const auto& { return fCommNodeRank; }
    auto CommNodeSize() const -> const auto& { return fCommNodeSize; }
    auto OnCommNodeMaster() const -> auto { return CommNodeRank() == 0; }
    auto OnCommNodeWorker() const -> auto { return CommNodeRank() != 0; }

    auto NodeList() const -> const auto& { return fCluster.node; }
    auto LocalNodeID() const -> const auto& { return fCluster.local; }
    auto Node(int id) const -> const auto& { return NodeList().at(id); }
    auto LocalNode() const -> const auto& { return Node(LocalNodeID()); }
    auto ClusterSize() const -> int { return NodeList().size(); }
    auto OnSingleNode() const -> auto { return ClusterSize() == 1; }
    auto OnCluster() const -> auto { return ClusterSize() != 1; }

protected:
    auto PrintWelcomeMessageBody(int argc, char* argv[]) const -> void;

private:
    struct NodeInfo {
        int size;
        std::string name;
    };

private:
    const int fMPIThreadSupport;

    const int fCommWorldRank;
    const int fCommWorldSize;

    const struct {
        std::vector<NodeInfo> node;
        int local;
    } fCluster;

    const MPI_Comm fCommNode;
    const int fCommNodeRank;
    const int fCommNodeSize;
};

} // namespace Mustard::Env

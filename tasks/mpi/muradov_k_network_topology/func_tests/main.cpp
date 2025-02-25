#define OMPI_SKIP_MPICXX
#include <gtest/gtest.h>
#include <mpi.h>

#include "mpi/muradov_k_network_topology/include/ops_mpi.hpp"

namespace muradov_k_network_topology_mpi {

TEST(muradov_k_network_topology_mpi, FullRingCommunication) {
  MPI_Comm comm = MPI_COMM_WORLD;
  NetworkTopology topology(comm);
  topology.CreateRingTopology();

  int rank = 0;
  int size = 0;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);

  const int test_data = rank * 100;
  int received_data = -1;
  const int target = (rank + 1) % size;

  if (size >= 2) {
    // Send and receive in separate steps
    if (rank % 2 == 0) {
      topology.Send(target, &test_data, 1, MPI_INT);
      topology.Receive((rank - 1 + size) % size, &received_data, 1, MPI_INT);
    } else {
      topology.Receive((rank - 1 + size) % size, &received_data, 1, MPI_INT);
      topology.Send(target, &test_data, 1, MPI_INT);
    }

    if (rank == 0) {
      ASSERT_EQ(received_data, ((size - 1) * 100));
    } else {
      ASSERT_EQ(received_data, ((rank - 1) * 100));
    }
  } else {
    GTEST_SKIP() << "Requires at least 2 processes";
  }
}

}  // namespace muradov_k_network_topology_mpi

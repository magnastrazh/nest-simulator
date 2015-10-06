/*
 *  kernel_manager.h
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef KERNEL_MANAGER_H
#define KERNEL_MANAGER_H

#include "vp_manager.h"
#include "logging_manager.h"
#include "io_manager.h"
#include "connection_builder_manager.h"
#include "simulation_manager.h"
#include "modelrange_manager.h"
#include "event_delivery_manager.h"
#include "mpi_manager.h"
#include "rng_manager.h"

#include "dictdatum.h"

// clang-format off
/* BeginDocumentation
 Name: kernel - Global properties of the simulation kernel.
 
 Description:
 (start here.)
 
 Parameters:
 The following parameters can be set in the status dictionary.
 
 data_path                stringtype  - A path, where all data is written to (default is the current directory)
 data_prefix              stringtype  - A common prefix for all data files
 dict_miss_is_error       booltype    - Whether missed dictionary entries are treated as errors
 local_num_threads        integertype - The local number of threads (cf. global_num_virt_procs)
 max_delay                doubletype  - The maximum delay in the network
 min_delay                doubletype  - The minimum delay in the network
 ms_per_tic               doubletype  - The number of miliseconds per tic (cf. tics_per_ms, tics_per_step)
 network_size             integertype - The number of nodes in the network
 num_connections          integertype - The number of connections in the network
 off_grid_spiking         booltype    - Whether to transmit precise spike times in MPI communicatio
 print_time               booltype    - Whether to print progress information during the simulation
 resolution               doubletype  - The resolution of the simulation (in ms)
 tics_per_ms              doubletype  - The number of tics per milisecond (cf. ms_per_tic, tics_per_step)
 tics_per_step            integertype - The number of tics per simulation time step (cf. ms_per_tic, tics_per_ms)
 time                     doubletype  - The current simulation time
 total_num_virtual_procs  integertype - The total number of virtual processes (cf. local_num_threads)
 to_do                    integertype - The number of steps yet to be simulated
 T_max                    doubletype  - The largest representable time value
 T_min                    doubletype  - The smallest representable time value
 SeeAlso: Simulate, Node
 */
// clang-format on

namespace nest
{

class KernelManager
{
private:
  KernelManager();
  ~KernelManager();
  static KernelManager* kernel_manager_instance_;

  KernelManager( KernelManager const& );  // do not implement
  void operator=( KernelManager const& ); // do not implement

public:
  /**
   * Create/destroy and access the KernelManager singleton.
   */
  static void create_kernel_manager();
  static void destroy_kernel_manager();
  static KernelManager& get_kernel_manager();

  void init();
  void reset();

  void set_status( const DictionaryDatum& );
  void get_status( DictionaryDatum& );

  //! Returns true if kernel is initialized
  bool is_initialized() const;

  LoggingManager logging_manager;
  MPIManager mpi_manager;
  VPManager vp_manager;
  IOManager io_manager;
  ConnectionBuilderManager connection_builder_manager;
  EventDeliveryManager event_delivery_manager;
  SimulationManager simulation_manager;
  ModelRangeManager modelrange_manager;
  RNGManager rng_manager;

private:
  bool initialized_; //!< true if all sub-managers initialized
};

KernelManager& kernel();

} // namespace nest

inline nest::KernelManager&
nest::KernelManager::get_kernel_manager()
{
  assert( kernel_manager_instance_ );
  return *kernel_manager_instance_;
}

inline nest::KernelManager&
nest::kernel()
{
  return KernelManager::get_kernel_manager();
}

inline bool
nest::KernelManager::is_initialized() const
{
  return initialized_;
}

#endif /* KERNEL_MANAGER_H */

/*
** Copyright (2019-2020) Robotics Systems Lab - ETH Zurich:
** Markus Staeuble, Jonas Junger, Johannes Pankert, Philipp Leemann,
** Tom Lankhorst, Samuel Bachmann, Gabriel Hottiger, Lennert Nachtigall,
** Mario Mauerer, Remo Diethelm
**
** This file is part of the soem_interface.
**
** The soem_interface is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** The seom_interface is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with the soem_interface.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <soem_interface_examples/ExampleSlave.hpp>
#include <soem_interface/EthercatBusBase.hpp>

#include <memory>

#define UNUSED(x) (void)(x)

 #include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

int main(int argc, char** argv) {
  UNUSED(argc);
  UNUSED(argv);

  const std::string busName = "enp4s0";
  const std::string slaveName = "ZeroErr Driver";
  const uint32_t slaveAddress = 1;

  std::unique_ptr<soem_interface::EthercatBusBase> bus = std::make_unique<soem_interface::EthercatBusBase> (
    busName);

  std::shared_ptr<soem_interface_examples::ExampleSlave> slave = std::make_shared<soem_interface_examples::ExampleSlave> (
    slaveName, bus.get(), slaveAddress);

  bus->addSlave(slave);
  bus->startup();
  bus->setState(EC_STATE_PRE_OP, slaveAddress);
  std::this_thread::sleep_for(std::chrono::milliseconds(32));
  
  bus->setState(EC_STATE_SAFE_OP, slaveAddress);
  std::this_thread::sleep_for(std::chrono::milliseconds(32));
  
  bus->setState(EC_STATE_OPERATIONAL, slaveAddress);
  std::this_thread::sleep_for(std::chrono::milliseconds(32));

  if(!bus->waitForState(EC_STATE_OPERATIONAL, slaveAddress)) {
    // Something is wrong
    return 1;
  }

  while(true) {
    bus->updateRead();
    bus->updateWrite();
  }

  bus->shutdown();
  return 0;
}

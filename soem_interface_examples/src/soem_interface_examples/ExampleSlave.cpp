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

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

namespace soem_interface_examples {

ExampleSlave::ExampleSlave(const std::string& name, soem_interface::EthercatBusBase* bus, const uint32_t address) :
soem_interface::EthercatSlaveBase(bus, address), 
name_(name)
{
  pdoInfo_.rxPdoId_ = RX_PDO_ID;
  pdoInfo_.txPdoId_ = TX_PDO_ID;
  pdoInfo_.rxPdoSize_ = sizeof(command_);
  pdoInfo_.txPdoSize_ = sizeof(reading_);
  pdoInfo_.moduleId_ = 0x00123456;
}

bool ExampleSlave::startup() {
  // Do nothing else
  return true;
}

void ExampleSlave::updateRead() {
  bus_->readTxPdo(address_, reading_);
  std::cout << "Reading: " << sizeof(reading_) << std::endl;
  std::cout << "Status 0x" << std::hex << reading_.status << std::endl;
  std::cout << "Position " << reading_.position << std::endl;
  std::cout << "Input " << reading_.input << std::endl;
}

void ExampleSlave::updateWrite() {
  bus_->writeRxPdo(address_, command_);
  std::cout << "Write Command: " << sizeof(command_) << std::endl;
  std::cout << "Controlword 0x" << std::hex << command_.controlword << std::endl;
  std::cout << "Position " << command_.target_position << std::endl;
  std::cout << "Output " << command_.output << std::endl;
}

void ExampleSlave::shutdown() {
  // Do nothing
}

}
